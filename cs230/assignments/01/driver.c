// ----------------------------------------------------------------------------
// Project Name		:	Game State Manager
// File Name		:	Project1_Win32.cpp
// Author			:	Antoine Abi Chakra, Dan Weiss
// Creation Date	:	September 7, 2010
// Purpose			:	- Initial point for creating a window and intializing
//						all related systems for the game state manager project.
//						- Template for CS230 Prject 1
// History			:
// - 2010/09/07		:	Initial Implementation
// ----------------------------------------------------------------------------

#include "state.h"
#include "level1.h"
#include "level2.h"
#include "system.h"
#include "gamestatemanager.h"
#include "gamestatelist.h"
#include "input.h"

#include <stdio.h>

#include <windows.h>



LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

//
//  FUNCTION: WinMain()
//
//  PURPOSE: Main used by the Windows API to run Win32 programs.
//
//  COMMENTS:
//
//    This is the replacement for main seen in traditional C/C++ programs.
//    The Windows API will always be looking for a WinMain function, so it
//    can be treated as such.  The function params are a bit different, so if
//    your program requires their usage, the information can be found on MSDN.
//
int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR command_line, int show)
{
	int i = 0;
    States result;
    State level[2];
    State current;
	
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;

	wc.style = CS_HREDRAW | CS_VREDRAW;							/*Class style*/
	wc.lpfnWndProc = WinProc;									/*A function pointer which should point to the procedure function. Remember that the procedure function handles the window messages*/
	wc.cbClsExtra = 0;											/*The number of extra bytes you want to allocate for this window class structure. The default value is 0*/
	wc.cbWndExtra = 0;											/*The number of extra bytes you want to allocate for the window instance*/
	wc.hInstance = instance;									/*Instance of the module associated with the window. This is the 1st paramter passed to the WinMain function*/
	wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);					/*Handle to the icon class which will be displayed on the top left part of the window*/
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);					/*Handle to the cursor class which will be used in this window class*/
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		/*Handle to the class background brush. It can be a color value*/
	wc.lpszMenuName = NULL;										/*Pointer to a null terminated string which specifies the name of the menu resources used by this window class (if any)*/
	wc.lpszClassName = "Window Class Name";						/*String that specifies thw window class name. This is needed to create any window based on this window class*/

	RegisterClass(&wc);


	hWnd = CreateWindow(wc.lpszClassName,			/*The class name we chose for the window class*/
		"Win32 Sample",								/*The window caption*/
		WS_OVERLAPPEDWINDOW,						/*The style of the window, which determines if the window will have a minimize/maximize buttons, if its frame is thick or not.. */
		200,										/*The X position of the top left corner of the window. Remember that (0,0) is the top left of the monitor*/
		100,										/*The Y position of the top left corner of the window. Remember that (0,0) is the top left of the monitor*/
		640,										/*The width of the window*/
		480,										/*The heiht of the window*/
		NULL,										/*Handle to the parent window (in case this was a child window)*/
		NULL,										/*Handle to a menu (In case there is a menu for this window)*/
		instance,									/*Instance of the module associated with the window. This is the 1st paramter passed to the WinMain function*/
		NULL);										/*Pointer to a value sent to the window in the WM_CREATE message*/
	ShowWindow(hWnd, show);
	UpdateWindow(hWnd);

    System_Initialize();

    level[0] = (State)create_level1();
    level[1] = (State)create_level2();

    current = level[i];

    GSM_Initialize(current);

    /* It's gameloop time! */
    do
    {
        Input_Handle();
		
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
        
        result = GSM_RunFrame();

        switch (result)
        {
            case RESTART:
                GSM_Restart();
                break;
            case END:
                ++i;
                current = level[i];

                GSM_Update(level[i]); /* the heck is this for. */

                break;
			case ERROR:
				printf("An error occured!\n");
				break;
            default:
                break;
        }
    } while (result != QUIT);
    
    GSM_Exit();

    System_Exit();
	


	//---------------------------------------------------------------------------
	// Cleanup block.  In particular, the reason I added keep track of hWnd in
	//   the project was to call DestroyWindow here.  This safely deletes the
	//   window in the event that it has not been deleted elsewhere.
	//---------------------------------------------------------------------------
	if (hWnd)
		DestroyWindow(hWnd);

	return (int) msg.wParam;

	UnregisterClass(wc.lpszClassName, instance);

	return (int)msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	HDC dc;           /* device context */
	PAINTSTRUCT ps;   /* the paint struct */

	switch (msg)
	{
		/* when the window is created */
		case WM_CREATE:
			break;

		/* when the rectangle is drawn */
		case WM_LBUTTONDOWN:
			break;
		
		case WM_MOUSEMOVE:
			break;

		case WM_PAINT:
			dc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		/* When it's time for the window to be closed and removed */
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE)
				GSM_Signal(QUIT);// Quit the application by setting the next game state indicator to the QUIT "state"
			break;

		/* called any time the window is moved */
		case WM_MOVE:
			/* Invalidate the rect to force a redraw */
			InvalidateRect(hWnd, NULL, FALSE);
			break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}