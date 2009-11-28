#ifndef __BOARDGEOMETRY__H
#define __BOARDGEOMETRY__H

#include "boost/concept/assert.hpp"

#include "boost/intrusive/avl_set.hpp"

namespace game { namespace engine {

struct board_cell_position
{
	signed char m_x;
	signed char m_y;
};

template <signed char MAX_X, signed char MAX_Y, unsigned char DIRECTION>
class square_board_walker;

/*
square_board_walker directions
^ y		   0
|		   ^
|          |
|	   1<-   ->3
|	       |
|		   V
|		   2
|                   X
 ------------------->
next_cell return true if next cell is in board
*/
template <signed char MAX_X, signed char MAX_Y>
class square_board_walker<MAX_X, MAX_Y, 0>
{
	static bool next_cell(board_cell_position& cell)
	{
		++cell.y;
		return cell.y <= MAX_Y && cell.y >= 0 && cell.x >= 0 && cell.x <= NAX_X;
	}
};

template <signed char MAX_X, signed char MAX_Y>
class square_board_walker<MAX_X, MAX_Y, 1>
{
	static bool next_cell(board_cell_position& cell)
	{
		--cell.x;
		return cell.x >= 0 && cell.x <= NAX_X && cell.y <= MAX_Y && cell.y >= 0;
	}
};

template <signed char MAX_X, signed char MAX_Y>
class square_board_walker<MAX_X, MAX_Y, 2>
{
	static bool next_cell(board_cell_position& cell)
	{
		--cell.y;
		return cell.y >= 0 && cell.x >= 0 && cell.x <= NAX_X && cell.y <= MAX_Y;
	}
};

template <signed char MAX_X, signed char MAX_Y>
class square_board_walker<MAX_X, MAX_Y, 3>
{
	static bool next_cell(board_cell_position& cell)
	{
		++cell.x;
		return cell.x <= NAX_X && cell.y <= MAX_Y && cell.y >= 0 && cell.x >= 0;
	}
};

} } // namespace engine, namespace game

#endif //__BOARDGEOMETRY__H