#ifndef __BOARDGEOMETRY__H
#define __BOARDGEOMETRY__H

#include <boost/concept/assert.hpp>
#include <boost/intrusive/avl_set.hpp>

namespace game { namespace engine {

struct board_cell_coordinates 
{
    board_cell_coordinates(signed int x, signed int y)
        : m_x(x), m_y(y)
    {}
	signed int m_x;
	signed int m_y;
};

bool operator != (const board_cell_coordinates& c1, const board_cell_coordinates& c2)
{
    return c1.m_x != c2.m_x || c1.m_y != c2.m_y;
}

bool operator == (const board_cell_coordinates& c1, const board_cell_coordinates& c2)
{
    return c1.m_x == c2.m_x && c1.m_y == c2.m_y;
}

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
public:
	static inline bool next_cell(board_cell_coordinates& cell)
	{
		++cell.m_y;
		return cell.m_y < Y_SIZE && cell.m_y >= 0 && cell.m_x >= 0 && cell.m_x < X_SIZE;
	}
};

template <signed int X_SIZE, signed int Y_SIZE>
class square_board_walker<X_SIZE, Y_SIZE, 1>
{
public:
	static inline bool next_cell(board_cell_coordinates& cell)
	{
		--cell.m_x;
		return cell.m_x >= 0 && cell.m_x < X_SIZE && cell.m_y < Y_SIZE && cell.m_y >= 0;
	}
};

template <signed int X_SIZE, signed int Y_SIZE>
class square_board_walker<X_SIZE, Y_SIZE, 2>
{
public:
	static inline bool next_cell(board_cell_coordinates& cell)
	{
		--cell.m_y;
		return cell.m_y >= 0 && cell.m_x >= 0 && cell.m_x < X_SIZE && cell.m_y < Y_SIZE;
	}
};

template <signed int X_SIZE, signed int Y_SIZE>
class square_board_walker<X_SIZE, Y_SIZE, 3>
{
public:
	static inline bool next_cell(board_cell_coordinates& cell)
	{
		++cell.m_x;
		return cell.m_x < X_SIZE && cell.m_y < Y_SIZE && cell.m_y >= 0 && cell.m_x >= 0;
	}
};

} } // namespace engine, namespace game

#endif //__BOARDGEOMETRY__H