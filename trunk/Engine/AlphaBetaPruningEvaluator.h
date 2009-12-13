#ifndef __MINIMAXEVALUATOR__H
#define __MINIMAXEVALUATOR__H

#include <boost/concept/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <map>

#include "BaseEvaluator.h"
#include "NativeEvaluator.h"
#include "CacheStrategy.h"

namespace game { namespace engine {

template<
	class POSITION, 
	template <class> class FINALLY_EVALUATOR,
	template <class> class CACHE_STRATEGY,
	template <class, template <class> class > class CACHE_STRATEGY_HELPER >

class alpha_beta_pruning_evaluator : public base_evaluator<POSITION, FINALLY_EVALUATOR, CACHE_STRATEGY>
{
public:

    typedef base_evaluator<POSITION, FINALLY_EVALUATOR, CACHE_STRATEGY> base_type;
    typedef typename base_type::position_type position_type;
    typedef typename base_type::position_evaluation_type position_evaluation_type;
    typedef typename base_type::cahce_strategy_type cahce_strategy_type;
    typedef typename base_type::successor_positions_iterator_type successor_positions_iterator_type;
    typedef typename base_type::position_cache_key_type position_cache_key_type;
    typedef typename base_type::cache_container_iterator_type cache_container_iterator_type;
    typedef typename base_type::finally_evaluator_type finally_evaluator_type;
	typedef CACHE_STRATEGY_HELPER<POSITION, CACHE_STRATEGY> cache_strategy_helper_type;

	position_evaluation_type f2(signed char depth, 
			const position_type& position, 
			const position_evaluation_type& alfa, 
			const position_evaluation_type& beta);

	position_evaluation_type g2(signed char depth, 
			const position_type& position, 
			const position_evaluation_type& alfa, 
			const position_evaluation_type& beta);

private:
	cahce_strategy_type m_cache_f;    
	cahce_strategy_type m_cache_g;    
};

template<
	class POSITION, 
	template <class> class FINALLY_EVALUATOR,
    template <class> class CACHE_STRATEGY,
	template <class, template <class> class > class CACHE_STRATEGY_HELPER >
	
	typename base_evaluator<POSITION, FINALLY_EVALUATOR, CACHE_STRATEGY>::position_evaluation_type 

	alpha_beta_pruning_evaluator<POSITION, FINALLY_EVALUATOR, CACHE_STRATEGY, CACHE_STRATEGY_HELPER>::
	f2(
		signed char depth, 
		const position_type& position, 
		const position_evaluation_type& alpha, 
		const position_evaluation_type& beta)
{
    position_evaluation_type result;
 
    cache_strategy_helper_type helper(position, depth, m_cache_f);
    bool need_return = helper.pre_evaluate(result);
    if(need_return)
        return result;
    
    if(!position->terminal_position_preanalize(result))
    {
        if(0 >= depth)
        {
            position_evaluation_type result = finally_evaluator_type::f(position);
        }
        else
        {
            result = alpha;
            successor_positions_iterator_type i(position);
            if(!i)
            {
                // it is terminal position
                result = position->terminal_position_evaluate();
            }
            else 
            { 
                for(; i; ++i)
                {
                    const position_type& i_position = *i;
                    position_evaluation_type t = 
                            g2(depth - 1, 
								i_position, 
								result, beta,
								m_cache);
                    if(t > result)
                        result = t;
                    if(result >= beta)
                        break;
                }
            }
        }
	}
    
    helper.post_evaluate(result);
    
	return result;
}


template<
	class POSITION, 
	template <class> class FINALLY_EVALUATOR,
    template <class> class CACHE_STRATEGY,
	template <class, template <class> class > class CACHE_STRATEGY_HELPER >
	
	typename base_evaluator<POSITION, FINALLY_EVALUATOR, CACHE_STRATEGY>::position_evaluation_type 
	
	alpha_beta_pruning_evaluator<POSITION, FINALLY_EVALUATOR, CACHE_STRATEGY, CACHE_STRATEGY_HELPER>::
	g2(
		signed char depth, 
		const position_type& position, 
		const position_evaluation_type& alpha, 
		const position_evaluation_type& beta)
{
    position_evaluation_type result;
 
    cache_strategy_helper_type helper(position, depth, m_cache_g);
    bool need_return = helper.pre_evaluate(result);
    if(need_return)
        return result;
    
    if(!position->terminal_position_preanalize(result))
    {
        if(0 >= depth)
        {
            position_evaluation_type result = finally_evaluator_type::f(position);
        }
        else
        {
            result = beta;
            successor_positions_iterator_type i(position);
            if(!i)
            {
                // it is terminal position
                result = position->terminal_position_evaluate();
            }
            else 
            { 
                for(; i; ++i)
                {
                    {
                        const position_type& i_position = *i;
                        position_evaluation_type t = 
                                f2(depth - 1, 
									i_position, 
									alpha, result,
									m_cache);
                        if(t < result)
                            result = t;
                        if(result <= alpha)
                            break;
                    }
                }
            }
        }
    }
	
    helper.post_evaluate(result);

	return result;
}

} } // namespace engine, namespace game


#endif //__MINIMAXEVALUATOR__H