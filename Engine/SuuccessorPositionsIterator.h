#ifndef __SUUCCESSOR_POSITION_ITERATOR__H
#define __SUUCCESSOR_POSITION_ITERATOR__H

#include "boost/pool/singleton_pool.hpp"

#include "../Engine/BoardGeometry.h"

namespace game { namespace engine {

template<class POSITION>
class successor_positions_iterator
{
public:
	
	typedef POSITION position_type;
	typedef boost::singleton_pool<position_type, sizeof(position_type)> pool_type;

	successor_positions_iterator(const position_type& position) : 
		m_position(position), m_result_buffer(pool_type::malloc()),
		m_current_coordinates(0,0)
	{}

	const SquareReversiPosition& operator* () const
	{
		return *m_result_buffer;
	}

	const SquareReversiPosition& operator-> () const
	{
		return *m_result_buffer;
	}

protected:
	const SquareReversiPosition& m_position;
	SquareReversiPosition* m_result_buffer;

	board_cell_coordinates m_current_coordinates;
};


template<class POSITION, signed int X_SIZE, signed int Y_SIZE>
class square_board_stone_successor_positions_iterator : public successor_positions_iterator<POSITION>
{
public:

	square_board_stone_successor_positions_iterator(const position_type& position)
		: successor_positions_iterator(position), m_isValid(true)
	{}

	operator bool () const
	{
		return m_isValid;
	}

	square_board_stone_successor_positions_iterator& operator++ ()
	{
		*m_result_buffer = m_position;
		while(true)
		{
			++ m_current_coordinates.m_x;
			if(m_current_coordinates.m_x >= X_SIZE)
			{
				m_current_coordinates.m_x = 0;
				++ m_current_coordinates.m_y;
				if(m_current_coordinates.m_y >= Y_SIZE)
				{
					isValid = false;
					break;
				}
			}

			// is it possible to put stone in this cell?

			if(m_result_buffer->putStoneIfPossible(m_current_coordinates))
			{
				break;
			}
		}
		
		return *this;
	}

private:
	bool m_isValid;
};

}} // engine, game

#endif // __AQUARE_BOARDS_SUUCCESSOR_POSITION_ITERATOR__H
