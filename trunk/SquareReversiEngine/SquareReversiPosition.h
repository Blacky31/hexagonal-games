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

	typedef square_board_walker<8, 8, 0> wolker0;
	typedef square_board_walker<8, 8, 1> wolker1;
	typedef square_board_walker<8, 8, 2> wolker2;
	typedef square_board_walker<8, 8, 3> wolker3;

	SquareReversiPosition(player_type current_player)
		: game_board(current_player)
	{}

	// called from square_board_stone_successor_positions_iterator
	bool putStoneIfPossible(const engine::board_cell_coordinates& coordinates)
	{
		cell_type& current_cell = cell(coordinates);
		// test is it empty
		if(current_cell != cell_empty)
			return false;
		
		// try to walk in any direction and find opponent stone near (x,y) cell
		engine::board_cell_coordinates coord = coordinates;
		const player_type switched_player = switch_player(m_current_player); 

		// direction 0
		bool ok0 = false;
		if(wolker0::next_cell(coord))
		{
			// ok, it is inside the board
			// lets check content
			if(cell(coord) == switched_player)
			{
				//ok, lets find empty cell in this direction after opponent player stones
				while(wolker0::next_cell(coord))
				{
					cell_type& cell2 = cell(ccord);
					if(cell2 == cell_empty)
						break;
					if(cell2 == m_current_player)
					{
						ok0 = true;
						break;
					}
				}
				if(ok0)
				{
					// put new stone and change all stones to current player
					
				}
			}
			
		}
		// direction 1

		// direction 2

		// direction 3
	}
};

}} //square_reversi, game

}
#endif //__SQUARE_REVERSI_POSITION__H