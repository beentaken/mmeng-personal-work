#ifdef _MSC_VER
#pragma warning(disable: 4702) // Suppress 'Unreachable code' due to the commented lines below
#endif

#include "GameBoard.h"
#include <time.h>
#include <stdio.h>

#include <cstdlib>  //exit

  // These values control the amount of output
namespace
{
  bool SHOW_BOARDS = false;
  bool SHOW_MESSAGES = false;
  bool PAUSE = false;
  bool SHOW_TIMINGS = true;
  bool SHOW_SOLUTION = false;
  bool SHOW_HTABLES = false;
  bool ABORTED = false;
}

void DumpBoard(int const *board, unsigned rows, unsigned columns)
{
  char ROWC[] = "----------";
  char ROWS[] = "|         ";
  unsigned cw = 5;
  ROWC[cw] = 0;
  ROWS[cw] = 0;

  for (unsigned r = 0; r < rows; r++)
  {
    for (unsigned i = 0; i < columns; i++)
      printf("%s", ROWC);
    printf("-\n");
    for (unsigned h = 0; h < 3; h++)
    {
      for (unsigned c = 0; c < columns; c++)
      {
        if (h == 1)
        {
          int value = board[r * columns + c];
          if (value != -1)
            printf("|%*d ", cw - 2, value);
          else
            printf("%s", ROWS);
        }
        else
        {
          printf("%s", ROWS);
        }
      }
      printf("|\n");
    }
  }
  for (unsigned i = 0; i < columns; i++)
    printf("%s", ROWC);
  printf("-\n");
}

void DumpBoardFlat(int const *board, unsigned rows, unsigned columns)
{
  for (unsigned r = 0; r < rows; r++)
  {
    for (unsigned c = 0; c < columns; c++)
    {
      int value = board[r * columns + c];
      if (value != -1)
        printf("%6i", value);
      else
        printf("      ");
    }
    printf("\n");
  }
}

void DumpBoardFlat(double const *board, unsigned rows, unsigned columns)
{
  for (unsigned r = 0; r < rows; r++)
  {
    for (unsigned c = 0; c < columns; c++)
    {
      double value = board[r * columns + c];
      printf(" %03.2f ", value);
    }
    printf("\n");
  }
}

void DumpBoard2(double const *board, unsigned rows, unsigned columns)
{
  char ROWC[] = "----------";
  char ROWS[] = "|         ";
  unsigned cw = 5;
  ROWC[cw] = 0;
  ROWS[cw] = 0;

  for (unsigned r = 0; r < rows; r++)
  {
    for (unsigned i = 0; i < columns; i++)
      printf("%s", ROWC);
    printf("-\n");
    for (unsigned h = 0; h < 3; h++)
    {
      for (unsigned c = 0; c < columns; c++)
      {
        if (h == 1)
        {
          double value = board[r * columns + c];
          if (value != -1)
            printf("|%2.1f ", value);
          else
            printf("%s", ROWS);
        }
        else
        {
          printf("%s", ROWS);
        }
      }
      printf("|\n");
    }
  }
  for (unsigned i = 0; i < columns; i++)
    printf("%s", ROWC);
  printf("-\n");
}

void DumpBoard2(int const *board, unsigned move, unsigned rows, unsigned columns, unsigned row, unsigned column, bool placing)
{
  char ROWC[] = "----------";
  char ROWS[] = "|         ";
  unsigned cw = 5;
  ROWC[cw] = 0;
  ROWS[cw] = 0;

  for (unsigned r = 0; r < rows; r++)
  {
    for (unsigned i = 0; i < columns; i++)
      printf("%s", ROWC);
    printf("-\n");
    for (unsigned h = 0; h < 3; h++)
    {
      for (unsigned c = 0; c < columns; c++)
      {
        if (h == 1)
        {
          int value = board[r * columns + c];

          char sign = placing ? '+' : '-';

          if (value != -1)
          {
            if (r == row && c == column)
              printf("|%*d%c", cw - 2, value, sign);
            else
              printf("|%*d ", cw - 2, value);
          }
          else
          {
            if (r == row && c == column)
              printf("|%*d%c", cw - 2, move, sign);
            else
              printf("%s", ROWS);
          }
        }
        else
        {
          printf("%s", ROWS);
        }
      }
      printf("|\n");
    }
  }
  for (unsigned i = 0; i < columns; i++)
    printf("%s", ROWC);
  printf("-\n");
}


void Pause(void)
{
  if (fgetc(stdin) == 'x')
  {
    printf("User abort.\n");
    ABORTED = 1;
    std::exit(1);
  }
}

