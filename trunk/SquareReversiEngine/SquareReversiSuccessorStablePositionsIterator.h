/*
 *  SquareReversiSuccessorStablePositionsIterator.h
 *  Game
 *
 *  Created by Viktor Zhuravel on 12/28/09.
 *
 */

#ifndef __SQUARE_REVERSI_SUCCESSOR_STABLE_POSITION_ITERATOR
#define __SQUARE_REVERSI_SUCCESSOR_STABLE_POSITION_ITERATOR

#include "SquareReversiPosition.h"

#include "../Engine/BoardGeometry.h"

namespace game { namespace square_reversi {

template <class POSITION, signed int SIZE>
class SquareReversiSuccessorStablePositionsIterator
{
public:

    typedef POSITION position_type;

	SquareReversiSuccessorStablePositionsIterator(const position_type& position)
		: m_current_coordinates(0, 0),
		  m_result_buffer(),
		  m_position(&position),
		  m_isValid(true),
		  m_move_was_generated(false)
	{
		next_position();
	}

    // there are no operators "==" , "!="
    // user's code should call "operator bool ()" instead of "!= end"
	inline operator bool () const
	{
		return isValid();
	}

    // I understabd, that operator++ should return reference to this, but here it is not needed
	inline void operator++ ()
	{
		if(isValid()) 
            next_position();
	}

	inline const position_type& operator* () const
	{
		return m_result_buffer;
	}

	inline const position_type& operator-> () const
	{
		return m_result_buffer;
	}

    inline void begin_on_position(const position_type& position)
    {
        m_position = &position;
        m_current_coordinates.m_x = 0;
        m_current_coordinates.m_y = 0;
        m_isValid = true;
        m_move_was_generated = false;

		next_position();
    }

private:

    inline bool isValid()
    {
        return m_isValid;
    }

    inline void next_position()
    {
        if(m_current_coordinates.m_y >= SIZE)
        {
            process_out_off_board();
            return;
        }

		if(m_current_coordinates.m_y == 0 || m_current_coordinates.m_y == (SIZE -1))
		{
			for(;true;++m_current_coordinates.m_x)
			{
				if(m_current_coordinates.m_x >= SIZE)
				{
					m_current_coordinates.m_x = 0;
					++m_current_coordinates.m_y;
					if(m_current_coordinates.m_y >= SIZE)
					{
						process_out_off_board();
						break;
					}
				}
	            
				if(process_in_board())
					break;
			}
		}
		else
		{
			if(m_current_coordinates.m_x == 0)
			{
				m_current_coordinates.m_x = (SIZE -1);
			}
			else
			{
				m_current_coordinates.m_x = 0;
				++m_current_coordinates.m_y;
			}

			if(process_in_board())
				break;
		}
    }

    inline void process_out_off_board()
    {
		m_isValid = false;
    }    

    // returns true if it is needed to break loop
	inline bool process_in_board()
    {
        // is it possible to put stone in this cell?
        unsigned char direction;
        bool isPossiblePutStone = m_position->isPossiblePutStone(m_current_coordinates, direction);
        if(isPossiblePutStone)
        {
            m_result_buffer = *m_position;
            m_result_buffer.putStone(m_current_coordinates, direction);
            m_result_buffer.switch_player();
            return true;
        }
        return false;
    }

private:
    engine::board_cell_coordinates m_current_coordinates;
    position_type m_result_buffer;
    const position_type* m_position;
	bool m_isValid;
};

}} // square_reversi, game

#endif // __SQUARE_REVERSI_SUCCESSOR_STABLE_POSITION_ITERATOR