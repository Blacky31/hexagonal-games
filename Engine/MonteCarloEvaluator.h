#ifndef __MONTECARLOEVALUATOR__H
#define __MONTECARLOEVALUATOR__H

#include "BaseEvaluator.h"

namespace game { namespace engine {

static unsigned int monte_carlo_repeat_count = 10000;

template<class POSITION>
class monte_carlo_evaluator : base_position_evaluator<POSITION>
{
public:

	static position_evaluation_type f(const position_type& position)
	{
		position_evaluation_type result = 0;

		for(unsigned int i = 0; i < repeat_count; ++i)
		{
			position_evaluation_type t = f_single(position);
			if(t > 0)
				++result;
			else if(t < 0)
				--result;
		}

		return result;
	}

private:

	static position_evaluation_type f_single(const position_type& position)
	{
		position_evaluation_type result;
		if(position.terminal_position_preanalize(result))
			return result;

		position_type p;
		bool can_generate_successor_position = position.random_successor_position(p);
		if(!can_generate_successor_position)
		{
			result = position.terminal_position_evaluate();
			return result;
		}

		return f(p);
	}
};

} } // namespace engine, namespace game


#endif // __MONTECARLOEVALUATOR__H