#ifndef __SUUCCESSOR_POSITION_ITERATOR__H
#define __SUUCCESSOR_POSITION_ITERATOR__H

#include <boost/pool/singleton_pool.hpp>

#include "../Engine/BoardGeometry.h"

namespace game { namespace engine {

template<class POSITION>
class successor_positions_iterator
{
public:
	
	typedef POSITION position_type;
	typedef boost::singleton_pool<position_type, sizeof(position_type)> pool_type;

	successor_positions_iterator(const position_type& position) : 
		m_position(position), m_result_buffer(static_cast<position_type*>(pool_type::malloc())),
		m_current_coordinates(0,0)
	{}

	const position_type& operator* () const
	{
		return *m_result_buffer;
	}

	const position_type& operator-> () const
	{
		return *m_result_buffer;
	}

public:
	const position_type& m_position;
	position_type* m_result_buffer;
	board_cell_coordinates m_current_coordinates;
};


template<class POSITION, signed int X_SIZE, signed int Y_SIZE>
class square_board_stone_successor_positions_iterator : public successor_positions_iterator<POSITION>
{
public:

    typedef successor_positions_iterator<POSITION> base_type;
    typedef typename base_type::position_type position_type;
    
	square_board_stone_successor_positions_iterator(const position_type& position)
		: successor_positions_iterator<position_type>(position), m_isValid(true)
	{}

	operator bool () const
	{
		return m_isValid;
	}

	square_board_stone_successor_positions_iterator& operator++ ()
	{
		*successor_positions_iterator<position_type>::m_result_buffer = successor_positions_iterator<position_type>::m_position;
		while(true)
		{
			++ successor_positions_iterator<position_type>::m_current_coordinates.m_x;
			if(successor_positions_iterator<position_type>::m_current_coordinates.m_x >= X_SIZE)
			{
				successor_positions_iterator<position_type>::m_current_coordinates.m_x = 0;
				++ successor_positions_iterator<position_type>::m_current_coordinates.m_y;
				if(successor_positions_iterator<position_type>::m_current_coordinates.m_y >= Y_SIZE)
				{
					m_isValid = false;
					break;
				}
			}

			// is it possible to put stone in this cell?

			if(successor_positions_iterator<position_type>::m_result_buffer->putStoneIfPossible(successor_positions_iterator<position_type>::m_current_coordinates))
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
