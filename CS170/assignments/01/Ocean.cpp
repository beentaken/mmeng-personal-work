/******************************************************************************/
/*!
\file   Ocean.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS170
\par    Assignment #01
\date   February 3, 2010
\brief
  Implements functions required to adjust and track data in the "Ocean" that
  the WarBoats game uses.

Hours spent on this assignment: 3

Specific portions that gave you the most trouble:
  Mostly just debugging things. Small places where I made stupid mistakes.

*/
/******************************************************************************/

#include "WarBoats.h"
#include "Ocean.h"
#include <iostream> // cout, endl
#include <iomanip>  // setw

namespace
{
  /******************************************************************************/
  /*!
    \brief
      A simple function to help consistently get the value out of the grid.
    
    \param ocean
      The ocean containing the grid to work with.
      
    \param x
      x coordinates of the value to grab.
        
    \param y
      y coordinates of the value to grab.

    \return
      A pointer to the location on the grid.
  */
  /******************************************************************************/
  inline int* get_grid_value(CS170::WarBoats::Ocean &ocean, const int& x, const int& y)
  {
    return(&ocean.grid[y * ocean.x_quadrants + x]);
  }
}

namespace CS170
{
  namespace WarBoats
  {
    const int BOAT_LENGTH = 4;  // Length of a boat
    const int HIT_OFFSET = 100; // Add this to the boat ID
    

    /*
     * ALL STUDENT IMPLEMENTATION GOES HERE 
     */

    /******************************************************************************/
    /*!
      \brief
        Dynamically allocates and initializes a new Ocean.
      
      \param num_boats
        The number of boats this Ocean is meant to contain.
      
      \param x_quadrants
        How big the grid should be horizontally.
      
      \param y_quadrants
        How big the grid should be vertically.
        
      \return
        A pointer to the newly-created Ocean struct.
    */
    /******************************************************************************/
     Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants)
    {
      Ocean *newOcean = new Ocean;

      newOcean->grid = new int[x_quadrants * y_quadrants];

      newOcean->x_quadrants = x_quadrants;
      newOcean->y_quadrants = y_quadrants;

      newOcean->num_boats = num_boats;
      newOcean->boats = new Boat[num_boats];

      return(newOcean);
    }

    /******************************************************************************/
    /*!
      \brief
        Deallocates the specified Ocean struct and all members inside it.
      
      \param theOcean
        The ocean to deallocate.
    */
    /******************************************************************************/
    void DestroyOcean(Ocean *theOcean)
    {
      delete[] theOcean->grid;
      delete[] theOcean->boats;
      delete[] theOcean;
      theOcean = NULL;
    }

