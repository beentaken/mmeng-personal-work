/******************************************************************************/
/*!
\file   GameBoard.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #3
\date   2010-02-24
\brief  
  This is the header file for a class that can compute the solution
  to the Knight's Tour problem.

*/
/******************************************************************************/

//---------------------------------------------------------------------------
#ifndef GAMEBOARDH
#define GAMEBOARDH
//---------------------------------------------------------------------------

#include <vector>
#include <stdexcept>
#include <algorithm>

class BoardException : public std::exception
{
	private:
		int m_ErrCode;
		std::string m_Description;
	public:
		BoardException(int code, const std::string& error)
			:m_ErrCode(code), m_Description(error) {};

		virtual int code() const
		{
			return(m_ErrCode);
		}

		virtual const char* what() const throw()
		{
			return(m_Description.c_str());
		}

		virtual ~BoardException() throw()
		{
		}

		enum BOARD_EXCEPTION
		{
			E_OUT_OF_BOUNDS
		};
};

class GameBoard
{
  public:
    enum BoardMessage 
    {
      MSG_FINISHED_OK,   // finished and found a tour
      MSG_FINISHED_FAIL, // finished but no tour found
      MSG_ABORT_CHECK,   // checking to see if algorithm should continue
      MSG_PLACING,       // placing a knight on the board
      MSG_REMOVING       // removing a knight (back-tracking)
    };

    typedef bool (*KNIGHTS_CALLBACK)
      (const GameBoard& gb,  // the gameboard object itself
       const int *board,     // one-dimensional array
       BoardMessage message, // type of message
       unsigned move,        // the move number
       unsigned rows,        // number of rows in the board
       unsigned columns,     // number of columns in the board
       unsigned row,         // current row algorithm is accessing
       unsigned column       // current column algorithm is accessing
      );

    enum TourPolicy 
    {
      tpSTATIC,    // use a fixed set of offsets for next move
      tpHEURISTICS // use heuristics for next move
    };

      // Constructor/Destructor
    GameBoard(unsigned rows, unsigned columns, KNIGHTS_CALLBACK callback = NULL);
    ~GameBoard();

      // Starts the tour at row,column using specified tour policy
    bool KnightsTour(unsigned row, unsigned column, TourPolicy policy = tpSTATIC);
    unsigned GetMoves(void) const;        // the number of moves made
    TourPolicy GetTourPolicy(void) const; // the policy used to search
    int const *GetBoard(void) const;      // 1-D representation of board state

      // Debugging helpers
    int const *GetHTable(void) const;    // 1-D representation of heuristic table
    double const *GetDTable(void) const; // 1-D representation of distance table

  private:
    KNIGHTS_CALLBACK callback_;
    TourPolicy policy_;

	// Positional data.
	class Position
	{
		public:
			Position();
			Position(unsigned new_heuristic, unsigned new_distance);
    
			void setFilled(bool flag);
			bool getFilled() const;

			void setHeuristicValue(unsigned new_value);
			void setDistanceValue(double new_value);
			void setWalkedValue(int new_value);

			unsigned getHeuristicValue() const;
			double getDistanceValue() const;
			int getWalkedValue() const;
		private:
			bool filled_;
			unsigned heuristic_value_;
			double distance_value_;
			int walked_value_;
	};

	// A container more well-suited to how this class works.
	class GameBoardInternal
	{
		public:
			GameBoardInternal(unsigned rows, unsigned columns);

			Position& operator()(unsigned row, unsigned column) throw(BoardException);
			const Position& operator()(unsigned row, unsigned column) const throw(BoardException);
			unsigned getRows() const;
			unsigned getColumns() const;

			void reset();
		private:
			std::vector<Position> internal_board_;
			unsigned rows_;
			unsigned columns_;

			void generateHeuristicTable();
	};

	// First direction specifies which way to move two,
	// second direction moves one.
	// This allows us to iterate through directions, too.
	enum Direction
	{
		EN = 0,
		NE,
		NW,
		WN,
		WS,
		SW,
		SE,
		ES
	};

	class HeuristicSorter
	{
		const GameBoardInternal & board_;

		public:
			HeuristicSorter(const GameBoardInternal &board);
			bool operator()(const std::pair<unsigned, unsigned>& first, const std::pair<unsigned, unsigned>& second);
	};
	const int total_directions_;

	GameBoardInternal board_;
	unsigned move_;
	unsigned total_moves_;

	mutable int * flat_board_;
	mutable int * flat_heuristics_;
	mutable double * flat_distances_;

	void updateFlatBoard();
	void updateFlatHeuristics();
	void updateFlatDistances();
    
	// Other private fields and methods ...
	// Support functions.
	bool myPlaceKnight(const unsigned row, const unsigned column);
	bool bindMessage(BoardMessage message, const unsigned row, const unsigned col);
	bool preSweep(const unsigned row, const unsigned column);
	bool staticSweepNeighbors(const unsigned row, const unsigned column);
	bool heuristicSweepNeighbors(const unsigned row, const unsigned column);
	void updateHeuristicsTable(unsigned row, unsigned col, bool add);
	void postSweep(const unsigned row, const unsigned column);

	// Information gathering functions.
	unsigned getNewRow(unsigned row, const Direction dir) const;
	unsigned getNewColumn(unsigned column, const Direction dir) const;
	bool myCheckRelativePositionOpen(const unsigned row, const unsigned col, Direction dir) const throw(BoardException);
};

#endif  // GAMEBOARDH

