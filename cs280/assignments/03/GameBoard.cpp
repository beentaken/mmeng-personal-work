/******************************************************************************/
/*!
\file   GameBoard.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #3
\date   2010-02-24
\brief  
  This is the implementation file for a class that can compute the solution
  to the Knight's Tour problem.

Hours Spent: 7-8

  Fixing minor bugs was the worst part, the assignment as a whole was fairly
  straightforward.

  Microsoft C++ seems to like to complain about any usage of exceptions though,
  hope I won't be penalized too much for the warnings. Didn't manage to get
  rid of them, suspect a larger rewrite would be needed.

*/
/******************************************************************************/

#include "GameBoard.h"

#ifdef MARCUS_DEBUG
#include <iostream>
#endif


/*!\brief Constructs a new GameBoard with the given data.
 *
 * \param rows
 * 	The number of rows in the board.
 *
 * \param columns
 * 	The number of columns in the board.
 *
 * \param callback
 * 	A callback used to report the current status of the simulation to
 * 	an interested observer.
 */
GameBoard::GameBoard(unsigned rows, unsigned columns, KNIGHTS_CALLBACK callback)
:callback_(callback), total_directions_(8), board_(rows, columns), move_(0U), total_moves_(0U),
	flat_board_(new int[rows * columns]), flat_heuristics_(new int[rows * columns]),
	flat_distances_(new double[rows * columns])
{
	updateFlatDistances();
}

/*!\brief Cleans up the game board and associated data members.
 */
GameBoard::~GameBoard()
{
	delete[] flat_distances_;
	delete[] flat_heuristics_;
	delete[] flat_board_;
}

/*!\brief Starts a tour at the given initial position.
 *
 * \param row
 * 	The row to start at.
 *
 * \param column
 * 	The column to start at.
 *
 * \param policy
 * 	The policy to use.
 *
 * \return true if a tour is possible, false otherwise.
 */
bool GameBoard::KnightsTour(unsigned row, unsigned column, GameBoard::TourPolicy policy)
{
	policy_ = policy;

	board_.reset(); // Time for a clean run.
	move_ = 0;
	total_moves_ = 0;
	updateFlatHeuristics();

	// Start our tour de code~
	if(myPlaceKnight(row, column))
	{
		return(true);
	}
	else
	{
		// We have failed!
		updateFlatBoard();
		bindMessage(MSG_FINISHED_FAIL, row, column);
		return(false);
	}
}

/*!\brief Obtains the number of moves made.
 *
 * \return The number of moves made.
 */
unsigned GameBoard::GetMoves() const
{
	return(move_);
}

/*!\brief Obtains the current policy in use.
 *
 * \return The policy currently in use.
 */
GameBoard::TourPolicy GameBoard::GetTourPolicy() const
{
	return(policy_);
}

/*!\brief Gets a pointer to the board.
 *
 * \return A pointer to a constant representing the board.
 */
int const * GameBoard::GetBoard() const
{
	return(flat_board_);
}

/*!\brief Gets a pointer to the heuristic table.
 *
 * \return A pointer to a constant representing the heuristic table.
 */
int const * GameBoard::GetHTable() const
{
	return(flat_heuristics_);
}

/*!\brief Gets a pointer to the distance table.
 *
 * \return A pointer to a constant representing the distance table.
 */
double const * GameBoard::GetDTable() const
{
	return(flat_distances_);
}

/*****************************************************************************
 * Private member implementation.
 */

/**************************************
 * Sort functor.
 */

/*!\brief Constructs a sort functor associated with the provided board.
 *
 * \param board
 * 	The board to attach to the functor.
 */
GameBoard::HeuristicSorter::HeuristicSorter(const GameBoard::GameBoardInternal &board)
:board_(board)
{
}

/*!\brief Figures out whether the coordinates given in the arguments are in order.
 *
 * Priority: Lower heuristic value, ties broken by higher distance, ties broken
 * by arbitrary search order.
 *
 * \param first
 * 	The coordinates of the first Position to compare.
 *
 * \param second
 * 	The coordinates of the second Position to compare.
 *
 * \return true if the Position objects are in order, false otherwise.
 */
