#ifndef __BOARDGEOMETRY__H
#define __BOARDGEOMETRY__H

#include "boost/concept/assert.hpp"

#include "boost/intrusive/avl_set.hpp"

namespace game { namespace engine {

struct board_cell_coordinates 
{
	signed int m_x;
	signed int m_y;
};

template <signed int X_SIZE, signed int Y_SIZE, unsigned int DIRECTION>
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
template <signed int X_SIZE, signed int Y_SIZE>
class square_board_walker<X_SIZE, Y_SIZE, 0>
{
	static inline bool next_cell(board_cell_coordinates& cell)
	{
		++cell.y;
		return cell.y < Y_SIZE && cell.y >= 0 && cell.x >= 0 && cell.x < X_SIZE;
	}
};

template <signed int X_SIZE, signed int Y_SIZE>
class square_board_walker<X_SIZE, Y_SIZE, 1>
{
	static inline bool next_cell(board_cell_coordinates& cell)
	{
		--cell.x;
		return cell.x >= 0 && cell.x < X_SIZE && cell.y < Y_SIZE && cell.y >= 0;
	}
};

template <signed int X_SIZE, signed int Y_SIZE>
class square_board_walker<X_SIZE, Y_SIZE, 2>
{
	static inline bool next_cell(board_cell_coordinates& cell)
	{
		--cell.y;
		return cell.y >= 0 && cell.x >= 0 && cell.x < X_SIZE && cell.y < Y_SIZE;
	}
};

template <signed int X_SIZE, signed int Y_SIZE>
class square_board_walker<X_SIZE, Y_SIZE, 3>
{
	static inline bool next_cell(board_cell_coordinates& cell)
	{
		++cell.x;
		return cell.x < X_SIZE && cell.y < Y_SIZE && cell.y >= 0 && cell.x >= 0;
	}
};

} } // namespace engine, namespace game

#endif //__BOARDGEOMETRY__H