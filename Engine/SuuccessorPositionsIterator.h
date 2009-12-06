#ifndef __SUUCCESSOR_POSITION_ITERATOR__H
#define __SUUCCESSOR_POSITION_ITERATOR__H

#include "../Engine/BoardGeometry.h"

/* this is crap */

/*

namespace game { namespace engine {


template<class POSITION>
class successor_positions_iterator_base
{
public:

	typedef POSITION position_type;

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

    inline bool isValid()
    {
        return m_isValid;
    }

public:
    const position_type* m_position;
	bool m_isValid;    
};

template<class POSITION, bool GENERATE_NEW_POSITION>
class successor_positions_iterator;

template<class POSITION>
class successor_positions_iterator<POSITION, true> : public successor_positions_iterator_base<POSITION>
{
public:
	
	typedef successor_positions_iterator_base<POSITION> base_type;
    typedef typename base_type::position_type position_type;

	inline const position_type& operator* () const
	{
		return m_result_buffer;
	}

	inline const position_type& operator-> () const
	{
		return m_result_buffer;
	}

public:
	position_type m_result_buffer;
};

template<class POSITION>
class successor_positions_iterator<POSITION, false>
// this partial specialization can be useful for calculating possible moves 
// without its generating 
{
public:
	typedef successor_positions_iterator_base<POSITION> base_type;
    typedef typename base_type::position_type position_type;
};

template<class POSITION, signed int X_SIZE, signed int Y_SIZE, bool GENERATE_NEW_POSITION> 
class square_board_stone_successor_positions_iterator : public successor_positions_iterator<POSITION, GENERATE_NEW_POSITION>
{
public:

    typedef successor_positions_iterator<POSITION, GENERATE_NEW_POSITION> base_type;
    typedef typename base_type::position_type position_type;

    using successor_positions_iterator<position_type, GENERATE_NEW_POSITION>::m_position;
    using successor_positions_iterator<position_type, GENERATE_NEW_POSITION>::m_isValid;
    using successor_positions_iterator<position_type, GENERATE_NEW_POSITION>::isValid;

    inline void begin_on_position(const position_type& position)
    {
        m_position = &position;
        m_current_coordinates.m_x = 0;
        m_current_coordinates.m_y = 0;
        m_isValid = true;
    }

    inline void next_position()
    {
        if(m_current_coordinates.m_y >= Y_SIZE)
        {
            process_out_off_board();
            return;
        }

		for(;true;++m_current_coordinates.m_x)
		{
			if(m_current_coordinates.m_x >= X_SIZE)
			{
				m_current_coordinates.m_x = 0;
				++m_current_coordinates.m_y;
				if(m_current_coordinates.m_y >= Y_SIZE)
				{
                    process_out_off_board();
					break;
				}
			}
            
            if(process_in_board())
                break;
		}
    }
    
private:
    board_cell_coordinates m_current_coordinates;
};

// PASS_SUPPORT: 0 - no pass, 1 - pass only if there are no other moves, 2 - pass in any position 
template<class POSITION, signed int X_SIZE, signed int Y_SIZE, 
    bool GENERATE_NEW_POSITION, unsigned char PASS_SUPPORT>
class square_board_stone_successor_positions_pass_support_iterator;

template<class POSITION, signed int X_SIZE, signed int Y_SIZE,
    bool GENERATE_NEW_POSITION>
class square_board_stone_successor_positions_pass_support_iterator
    <POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION, 0> 
    : square_board_stone_successor_positions_iterator<POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION>
{
public:
    inline void process_out_off_board()
    {
        m_isValid = false;
    }    
};

template<class POSITION, signed int X_SIZE, signed int Y_SIZE,
    bool GENERATE_NEW_POSITION>
class square_board_stone_successor_positions_pass_support_iterator
    <POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION, 1> 
    : square_board_stone_successor_positions_iterator<POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION>
{
public:
    inline void begin_on_position(const position_type& position)
    {
        square_board_stone_successor_positions_iterator::begin_on_position(position);
        m_move_was_generated = false;
    }

    inline void process_out_off_board()
    {
        if(!m_move_was_generated && m_position->is_pass_possible())
        {
            if(GENERATE_NEW_POSITION)
            {        
                m_result_buffer = *m_position;
                m_result_buffer.apply_pass();
                m_result_buffer.switch_player(); 
            }
        }
        else
        { 
            m_isValid = false;
        }
    }    

public:
    bool m_move_was_generated;
};

template<class POSITION, signed int X_SIZE, signed int Y_SIZE,
    bool GENERATE_NEW_POSITION>
class square_board_stone_successor_positions_pass_support_iterator
    <POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION, 2> 
    : square_board_stone_successor_positions_iterator<POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION>
{
public:
    inline void process_out_off_board()
    {
        if(m_position->is_pass_possible())
        {
            if(GENERATE_NEW_POSITION)
            {        
                m_result_buffer = *m_position;
                m_result_buffer.apply_pass();
                m_result_buffer.switch_player(); 
            }
        }
        else
        { 
            m_isValid = false;
        }
    }    
};

template<class POSITION, signed int X_SIZE, signed int Y_SIZE, 
    unsigned char PASS_SUPPORT, bool USE_DIRECTION>
class square_board_stone_successor_positions_pass_support_use_direction_iterator;

template<class POSITION, signed int X_SIZE, signed int Y_SIZE,
    bool GENERATE_NEW_POSITION, unsigned char PASS_SUPPORT>
class square_board_stone_successor_positions_pass_support_use_direction_iterator
    <POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION, PASS_SUPPORT, true> :
    square_board_stone_successor_positions_pass_support_iterator<POSITION, X_SIZE, Y_SIZE, 
            GENERATE_NEW_POSITION, PASS_SUPPORT>
    
{
    // returns true if it is needed to break loop
    inline bool process_in_board()
    {
        // is it possible to put stone in this cell?
        unsigned char direction;
        bool isPossiblePutStone = m_position->isPossiblePutStone(m_current_coordinates, direction);
        if(isPossiblePutStone)
        {
            if(GENERATE_NEW_POSITION)
            {        
                m_result_buffer = *m_position;
                m_result_buffer.putStone(m_current_coordinates, direction);
                m_result_buffer.switch_player();
            }
            return true;
        }
        return false;
    }
};

template<class POSITION, signed int X_SIZE, signed int Y_SIZE,
    bool GENERATE_NEW_POSITION, unsigned char PASS_SUPPORT>
class square_board_stone_successor_positions_pass_support_use_direction_iterator
    <POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION, PASS_SUPPORT, false> :
    square_board_stone_successor_positions_pass_support_iterator<POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION, PASS_SUPPORT>
    
{
    // returns true if it is needed to break loop
    inline bool process_in_board()
    {
        bool isPossiblePutStone = m_position->isPossiblePutStone(m_current_coordinates);
        if(isPossiblePutStone)
        {
            if(GENERATE_NEW_POSITION)
            {
                m_result_buffer = *m_position;
                m_result_buffer.putStone(m_current_coordinates);
                m_result_buffer.switch_player();
            }
            return true;
        }
        return false;
    }
};

template<class POSITION, signed int X_SIZE, signed int Y_SIZE,
        bool GENERATE_NEW_POSITION>
class square_board_stone_successor_positions_pass_support_use_direction_iterator
    <POSITION, X_SIZE, Y_SIZE, 1, true> :
    square_board_stone_successor_positions_pass_support_iterator<POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION, 1>
    
{
    // returns true if it is needed to break loop
    inline bool process_in_board()
    {
        // is it possible to put stone in this cell?
        unsigned char direction;
        bool isPossiblePutStone = m_position->isPossiblePutStone(m_current_coordinates, direction);
        if(isPossiblePutStone)
        {
            if(GENERATE_NEW_POSITION)
            {
                m_result_buffer = *m_position;
                m_result_buffer.putStone(m_current_coordinates, direction);
                m_result_buffer.switch_player();
            }
            m_move_was_generated = true;
            return true;
        }
        return false;
    }
};

template<class POSITION, signed int X_SIZE, signed int Y_SIZE,
        bool GENERATE_NEW_POSITION>
class square_board_stone_successor_positions_pass_support_use_direction_iterator
    <POSITION, X_SIZE, Y_SIZE, 1, false> :
    square_board_stone_successor_positions_pass_support_iterator<POSITION, X_SIZE, Y_SIZE, GENERATE_NEW_POSITION, 1>
    
{
    // returns true if it is needed to break loop
    inline bool process_in_board()
    {
        bool isPossiblePutStone = m_position->isPossiblePutStone(m_current_coordinates);
        if(isPossiblePutStone)
        {
            if(GENERATE_NEW_POSITION)
            {
                m_result_buffer = *m_position;
                m_result_buffer.putStone(m_current_coordinates);
                m_result_buffer.switch_player();
            }
            m_move_was_generated = true;
            return true;
        }
        return false;
    }
};
    
}} // engine, game
*/

#endif // __AQUARE_BOARDS_SUUCCESSOR_POSITION_ITERATOR__H