bool GameBoard::HeuristicSorter::operator()(const std::pair<unsigned, unsigned>& first, const std::pair<unsigned, unsigned>& second)
{
	if (board_(first.first, first.second).getHeuristicValue() < board_(second.first, second.second).getHeuristicValue())
	{
		return(true);
	}
	else if (board_(first.first, first.second).getHeuristicValue() > board_(second.first, second.second).getHeuristicValue())
	{
		return(false);
	}
	else
	{
		if (board_(first.first, first.second).getDistanceValue() >= board_(second.first, second.second).getDistanceValue())
		{
			return(true);
		}
	}

	return(false);
}

/**************************************
 * Position data.
 */

/*!\brief Constructs a piece of position data with sane default values.
 */
GameBoard::Position::Position()
:filled_(false), heuristic_value_(0), distance_value_(0), walked_value_(-1)
{
}

/*!\brief Constructs a piece of position data with the provided values.
 *
 * \param new_heuristic
 * 	The heuristic value for this position.
 *
 * \param new_distance
 * 	The distance value for this position.
 */
GameBoard::Position::Position(unsigned new_heuristic, unsigned new_distance)
:filled_(false), heuristic_value_(new_heuristic), distance_value_(new_distance), walked_value_(0)
{
}

/*!\brief Sets the heuristic value of the position to the given value.
 *
 * \param new_value
 * 	The value to set the position's heuristic data to.
 */
void GameBoard::Position::setHeuristicValue(unsigned new_value)
{
	heuristic_value_ = new_value;
}

/*!\brief Sets the distance value of the position to the given value.
 *
 * \param new_value
 * 	The value to set the position's distance data to.
 */
void GameBoard::Position::setDistanceValue(double new_value)
{
	distance_value_ = new_value;
}

/*!\brief Obtains the heuristic value of the current position.
 *
 * \return The heuristic value of the current position.
 */
unsigned GameBoard::Position::getHeuristicValue() const
{
	return(heuristic_value_);
}

/*!\brief Obtains the distance value of the current position.
 *
 * \return The distance value of the current position.
 */
double GameBoard::Position::getDistanceValue() const
{
	return(distance_value_);
}

/*!\brief Sets the position to a filled or unfilled state.
 *
 * Used to represent whether a knight exists on the current position.
 *
 * \param flag
 * 	The flag to set the position to.
 */
void GameBoard::Position::setFilled(bool flag)
{
	filled_ = flag;
}

/*!\brief Gets the filled status of the position.
 *
 * \return True if the position is filled, false otherwise.
 */
bool GameBoard::Position::getFilled() const
{
	return(filled_);
}

/*!\brief Sets the walked value of the position.
 *
 * The walked value represents where in the order of the tour
 * the knight passes over this spot.
 *
 * \param new_value
 * 	The value to set the position to.
 */
void GameBoard::Position::setWalkedValue(int new_value)
{
	walked_value_ = new_value;
}

/*!\brief Gets the walked value of the current position.
 *
 * \return The walked value of the current position. It is -1
 * if the knight does not pass over it.
 */
int GameBoard::Position::getWalkedValue() const
{
	return walked_value_;
}

/**************************************
 * GameBoardInternal stuff.
 */

/*!\brief Constructs an internal board class with the given dimensions.
 *
 * \param rows
 * 	The number of rows the board should have.
 *
 * \param columns
 * 	The number of columns the board should have.
 */
GameBoard::GameBoardInternal::GameBoardInternal(unsigned rows, unsigned columns)
:internal_board_(rows * columns), rows_(rows), columns_(columns)
{
	// Generate distances!
	//
	// Technically, would be faster to use a single iterator,
	// but since this is only done once total per board, I'm not
	// particularly worried about performance here.
	const unsigned center_x = columns_ / 2;
	const unsigned center_y = rows_ / 2;
	for(unsigned i = 0; i < rows_; ++i)
	{
		for(unsigned j = 0; j < columns_; ++j)
		{
			// Wussy pythag formula.
			// Don't bother with the sqrt, all we want
			// are the relative values anyways.
			// So this technically is a dot product?
			(*this)(i, j).setDistanceValue(
					(j - center_x) * (j - center_x)
					+ (i - center_y) * (i - center_y));
		}
	}
}

