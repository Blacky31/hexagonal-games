#ifndef __MINIMAXEVALUATOR__H
#define __MINIMAXEVALUATOR__H

#include "boost/concept/assert.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include "BaseEvaluator.h"
#include "NativeEvaluator.h"
#include "CacheStrategy.h"

namespace game { namespace engine {

template<
	class POSITION, 
	template <class> class FINALLY_EVALUATOR = native_evaluator<POSITION>,
	template <class> class CACHE_STRATEGY = cache_strategy<POSITION, true> >
class alpha_beta_pruning_evaluator : public base_evaluator<POSITION, FINALLY_EVALUATOR, CACHE_STRATEGY>
{
public:

	position_evaluation_type f2(signed char depth, 
			const position_type& position, 
			const position_evaluation_type& alfa, 
			const position_evaluation_type& beta);

	position_evaluation_type g2(signed char depth, 
			const position_type& position, 
			const position_evaluation_type& alfa, 
			const position_evaluation_type& beta);

private:
	cahce_strategy_type m_cache;
};

template<
	class POSITION, 
	template <class> class FINALLY_EVALUATOR>

static typename base_position_evaluator<POSITION>::position_evaluation_type 
	alpha_beta_pruning_evaluator<POSITION, FINALLY_EVALUATOR>::f2(
		signed char depth, 
		const position_type& position, 
		const position_evaluation_type& alfa, 
		const position_evaluation_type& beta)
{
	position_cache_key_type key;
	cache_container_iterator_type i_cache;
	bool cache_was_found;

	if(cahce_strategy_type::use_cache)
	{
		position.generate_cache_key(key);
		
		cache_was_found = m_cache->find_in_cache(key, i_cache);
		if(cache_was_found)
		{
			cache_was_found = true;
			// Position was found in cache! So, return stored evaluation value
			signed char cache_on_depth i_cache->m_depth;
			if(cache_on_depth >= depth)
				return i_cache->m_eveluated_value;
		}
	}

	position_evaluation_type result;
	if(0 == depth)
	{
		position_evaluation_type result = finally_evaluator_type::f(position);
	}
	else
	{
		result = alpha;
		for(position_successor_positions_enumerator_type i = position.successor_positions_begin();
				i != position.successor_positions_end(); ++i)
		{
			const position_type& i_position = *i;
			position_evaluation_type t = 
				alpha_beta_pruning_evaluator<position_type, finally_evaluator_type>::
					g2(depth - 1, 
					i_position, 
					result, beta,
					cache);
			if(t > result)
				result = t;
			if(result >= beta)
				break;
		}
	}
	
	if(cahce_strategy_type::use_cache)
	{
		if(cache_was_found)
		{
			i_cache->m_depth = depth;
			i_cache->m_eveluated_value = result;
		}
		else
		{
			m_cache->add_to_cache(key, depth, result);
		}
	}

	return result;
}


template<
	class POSITION, 
	template <class> class FINALLY_EVALUATOR>
static typename base_position_evaluator<POSITION>::position_evaluation_type 
	alpha_beta_pruning_evaluator<POSITION, FINALLY_EVALUATOR>::g2(
		signed char depth, 
		const position_type& position, 
		const position_evaluation_type& alfa, 
		const position_evaluation_type& beta)
{
	position_cache_key_type key;
	position.generate_cache_key(key);

	cache_container_iterator_type i_cache;
	bool cache_was_found = m_cache->find_in_cache(key, i_cache);
	if(cache_was_found)
	{
		cache_was_found = true;
		// Position was found in cache! So, return stored evaluation value
		signed char cache_on_depth i_cache->m_depth;
		if(cache_on_depth >= depth)
			return i_cache->m_eveluated_value;
	}

	position_evaluation_type result;
	if(0 == depth)
	{
		position_evaluation_type result = finally_evaluator_type::f(position);
	}
	else
	{
		result = beta;
		for(position_successor_positions_enumerator_type i = position.successor_positions_begin();
				i != position.successor_positions_end(); ++i)
		{
			const position_type& i_position = *i;
			position_evaluation_type t = 
				alpha_beta_pruning_evaluator<position_type, finally_evaluator_type>::
					f2(depth - 1, 
					i_position, 
					alpha, result,
					cache);
			if(t < result)
				result = t;
			if(result <= alpha)
				break;
		}
	}
	
	if(cache_was_found)
	{
		i_cache->m_depth = depth;
		i_cache->m_eveluated_value = result;
	}
	else
	{
		m_cache->add_to_cache(key, depth, result);
	}

	return result;
}

} } // namespace engine, namespace game


#endif //__MINIMAXEVALUATOR__H