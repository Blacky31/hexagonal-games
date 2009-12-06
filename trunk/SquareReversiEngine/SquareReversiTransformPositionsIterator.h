/*
 *  SquareReversiTransformPositionsIterator.h
 *  Game
 *
 *  Created by Viktor Zhuravel on 12/6/09.
 *  Copyright 2009 Kring. All rights reserved.
 *
 */

#ifndef __SQUARE_REVERSI_TRANSFORM_POSITIONS_ITERATOR
#define __SQUARE_REVERSI_TRANSFORM_POSITIONS_ITERATOR

#include "SquareReversiPosition.h"

#include "BoardGeometry.h"

namespace game { namespace square_reversi {

template <class POSITION, signed int X_SIZE, signed int Y_SIZE>
class SquareReversiTransformPositionsIterator
{
public:

    typedef POSITION position_type;
    typedef typename position_type::cache_type cache_type;

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
		return m_cache_calue;
	}

	inline const cache_type& operator-> () const
	{
		return m_cache_calue;
	}

    inline void begin_on_position(const position_type& position)
    {
        m_position = &position;
        m_isValid = true;
        m_current_transformation_number = 0;
    }

private:

    inline bool isValid()
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
        
        
        
        ++m_current_transformation_number;
    }

    
private:
    unsigned int m_current_transformation_number; 
    cache_type m_cache_calue;
    const position_type* m_position;
	bool m_isValid;
    
    static const unsigned int s_max_transformation_number = 8;
    
    
};

}} // square_reversi, game

#endif // __SQUARE_REVERSI_TRANSFORM_POSITIONS_ITERATOR