/*!\brief An overloaded function call operator to make accessing indices
 * in the board easier.
 *
 * \param row
 * 	The row to access.
 *
 * \param column
 * 	The column to access.
 *
 * \return A reference to the position held at the specified coordinates.
 */
GameBoard::Position& GameBoard::GameBoardInternal::operator()(unsigned row, unsigned column) throw(BoardException)
{
	// Make sure things don't explode!
	if (row >= getRows())
	{
		throw(BoardException(BoardException::E_OUT_OF_BOUNDS, "operator(): Specified row out of bounds."));
	}
	if (column >= getColumns())
	{
		throw(BoardException(BoardException::E_OUT_OF_BOUNDS, "operator(): Specified column out of bounds."));
	}

	// Okay, we're good. Moving on...
	std::vector<Position>::iterator iter = internal_board_.begin();

	advance(iter, row * columns_ + column);
	return(*iter);
}

/*!\brief A const version of the overloaded function call operator.
 *
 * \param row
 * 	The row to access.
 *
 * \param column
 * 	The column to access.
 *
 * \return a const reference to the position specified.
 */
const GameBoard::Position& GameBoard::GameBoardInternal::operator()(unsigned row, unsigned column) const throw(BoardException)
{
	// Second verse, same as the first.
	if (row >= getRows())
	{
		throw(BoardException(BoardException::E_OUT_OF_BOUNDS, "const operator(): Specified row out of bounds."));
	}
	if (column >= getColumns())
	{
		throw(BoardException(BoardException::E_OUT_OF_BOUNDS, "const operator(): Specified column out of bounds."));
	}

	std::vector<Position>::const_iterator iter = internal_board_.begin();

	advance(iter, row * columns_ + column);
	return(*iter);
}

/*!\brief Obtains the number of rows in the game board.
 *
 * \return The number of rows the game board contains.
 */
unsigned GameBoard::GameBoardInternal::getRows() const
{
	return(rows_);
}

/*!\brief Obtains the number of columns in the game board.
 *
 * \return The number of columns the game board contains.
 */
unsigned GameBoard::GameBoardInternal::getColumns() const
{
	return(columns_);
}

/*!\brief Resets the gameboard to a good starting state.
 *
 * Refills the heuristic table, and sets all the walked
 * values to a neutral value.
 */
void GameBoard::GameBoardInternal::reset()
{
	std::vector<Position>::iterator iter = internal_board_.begin();

	while (iter != internal_board_.end())
	{
		(*iter).setFilled(false);
		(*iter).setWalkedValue(-1);
		advance(iter, 1);
	}
	generateHeuristicTable();
}

/*!\brief Generates the table of heuristic values for use in
 * the tour algorithm.
 */
void GameBoard::GameBoardInternal::generateHeuristicTable()
{
	for (unsigned i = 0; i < getRows(); ++i)
	{
		for (unsigned j = 0; j < getColumns(); ++j)
		{
			(*this)(i, j).setHeuristicValue(2);

			if (i > 0 && i < getRows() - 1)
				(*this)(i,j).setHeuristicValue((*this)(i,j).getHeuristicValue()+1);
			if (j > 0 && j < getColumns() - 1)
				(*this)(i,j).setHeuristicValue((*this)(i,j).getHeuristicValue()+1);
			
			if (i > 1 && j > 1 && i < getRows() - 2 && j < getColumns() - 2)
				(*this)(i,j).setHeuristicValue((*this)(i,j).getHeuristicValue()+2);
			if (i > 1 && i < getRows() - 2)
				(*this)(i,j).setHeuristicValue((*this)(i,j).getHeuristicValue()+1);
			if (j > 1 && j < getColumns() - 2)
				(*this)(i,j).setHeuristicValue((*this)(i,j).getHeuristicValue()+1);
			if (i > 1  && i < getRows() - 2 && j <= getColumns() - 2 && (j == 1 || j == getColumns() - 2))
				(*this)(i,j).setHeuristicValue((*this)(i,j).getHeuristicValue()+1);
			if (j > 1 && j < getColumns() - 2 && i <= getRows() - 2 && (i == 1 || i == getRows() - 2))
				(*this)(i,j).setHeuristicValue((*this)(i,j).getHeuristicValue()+1);
		}
	}
}

