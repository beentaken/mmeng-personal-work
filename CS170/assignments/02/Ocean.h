/******************************************************************************/
/*!
\file   Ocean.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Assignment #02
\date   February 10, 2010
\brief
  Implements functions required to adjust and track data in the "Ocean" that
  the WarBoats game uses.

Hours spent on this assignment: 1

Specific portions that gave you the most trouble:
  None.

*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef OCEAN_H
#define OCEAN_H
////////////////////////////////////////////////////////////////////////////////

#include "WarBoats.h"

namespace CS170
{
  namespace WarBoats
  {
    const int BOAT_LENGTH = 4;  // Length of a boat
    const int HIT_OFFSET = 100; // Add this to the boat ID

    class Ocean
    {
      public:
        
          /*
           * Other public methods
          */
	Ocean(int num_boats, int x_quadrants, int y_quadrants);
	~Ocean(void);

	ShotStats GetShotStats(void) const;
	ShotResult TakeShot(const Point &coordinate);
	BoatPlacement PlaceBoat(const Boat &boat);
     
           // Provided
        const int *GetGrid(void) const;
        Point GetDimensions(void) const;

      private:
        int *grid_;        // The 2D ocean
        int x_quadrants_;  // Ocean size along x-axis
        int y_quadrants_;  // Ocean size along y-axis
	Boat *boats_;
	int num_boats_;
	ShotStats stats_;
        
        /*
         * Other private data
        */
	
	int* get_grid_value(const int& x, const int& y);
        
    }; // class Ocean

  } // namespace WarBoats

} // namespace CS170

#endif // OCEAN_H
////////////////////////////////////////////////////////////////////////////////