bool Callback(const GameBoard& gb, const int *board, GameBoard::BoardMessage message, unsigned move, unsigned rows, unsigned columns, unsigned row, unsigned column)
{
  switch (message)
  {
    case GameBoard::MSG_PLACING:
      if (SHOW_MESSAGES)
        printf("Move: %i, Placing at %i,%i.\n", move, row + 1, column + 1);
      if (SHOW_BOARDS)
        DumpBoard2(board, move, rows, columns, row, column, true);
      if (SHOW_HTABLES)
        //DumpBoard2(gb.GetHTable(), move, rows, columns, row, column, true);
        DumpBoard(gb.GetHTable(), rows, columns);
        //DumpBoardFlat(gb.GetHTable(), rows, columns);
      break;
    case GameBoard::MSG_REMOVING:
      if (SHOW_MESSAGES)
        printf("Move: %i, Removing from %i,%i.\n", move, row + 1, column + 1);
      if (SHOW_BOARDS)
        DumpBoard2(board, move, rows, columns, row, column, false);
      break;
    case GameBoard::MSG_FINISHED_OK:
      if (move != rows * columns)
        printf("Tour found in %i moves. (Non-perfect)\n", move);
      else
        printf("Tour found in %i moves.\n", move);
      if (SHOW_SOLUTION)
        DumpBoard2(board, move, rows, columns, row, column, true);
      break;
    case GameBoard::MSG_FINISHED_FAIL:
      printf("No tour found after %i moves.\n", move);
      break;
    case GameBoard::MSG_ABORT_CHECK:
      return ABORTED;
    default:
      printf("Unknown message.");
  }

  if (PAUSE)
    Pause();

  return false;
}

void TestMessages(void)
{
  SHOW_BOARDS = 0;
  SHOW_MESSAGES = 1;
  GameBoard gb(5, 5, Callback);
  gb.KnightsTour(0, 0, GameBoard::tpHEURISTICS);
}

void TestBoards(unsigned low, unsigned high, GameBoard::TourPolicy search)
{
  for (unsigned r = low; r <= high; r++)
  {
    GameBoard gb(r, r, Callback);
    unsigned rows = r;
    unsigned cols = r;
    printf("\n************ Tour starting at: %u,%u\nBoard size %ux%u\n", 1, 1, rows, cols);

    if (search == GameBoard::tpHEURISTICS)
      printf("Policy: HEURISTICS\n");
    else
      printf("Policy: STATIC\n");

    time_t start = clock();
    bool tour = gb.KnightsTour(0, 0, search);
    time_t end = clock();
    if (SHOW_TIMINGS)
    {
      if (tour)
        printf("Tour found in %ld ms.\n", end - start);
      else
        printf("No tour found in %ld ms.\n", end - start);
    }
  }
}

void PrintDebug(void)
{
  int sizes[] = {5, 8, 10};
  int count = sizeof(sizes) / sizeof(*sizes);

  for (int i = 0; i < count; i++)
  {
    int value = sizes[i];
    GameBoard gb(value, value, 0);

    printf("Heuristic map for %ix%i:\n", value, value);
    int const *ht = gb.GetHTable();
    DumpBoard(ht, value, value);

    printf("Distance map for %ix%i:\n", value, value);
    double const *dt = gb.GetDTable();
    DumpBoard2(dt, value, value);
  }
}

void TestHeuristics(unsigned rows, unsigned cols, unsigned row, unsigned col)
{
  GameBoard gb(rows, cols, Callback);

  printf("\n************ Tour starting at: %u,%u\nBoard size %ux%u\n", row + 1, col + 1, rows, cols);

  printf("Policy: HEURISTICS\n");
  printf("Heuristics table:\n");
  DumpBoardFlat(gb.GetHTable(), rows, cols);
  printf("Distances table:\n");
  DumpBoardFlat(gb.GetDTable(), rows, cols);

  bool tour = gb.KnightsTour(row, col, GameBoard::tpHEURISTICS);
  if (tour)
  {
    printf("Board:\n");
    DumpBoardFlat(gb.GetBoard(), rows, cols);
  }
}

int main(void)
{
  //TestBoards(1, 8, GameBoard::tpSTATIC); 
  TestBoards(1, 8, GameBoard::tpHEURISTICS);
  //TestBoards(8, 8, GameBoard::tpSTATIC);
  //TestBoards(5, 5, GameBoard::tpSTATIC);
  //TestBoards(1, 20, GameBoard::tpHEURISTICS);
  //TestBoards(8, 20, GameBoard::tpHEURISTICS);
  //TestMessages();
  //PrintDebug();
  //TestHeuristics(6, 6, 0, 0);
  return 0;

  unsigned rows = 5;    
  unsigned cols = 5;    

  GameBoard* gb = new GameBoard(rows, cols, Callback);

  int count = 0;
  for (unsigned r = 1; r < rows; r++)
  {
    for (unsigned c = 2; c < cols; c++)
    {
      printf("\n************ Tour #%i starting at: %u,%u\nBoard size %ux%u\n", ++count, r + 1, c + 1, rows, cols);
      //GameBoard::TourPolicy search = GameBoard::tpHEURISTICS;
      GameBoard::TourPolicy search = GameBoard::tpSTATIC;

      if (search == GameBoard::tpHEURISTICS)
        printf("Policy: HEURISTICS\n");
      else
        printf("Policy: STATIC\n");

      //printf("Heuristics table:\n");
      //DumpBoardFlat(gb.GetHTable(), rows, cols);
      //printf("Distances table:\n");
      //DumpBoardFlat(gb.GetDTable(), rows, cols);

      time_t start = clock();
      bool tour = gb->KnightsTour(r, c, search);
      time_t end = clock();

      //if (tour)
        //DumpBoardFlat(gb.GetBoard(), rows, cols);

      if (SHOW_TIMINGS)
      {
        if (tour)
          printf("Tour found in %ld ms.\n", end - start);
        else
          printf("No tour found in %ld ms.\n", end - start);
      }
      break;
    }
    break;
  }
  delete gb;
  return 0;

}