/*!\brief Recursive function that runs one move of the tour.
 *
 * \param row
 * 	The row to check this once.
 *
 * \param column
 * 	The column to check this once.
 */
bool GameBoard::myPlaceKnight(const unsigned row, const unsigned column)
{
#ifdef MARCUS_DEBUG
	std::cerr << "Entered myPlaceKnight function." << std::endl;
#endif
	/* If preSweep is true, we have recieved an abort message, so get out.
	 */
	if (preSweep(row, column))
	{
		return(false);
	}
	
	// Early out if the board is, in fact, complete.
	if ((board_.getRows() * board_.getColumns()) == move_)
	{
		bindMessage(MSG_FINISHED_OK, row, column);
		return(true);
	}

	// If we're doing a static policy...
	if (policy_ == tpSTATIC)
	{
		if (staticSweepNeighbors(row, column))
		{
			// Hoho, we found something good.
			return(true);
		}
	}
	else // Well, only two options, so we're heuristic!
	{
		if (heuristicSweepNeighbors(row, column))
		{
			return(true);
		}
	}

	// Clean up for this particular iteration.
	postSweep(row, column);

	// If we made it this far, we can't have found anything interesting.
	return(false);
}

/*!\brief A simple binder function to remove a lot of the extra
 * parameters from the callback function.
 *
 * \param message
 * 	The message to signal to the callback.
 *
 * \param row
 * 	The row to pass to the callback.
 *
 * \param col
 * 	The column to pass to the callback.
 *
 * \return true if the callback needs the program to abort, false otherwise.
 */
bool GameBoard::bindMessage(BoardMessage message, const unsigned row, const unsigned col)
{
	if (callback_ != NULL)
	{
		updateFlatBoard();
		return(callback_(*this, GetBoard(), message, total_moves_, board_.getRows(), board_.getColumns(), row, col));
	}
	else
	{
		return(false);
	}
}

/*!\brief Prepares the current iteration for a tour sweep.
 *
 * Deals with allocating the knight, adjusting any relevant values,
 * and sending off the preperatory messages.
 *
 * \param row
 * 	The row to work in.
 *
 * \param column
 * 	The column to work in.
 *
 * \return true if the callback requests an abort, false otherwise.
 */
bool GameBoard::preSweep(const unsigned row, const unsigned column)
{
#ifdef MARCUS_DEBUG
	std::cerr << "Entered preSweep function." << std::endl;
#endif
	++move_;
	++total_moves_;
	// Place a knight.
	board_(row, column).setFilled(true);
	board_(row, column).setWalkedValue(move_);

	// Send placing message.
	bindMessage(MSG_PLACING, row, column);

	// Lastly, check for abort condition and send it back up
	// the stack.
	return(bindMessage(MSG_ABORT_CHECK, row, column));
}

/*!\brief Sweeps for tour locations using a static, naive algorithm.
 *
 * Is very slow for anything above approximately a 7x7 grid.
 *
 * \param row
 * 	The current row to start sweeping from.
 *
 * \param column
 * 	The current column to start sweeping from.
 *
 * \return true if a solution was found, false otherwise.
 */
