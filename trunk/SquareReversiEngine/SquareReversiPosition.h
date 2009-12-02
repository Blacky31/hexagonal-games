#ifndef __SQUARE_REVERSI_POSITION__H
#define __SQUARE_REVERSI_POSITION__H

#include "../Engine/BoardGeometry.h"
#include "../Engine/GameBoard.h"
#include "../Engine/SuuccessorPositionsIterator.h"

namespace game { namespace square_reversi {

class SquareReversiPosition : public engine::game_board<8, 8, 2, unsigned short>
{
public:
	typedef signed int evaluation_type;
	typedef engine::square_board_stone_successor_positions_iterator<SquareReversiPosition, 8, 8> successor_positions_iterator_type;

	typedef engine::square_board_walker<8, 8, 0> wolker0;
	typedef engine::square_board_walker<8, 8, 1> wolker1;
	typedef engine::square_board_walker<8, 8, 2> wolker2;
	typedef engine::square_board_walker<8, 8, 3> wolker3;

	SquareReversiPosition(player_type current_player)
		: engine::game_board<8, 8, 2, unsigned short>(current_player)
	{}

    template<class WALKER>
    bool testCell(const engine::board_cell_coordinates startCoordinates)
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
					for(engine::board_cell_coordinates c = startCoordinates; c != coord; WALKER::next_cell(coord))
                    {
                        cell(coord) = m_current_player;
                    }
				}
			}
		}
        
        return ok;
    }

	// called from square_board_stone_successor_positions_iterator
	bool putStoneIfPossible(const engine::board_cell_coordinates& coordinates)
	{
		cell_type& current_cell = cell(coordinates);
		// test is it empty
		if(current_cell != cell_empty)
			return false;
		
        bool ok = false;
        
		// try to walk in any direction and find opponent stone near (x,y) cell
		// direction 0
        ok |= testCell<wolker0>(coordinates);
        
		// direction 1
        ok |= testCell<wolker1>(coordinates);

		// direction 2
        ok |= testCell<wolker2>(coordinates);

		// direction 3
        ok |= testCell<wolker3>(coordinates);
        
        return ok;
	}
    
    successor_positions_iterator_type successor_iterator_begin()
    {
        return successor_positions_iterator_type(*this);
    }
};

}} //square_reversi, game

#endif //__SQUARE_REVERSI_POSITION__H