/*
 *  SimpleCacheStrategyHelper.h
 *  Game
 *
 *  Created by Viktor Zhuravel on 12/6/09.
 *
 */

#ifndef __SIMPLE_CAHCE_STRATEGY_HELPER_H
#define __SIMPLE_CAHCE_STRATEGY_HELPER_H

#include "CacheStrategy.h"
#include "SimpleCacheStrategyHelper.h"

namespace game { namespace engine {

/*	
template <class POSITION,
	template <class> class CACHE_STRATEGY>
class simple_cache_strategy_helper;
*/
	
template <class POSITION,
	template <class> class CACHE_STRATEGY>
class simple_cache_strategy_helper
{
public:

    typedef CACHE_STRATEGY<POSITION> cache_strategy_type;
    typedef typename cache_strategy_type::position_type position_type;
    typedef typename position_type::cache_type position_cache_key_type;
    typedef typename position_type::evaluation_type position_evaluation_type;
    typedef typename cache_strategy_type::cache_container_iterator_type cache_container_iterator_type; 
    
    simple_cache_strategy_helper(const position_type& position, signed char depth,
        cache_strategy_type& cache_strategy)
        : m_position(position),
          m_depth(depth),
          m_cache_strategy(cache_strategy)
    { }
        
    // returns true if "return" from eveluate function is requared
    inline bool pre_evaluate(position_evaluation_type& result)
    {
        // !?!?!?!?!?!?!?!!?!?!?!?!?!?!?!?!?!?!?!?!?!
		//m_position.generate_cache_key(m_key);
        
        m_cache_was_found = m_cache_strategy.find_in_cache(m_key, m_i_cache);
        if(m_cache_was_found)
        {
            // Position was found in cache! So, return stored evaluation value
            signed char cache_on_depth = m_i_cache->m_depth;
            if(cache_on_depth >= m_depth)
            {
                result = m_i_cache->m_evaluated_value;
                return true;
            }
        }
        
        return false;
    }    

    inline void post_evaluate(const position_evaluation_type& result)
    {
        if(m_cache_was_found)
        {
            m_i_cache->m_depth = m_depth;
            m_i_cache->m_evaluated_value = result;
        }
        else
        {
            m_cache_strategy.add_to_cache(m_key, m_depth, result);
        }
    }

	
protected:
    const position_type& m_position;
    
	signed char m_depth;
    cache_strategy_type& m_cache_strategy;
    
	position_cache_key_type m_key;
	cache_container_iterator_type m_i_cache;
	bool m_cache_was_found;
};

template <class POSITION>
class simple_cache_strategy_helper<POSITION, no_cache_strategy>
{
public:

    typedef POSITION position_type;

    typedef no_cache_strategy<position_type> cache_strategy_type;
    typedef typename position_type::cache_type position_cache_key_type;
    typedef typename position_type::evaluation_type position_evaluation_type;
    typedef typename cache_strategy_type::cache_container_iterator_type cache_container_iterator_type; 
    
    simple_cache_strategy_helper(const position_type&, signed char, cache_strategy_type&)
    { }
    
    inline bool pre_evaluate(position_evaluation_type&)
    {
        return false;
    }
    
    inline void post_evaluate(const position_evaluation_type&)
    {
    }
};

}} // engine game

#endif //__SIMPLE_CAHCE_STRATEGY_HELPER_H