bool GameBoard::staticSweepNeighbors(const unsigned row, const unsigned column)
{
	// Check for open positions...
	for (int i = 0; i < total_directions_; ++i)
	{
		try
		{
			// Too complicated to do a directional container.
			// So...
			// Cast i into the Direction enum.
			// Should do everything in order!
			if(myCheckRelativePositionOpen(row, column, Direction(i)))
			{
#ifdef MARCUS_DEBUG
				std::cerr << "Position is good, let's go..." << std::endl;
#endif
				// It's open, let's check that too!
				if(myPlaceKnight(getNewRow(row, Direction(i)), getNewColumn(column, Direction(i))))
				{
#ifdef MARCUS_DEBUG
					std::cerr << "Zomg, we're done!" << std::endl;
#endif
					return(true);
				}
			}
		}
		catch(BoardException &e)
		{
			// Do nothing. Or maybe debug stuff.
			// It was probably just an index going out of bounds,
			// which we shall ignore for now -- this should be safe,
			// and we will move on to the next iteration of this
			// loop with no issues.
#ifdef MARCUS_DEBUG
			std::cerr << e.what() << std::endl;
#endif
		}
	}

	return(false);
}

/*!\brief Performs a heuristic sweep of the tour locations.
 *
 * Significantly better performance than the static sweep.
 *
 * \param row
 * 	The row to start sweeping from.
 *
 * \param column
 * 	The column to start sweeping from.
 *
 * \return true if a solution was found, false otherwise.
 */
bool GameBoard::heuristicSweepNeighbors(const unsigned row, const unsigned column)
{
	// First, update the heuristics table to reflect our current position.
	updateHeuristicsTable(row, column, false);
	// So, we sweep the same way as the static, but use a heuristic sort
	// to cut down on the number of checks we have to do in the end.
	std::vector<std::pair<unsigned, unsigned> > new_coords;
	for (int i = 0; i < total_directions_; ++i)
	{
		try
		{
			if (myCheckRelativePositionOpen(row, column, Direction(i)))
			{
				// It's open, let's shove it into a box for further...
				// adjustments.
				new_coords.push_back(std::pair<unsigned, unsigned>(getNewRow(row, Direction(i)), getNewColumn(column, Direction(i))));
			}
		}
		catch (BoardException &)
		{
			// Do nothing! These should be safe errors.
		}
	}

	// We has a valid list of moves now.
	std::stable_sort(new_coords.begin(), new_coords.end(), HeuristicSorter(board_));

	// And now, chug through everything.
	std::vector<std::pair<unsigned, unsigned> >::iterator iter;

	for (iter = new_coords.begin(); iter != new_coords.end(); ++iter)
	{
		if (myPlaceKnight((*iter).first, (*iter).second))
			return(true);
	}

	// Reverse our heuristics changes.
	updateHeuristicsTable(row, column, true);

	return(false);
}

/*!\brief Either increments or decrements values in a heuristic table
 * to facilitate the heuristic sweep function.
 *
 * \param row
 * 	The row around which to modify the heuristic values.
 *
 * \param column
 * 	The column around which to modify heuristic values.
 *
 * \param add
 * 	Whether to deduct or add heuristic stats.
 */
void GameBoard::updateHeuristicsTable(unsigned row, unsigned column, bool add)
{
	for (int i = 0; i < total_directions_; ++i)
	{
		if (myCheckRelativePositionOpen(row, column, Direction(i)))
		{
			if (add)
			{
				board_(getNewRow(row, Direction(i)), getNewColumn(column, Direction(i)))
					.setHeuristicValue(board_(getNewRow(row, Direction(i)),
					getNewColumn(column, Direction(i))).getHeuristicValue()+1);
			}
			else
			{
				board_(getNewRow(row, Direction(i)), getNewColumn(column, Direction(i)))
					.setHeuristicValue(board_(getNewRow(row, Direction(i)),
					getNewColumn(column, Direction(i))).getHeuristicValue()-1);
			}
		}
	}
}

/*!\brief Cleans up the current iteration after a sweep.
 *
 * \param row
 * 	The row being swept from.
 *
 * \param column
 * 	The column being swept from.
 */
void GameBoard::postSweep(const unsigned row, const unsigned column)
{
	// Send removal message.
	bindMessage(MSG_REMOVING, row, column);
	// Clean up the knight we placed.
	board_(row, column).setFilled(false);
	--move_;
}

