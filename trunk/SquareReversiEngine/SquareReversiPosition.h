#ifndef __SQUARE_REVERSI_POSITION__H
#define __SQUARE_REVERSI_POSITION__H

#include <limits>

#include "../Engine/BoardGeometry.h"
#include "../Engine/GameBoard.h"
#include "SquareReversiSuccessorPositionsIterator.h"
#include "SquareReversiSuccessorStablePositionsIterator.h"
#include "SquareReversiTransformPositionsIterator.h"

namespace game { namespace square_reversi {

class SquareReversiPosition 
    : public engine::square_game_board<8, 2 /* bits per cell in cache*/, unsigned short>,
      public engine::pass_counter<2 /* max 2 passes */>
{
public:
	typedef signed int evaluation_type;
	typedef SquareReversiSuccessorPositionsIterator<SquareReversiPosition, 8>
        successor_positions_iterator_type;

	typedef SquareReversiSuccessorStablePositionsIterator<SquareReversiPosition, 8>
        successor_stable_positions_iterator_type;

	typedef SquareReversiTransformPositionsIterator<SquareReversiPosition, 8>
		transformed_positions_iterator_type;

	typedef engine::square_board_walker<8, 8, 0> wolker0;
	typedef engine::square_board_walker<8, 8, 1> wolker1;
	typedef engine::square_board_walker<8, 8, 2> wolker2;
	typedef engine::square_board_walker<8, 8, 3> wolker3;

	SquareReversiPosition()
		: engine::square_game_board<8, 2, unsigned short>(cell_algorithm),
          engine::pass_counter<2>(),
          m_algorithmStonesOnBoard(0), m_opponentStonesOnBoard(0)
    {}

	SquareReversiPosition(player_type current_player)
		: engine::square_game_board<8, 2, unsigned short>(current_player),
          engine::pass_counter<2>(),
          m_algorithmStonesOnBoard(0), m_opponentStonesOnBoard(0)
	{}

    inline void putStoneInCell(cell_type& cell, const cell_type& newValue)
    {
        if(cell != newValue)
        {
            if(cell != cell_empty)
            {
                if(cell == cell_algorithm)
                    --m_algorithmStonesOnBoard;
                else
                    --m_opponentStonesOnBoard;
            }
        
            if(newValue == cell_algorithm)
                ++m_algorithmStonesOnBoard;
            else
                ++m_opponentStonesOnBoard;
                
            cell = newValue;
        }
    }

    template<class WALKER>
    inline bool testMoveToCellAndPutStone(const engine::board_cell_coordinates startCoordinates)
    {
		// try to walk in any direction and find opponent stone near (x,y) cell
		bool ok = false;
        engine::board_cell_coordinates coord = startCoordinates;
		if(WALKER::next_cell(coord))
		{
			// ok, it is inside the board
			// lets check content
			if(cell(coord) == m_switched_player)
			{
				//ok, lets find empty cell in this direction after opponent player stones
				while(WALKER::next_cell(coord))
				{
					cell_type& cell2 = cell(coord);
					if(cell2 == cell_empty)
						break;
					if(cell2 == m_current_player)
					{
						ok = true;
						break;
					}
				}
                if(ok)
                {
                    // put new stone and change all stones to current player
                    for(engine::board_cell_coordinates c = startCoordinates; c != coord; 
                           WALKER::next_cell(coord))
                    {
                        putStoneInCell(cell(coord), m_current_player);
                    }
                }
			}
		}
        
        return ok;
    }

    template<class WALKER>
    inline bool testMoveToCell(const engine::board_cell_coordinates startCoordinates) const
    {
		// try to walk in any direction and find opponent stone near (x,y) cell
		bool ok = false;
        engine::board_cell_coordinates coord = startCoordinates;
		if(WALKER::next_cell(coord))
		{
			// ok, it is inside the board
			// lets check content
			if(cell(coord) == m_switched_player)
			{
				//ok, lets find empty cell in this direction after opponent player stones
				while(WALKER::next_cell(coord))
				{
					const cell_type& cell2 = cell(coord);
					if(cell2 == cell_empty)
						break;
					if(cell2 == m_current_player)
					{
						ok = true;
						break;
					}
				}
			}
		}
        
        return ok;
    }

    inline bool isPossiblePutStone(const engine::board_cell_coordinates& coordinates,
        unsigned char& direction) const
    {
		const cell_type& current_cell = cell(coordinates);
		// test is it empty
		if(current_cell != cell_empty)
			return false;
            
		// try to walk in any direction and find opponent stone near (x,y) cell
		// direction 0
        if(testMoveToCell<wolker0>(coordinates))
        {
            direction = 0;
            return true;
        }
        
		// direction 1
        if(testMoveToCell<wolker1>(coordinates))
        {
            direction = 1;
            return true;
        }

		// direction 2
        if(testMoveToCell<wolker2>(coordinates))
        {
            direction = 2;
            return true;
        }

		// direction 3
        if(testMoveToCell<wolker3>(coordinates))
        {
            direction = 3;
            return true;
        }
        
        return false;
    }

	// called from square_board_stone_successor_positions_iterator
	inline void putStone(const engine::board_cell_coordinates& coordinates,
        unsigned char direction)
	{
		// try to walk in any direction and find opponent stone near (x,y) cell
        switch(direction)
        {
            case 0: testMoveToCellAndPutStone<wolker0>(coordinates);
            case 1: testMoveToCellAndPutStone<wolker1>(coordinates);
            case 2: testMoveToCellAndPutStone<wolker2>(coordinates);
            case 3: testMoveToCellAndPutStone<wolker3>(coordinates);
        }
	}
        
    inline bool terminal_position_preanalize(evaluation_type& result) const
    {
        if(is_pass_max() || 64 == (m_algorithmStonesOnBoard + m_opponentStonesOnBoard))
        {
            result = terminal_position_evaluate();
            return true;
        }
        
        return false;
    }    
    
    inline evaluation_type terminal_position_evaluate() const
    {
        evaluation_type result = 0;
        
        if(m_algorithmStonesOnBoard > m_opponentStonesOnBoard)
        {
            result = (std::numeric_limits<evaluation_type>::max)();
        }
        else if(m_algorithmStonesOnBoard < m_opponentStonesOnBoard)
        {
            result = (std::numeric_limits<evaluation_type>::min)();
        }

        return result;
    }
    
    inline evaluation_type evaluate() const
    {
        return m_algorithmStonesOnBoard - m_opponentStonesOnBoard;
    }
    
private:
    unsigned char m_algorithmStonesOnBoard;
    unsigned char m_opponentStonesOnBoard;
};

}} //square_reversi, game

#endif //__SQUARE_REVERSI_POSITION__H