    /******************************************************************************/
    /*!
      \brief
        Places a given boat into the Ocean The boat is only placed if it can be
        fitted into a valid location.
      
      \param ocean
        The Ocean to place the boat into.
      
      \param boat
        The boat with the data that is to be inserted.
        
      \return
        bpREJECTED if there is an issue with the placement, bpACCEPTED otherwise.
    */
    /******************************************************************************/
    BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat)
    {
      // Perform edge checks.
      if (boat.position.x < 0 || boat.position.x > ocean.x_quadrants
       || boat.position.y < 0 || boat.position.y > ocean.y_quadrants)
      {
        return(bpREJECTED);
      }

      if ((boat.orientation == oHORIZONTAL &&
         ((boat.position.x + BOAT_LENGTH) > ocean.x_quadrants)))
      {
        return(bpREJECTED);
      }
      if ((boat.orientation == oVERTICAL &&
         ((boat.position.y + BOAT_LENGTH) > ocean.y_quadrants)))
      {
        return(bpREJECTED);
      }

      // Perform overlap checks.
      if (boat.orientation == oHORIZONTAL)
      {
        for (int i = 0; i < BOAT_LENGTH; i++)
        {
          if (*get_grid_value(ocean, boat.position.x + i,
        boat.position.y) != 0)
          {
            return(bpREJECTED);
          }
        }
      }
      else
      {
        for (int i = 0; i < BOAT_LENGTH; i++)
        {
          if (*get_grid_value(ocean, boat.position.x,
        boat.position.y + i) != 0)
          {
            return(bpREJECTED);
          }
        }
      }

      // All clear if it got here.
      if (boat.orientation == oHORIZONTAL)
      {
        for (int i = 0; i < BOAT_LENGTH; i++)
        {
          *get_grid_value(ocean, boat.position.x + i,
        boat.position.y) = boat.ID;
        }
      }
      else
      {
        for (int i = 0; i < BOAT_LENGTH; i++)
        {
          *get_grid_value(ocean, boat.position.x,
        boat.position.y + i) = boat.ID;
        }
      }

      ocean.boats[boat.ID].hits = 0;

      return(bpACCEPTED);
    }

    /******************************************************************************/
    /*!
      \brief
        Checks whether a shot is valid at the coordinates specified, and if so,
        handles it as appropriate.
      
      \param ocean
        The Ocean containing ships to hit.
      
      \param coordinate
        Where the shot hits in the Ocean.
      
      \return
        srILLEGAL if the shot is out of bounds, srDUPLICATE if the shot is fired
        at a position that already has been fired at, srMISS if the shot does not
        hit a ship, srHIT if the shot hits a ship but fails to sink it, and
        srSUNK otherwise.
    */
    /******************************************************************************/
     ShotResult TakeShot(Ocean &ocean, const Point &coordinate)
    {
      // Check edges.
      if (coordinate.x < 0 || coordinate.x > ocean.x_quadrants
    || coordinate.y < 0 || coordinate.y > ocean.y_quadrants)
      {
        return(srILLEGAL);
      }

      // Get the value for easy access.
      int gridvalue = *get_grid_value(ocean, coordinate.x, coordinate.y);

      // Miss test.
      if (gridvalue == 0)
      {
        ocean.stats.misses++;
        *get_grid_value(ocean, coordinate.x,
            coordinate.y) = -1;
        return(srMISS);
      }

      // Duplicate test.
      if (gridvalue == -1 || gridvalue > HIT_OFFSET)
      {
        ocean.stats.duplicates++;
        return(srDUPLICATE);
      }

      // If we're still here, it must've been a hit. Is it sunk?
      ocean.stats.hits++;
            ocean.boats[gridvalue].hits++;
      *get_grid_value(ocean, coordinate.x, coordinate.y) += HIT_OFFSET;

      if (ocean.boats[gridvalue].hits >= BOAT_LENGTH)
      {
        ocean.stats.sunk++;
        return(srSUNK);
      }


      return(srHIT);
    }

    /******************************************************************************/
    /*!
      \brief
        Gets the ShotStats struct containing information about how many shots and
        the results of the shots fired so far.
      
      \param ocean
        The Ocean containing the information requested.
      
      \return
        A struct containing hit/miss/illegal/duplicate shot information.
    */
    /******************************************************************************/
     ShotStats GetShotStats(const Ocean &ocean)
    {
      return(ocean.stats);
    }

    /******************************************************************************/
    /*!
      \brief
        Prints the grid (ocean) to the screen.
      
      \param ocean
        The Ocean to print
      
      \param field_width
        How much space each position takes when printed.
      
      \param extraline
        If true, an extra line is printed after each row. If false, no extra
        line is printed.
        
      \param showboats
        If true, the boats are shown in the output. (Debugging feature)
    */
    /******************************************************************************/
    void DumpOcean(const CS170::WarBoats::Ocean &ocean,
                                    int field_width, 
                                    bool extraline, 
                                    bool showboats)
    {
        // For each row
      for (int y = 0; y < ocean.y_quadrants; y++)
      {
          // For each column
        for (int x = 0; x < ocean.x_quadrants; x++)
        {
          int value = ocean.grid[y * ocean.x_quadrants + x];
    
            // Is it a boat?
          if ( (value > 0) && (value < HIT_OFFSET) && (showboats == false) )
            value = 0;
    
          std::cout << std::setw(field_width) << value;
        }
        std::cout << std::endl;
        if (extraline)
          std::cout << std::endl;
      }
    }

  } // namespace WarBoats
} // namespace CS170