/*!\brief Checks whether a square in the specified direction is open.
 *
 * In theory, should this program return true for a position, that
 * position should both be a valid position, and not filled.
 *
 * \param row
 * 	The current row.
 *
 * \param col
 * 	The current column.
 *
 * \param dir
 * 	The direction relative to the current to check in.
 *
 * \return true of the square is open, false otherwise, or if it is
 * inaccessible for whatever reason.
 */
bool GameBoard::myCheckRelativePositionOpen(unsigned row, unsigned col, Direction dir) const
throw(BoardException)
{
	// Deal with row changes.
	if (dir == NE || dir == NW)
	{
		if (row < 2)
			return(false);
		row -= 2;
	}

	if (dir == WN || dir == EN)
	{
		if (row < 1)
			return(false);

		--row;
	}

	if (dir == SE || dir == SW)
	{
		if (row >= board_.getRows() - 2)
			return(false);

		row += 2;
	}

	if (dir == ES || dir == WS)
	{
		if (row >= board_.getRows() - 1)
			return(false);

		++row;
	}

	// Deal with column changes.
	if (dir == EN || dir == ES)
	{
		if (col >= board_.getRows() - 2)
			return(false);

		col += 2;
	}

	if (dir == NE || dir == SE)
	{
		if (col >= board_.getRows() - 1)
			return(false);

		++col;
	}

	if (dir == WN || dir == WS)
	{
		if (col < 2)
			return(false);

		col -= 2;
	}

	if (dir == NW || dir == SW)
	{
		if (col < 1)
			return(false);

		--col;
	}

	return(!board_(row, col).getFilled());
}

/*!\brief A helper function to assist in calculating movements
 * in the vertical direction.
 *
 * \param row
 * 	The row we are starting from.
 *
 * \param dir
 * 	The direction we are heading in.
 *
 * \return The new row we will be in.
 */
unsigned GameBoard::getNewRow(unsigned row, const Direction dir) const
{
	switch(dir)
	{
		case EN:
		case WN:
			--row;
			break;
		case NE:
		case NW:
			row-=2;
			break;
		case SW:
		case SE:
			row += 2;
			break;
		case WS:
		case ES:
			++row;
			break;
	}
	return(row);
}

/*!\brief A helper function to assist in calculating movements
 * in the horizontal direction.
 *
 * \param column
 * 	The column we are starting from.
 *
 * \param dir
 * 	The direction we are heading in.
 *
 * \return The new column we will be in.
 */
unsigned GameBoard::getNewColumn(unsigned column, const Direction dir) const
{
	switch(dir)
	{
		case EN:
		case ES:
			column += 2;
			break;
		case WN:
		case WS:
			column -= 2;
			break;
		case NW:
		case SW:
			--column;
			break;
		case NE:
		case SE:
			++column;
			break;
	}

	return(column);
}

/*!\brief Updates the flat, basic-array form of the board.
 */
void GameBoard::updateFlatBoard()
{
	for (unsigned i = 0; i < board_.getRows(); ++i)
	{
		for (unsigned j = 0; j < board_.getColumns(); ++j)
		{
#ifdef MARCUS_DEBUG
			std::cerr << "Updating flat board coords " << i << ' ' << j << std::endl;
			std::cerr << "Max rows: " << board_.getRows() << " Max Cols: " << board_.getColumns() << std::endl;
#endif
			flat_board_[i * board_.getColumns() + j] = board_(i, j).getWalkedValue();
		}
	}
}

/*!\brief Updates the flat, basic-array form of the heuristics table.
 */
void GameBoard::updateFlatHeuristics()
{	
	for (unsigned i = 0; i < board_.getRows(); ++i)
	{
		for (unsigned j = 0; j < board_.getColumns(); ++j)
		{
			flat_heuristics_[i * board_.getColumns() + j] = board_(i, j).getHeuristicValue();
		}
	}
}

/*!\brief Updates the flat, basic-array form of the distances table.
 */
void GameBoard::updateFlatDistances()
{	
	for (unsigned i = 0; i < board_.getRows(); ++i)
	{
		for (unsigned j = 0; j < board_.getColumns(); ++j)
		{
			flat_distances_[i * board_.getColumns() + j] = board_(i, j).getDistanceValue();
		}
	}
}

