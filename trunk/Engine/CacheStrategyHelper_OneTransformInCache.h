/*
 *  CacheStrategyHelper_AllTransformsInCache.h
 *  Game
 *
 *  Created by Viktor Zhuravel on 12/6/09.
 *
 */

#ifndef __SIMPLE_CAHCE_STRATEGY_HELPER_ONE_TRANSFORM_IN_CACHE_H
#define __SIMPLE_CAHCE_STRATEGY_HELPER_ONE_TRANSFORM_IN_CACHE_H

#include "CacheStrategy.h"

namespace game { namespace engine {

template <class POSITION,
	template <class> class CACHE_STRATEGY>
class cache_strategy_helper_one_transfrom_in_cache;

template <class POSITION,
	template <class> class CACHE_STRATEGY>
class cache_strategy_helper_one_transfrom_in_cache 
	: simple_cache_strategy_helper<POSITION, CACHE_STRATEGY>
{
public:

	typedef simple_cache_strategy_helper<POSITION, CACHE_STRATEGY> base_type;

	typedef typename base_type::cache_strategy_type cache_strategy_type;
    typedef typename base_type::position_type position_type;
    typedef typename base_type::position_cache_key_type position_cache_key_type;
    typedef typename base_type::position_evaluation_type position_evaluation_type;
    typedef typename base_type::cache_container_iterator_type cache_container_iterator_type; 
    
	typedef typename position_type::transformed_positions_iterator_type transformed_positions_iterator_type;

    cache_strategy_helper_one_transfrom_in_cache(const position_type& position, signed char depth,
        cache_strategy_type& cache_strategy)
        : simple_cache_strategy_helper(position, depth, cache_strategy)
    { }
    
	using base_type::m_cache_was_found;
	using base_type::m_i_cache;
	using base_type::m_cache_strategy;
	using base_type::m_depth;

    // returns true if "return" from eveluate function is requared
    inline bool pre_evaluate(position_evaluation_type& result)
    {
		transformed_positions_iterator_type i(m_position);
		for(;i;++i)
		{
			m_key = *i;

			m_cache_was_found = m_cache_strategy->find_in_cache(m_key, m_i_cache);
			if(m_cache_was_found)
			{
				// Position was found in cache! So, return stored evaluation value
				signed char cache_on_depth = m_i_cache->m_depth;
				if(cache_on_depth >= m_depth)
				{
					result = m_i_cache->m_eveluated_value;
					return true;
				}

				break;
			}
		}

        return false;
    }    
};

template <class POSITION>
class cache_strategy_helper_one_transfrom_in_cache<POSITION, no_cache_strategy> : 
	simple_cache_strategy_helper<POSITION, no_cache_strategy>
{
public:

	typedef simple_cache_strategy_helper<POSITION, no_cache_strategy> base_type;

	typedef typename base_type::cache_strategy_type cache_strategy_type;
    typedef typename base_type::position_type position_type;
    typedef typename base_type::position_cache_key_type position_cache_key_type;
    typedef typename base_type::position_evaluation_type position_evaluation_type;
    typedef typename base_type::cache_container_iterator_type cache_container_iterator_type; 
    
    cache_strategy_helper_one_transfrom_in_cache(const position_type& position, signed char depth,
        cache_strategy_type& cache_strategy)
        : simple_cache_strategy_helper(position, depth, cache_strategy)
    { }    
};


}} // engine game

#endif // __SIMPLE_CAHCE_STRATEGY_HELPER_ONE_TRANSFORM_IN_CACHE_H