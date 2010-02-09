/*
 *  CacheStrategyHelper_AllTransformsInCache.h
 *  Game
 *
 *  Created by Viktor Zhuravel on 12/6/09.
 *
 */

#ifndef __SIMPLE_CAHCE_STRATEGY_HELPER_ALL_TRANSFORMS_IN_CACHE_H
#define __SIMPLE_CAHCE_STRATEGY_HELPER_ALL_TRANSFORMS_IN_CACHE_H

#include "CacheStrategy.h"
#include "SimpleCacheStrategyHelper.h"

namespace game { namespace engine {

/*
template <class POSITION,
	template <class> class CACHE_STRATEGY>
class cache_strategy_helper_all_transfroms_in_cache;
*/
 
template <class POSITION,
	template <class> class CACHE_STRATEGY>
class cache_strategy_helper_all_transfroms_in_cache 
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

    cache_strategy_helper_all_transfroms_in_cache(const position_type& position, signed char depth,
        cache_strategy_type& cache_strategy)
        : base_type(position, depth, cache_strategy)
    { }
    
	using base_type::m_cache_was_found;
	using base_type::m_i_cache;
	using base_type::m_cache_strategy;
	using base_type::m_depth;
	using base_type::m_position;

	inline bool pre_evaluate(position_evaluation_type& result)
    {
		return base_type::pre_evaluate(result);
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
			transformed_positions_iterator_type i(m_position);
			for(;i;++i)
			{
				const position_cache_key_type& key = *i;
				m_cache_strategy.add_to_cache(key, m_depth, result);
			}
        }
    }
};

template <class POSITION>
class cache_strategy_helper_all_transfroms_in_cache<POSITION, no_cache_strategy> : 
	simple_cache_strategy_helper<POSITION, no_cache_strategy>
{
public:

	typedef simple_cache_strategy_helper<POSITION, no_cache_strategy> base_type;

	typedef typename base_type::cache_strategy_type cache_strategy_type;
    typedef typename base_type::position_type position_type;
    typedef typename base_type::position_cache_key_type position_cache_key_type;
    typedef typename base_type::position_evaluation_type position_evaluation_type;
    typedef typename base_type::cache_container_iterator_type cache_container_iterator_type; 
    
    cache_strategy_helper_all_transfroms_in_cache(const position_type& position, signed char depth,
        cache_strategy_type& cache_strategy)
        : base_type(position, depth, cache_strategy)
    { }
    
    inline bool pre_evaluate(position_evaluation_type& result)
    {
		return base_type::pre_evaluate(result);
	}	
	
	inline void post_evaluate(const position_evaluation_type& result)
	{
		base_type::post_evaluate(result);
	}
};


}} // engine game

#endif // __SIMPLE_CAHCE_STRATEGY_HELPER_ALL_TRANSFORMS_IN_CACHE_H