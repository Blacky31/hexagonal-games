/*
 *  SquareReversiTransformPositionsIterator.h
 *  Game
 *
 *  Created by Viktor Zhuravel on 12/6/09.
 *
 */

#ifndef __SQUARE_REVERSI_TRANSFORM_POSITIONS_ITERATOR
#define __SQUARE_REVERSI_TRANSFORM_POSITIONS_ITERATOR

#include "SquareReversiPosition.h"

#include "../Engine/BoardGeometry.h"
#include "../Engine/SquareBoardTransformer.h"

namespace game { namespace square_reversi {

template <class POSITION, signed int SIZE>
class SquareReversiTransformPositionsIterator
{
public:

    typedef POSITION position_type;
    typedef typename position_type::cache_type cache_type;

	typedef engine::square_board_transformer<SIZE> square_board_transformer;
	typedef typename square_board_transformer::transfromation_function transfromation_function;
	
	SquareReversiTransformPositionsIterator(const position_type& position)
		: m_current_transformation_number(0),
		  m_cache_value(),
		  m_original_position(&position),
		  m_transformed_position(),
		  m_isValid(true)
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

	inline const cache_type& operator* () const
	{
		return m_cache_value;
	}

	inline const cache_type& operator-> () const
	{
		return m_cache_value;
	}

    inline void begin_on_position(const position_type& position)
    {
        m_original_position = &position;
        m_isValid = true;
        m_current_transformation_number = 0;

		next_position();
    }

private:

    inline bool isValid() const
    {
        return m_isValid;
    }

    inline void next_position()
    {
        if(m_current_transformation_number >= s_max_transformation_number)
        {
           m_isValid = false;
           return; 
        }
        
		transfromation_function fun = engine::square_board_transformer<SIZE>::get_function(m_current_transformation_number);

		engine::board_cell_coordinates coord(0, 0);

        for(coord.m_x = 0; coord.m_x < SIZE; ++coord.m_x)
			for(coord.m_y = 0; coord.m_y < SIZE; ++coord.m_y)
			{
				engine::board_cell_coordinates transformed_ccord = fun(coord);
				m_transformed_position.cell(transformed_ccord) = m_original_position->cell(coord);
			}
		
		// !?!?!?!?!?!?!?!?!!?!?
		//m_transformed_position.generate_cache_key(m_cache_value);

        ++m_current_transformation_number;
    }

    
private:
    unsigned int m_current_transformation_number; 
    cache_type m_cache_value;
	const position_type* m_original_position;
	position_type m_transformed_position;
	bool m_isValid;
    
    static const unsigned int s_max_transformation_number = 8;
};

}} // square_reversi, game

#endif // __SQUARE_REVERSI_TRANSFORM_POSITIONS_ITERATOR