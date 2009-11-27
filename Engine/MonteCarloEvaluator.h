#ifndef __MONTECARLOEVALUATOR__H
#define __MONTECARLOEVALUATOR__H

#include "BaseEvaluator.h"

namespace game { namespace engine {

template<class POSITION>
class monte_carlo_evaluator : base_position_evaluator<POSITION>
{
public:

	static position_evaluation_type f(const position_type& position)
	{
		
	}
};

} } // namespace engine, namespace game


#endif // __MONTECARLOEVALUATOR__H