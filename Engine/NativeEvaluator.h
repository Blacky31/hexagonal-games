#ifndef __NATIVEEVALUATOR__H
#define __NATIVEEVALUATOR__H

#include "BaseEvaluator.h"

namespace game { namespace engine {

template<class POSITION>
class native_evaluator : base_position_evaluator<POSITION>
{
public:

    typedef base_position_evaluator<POSITION> base_type;
    typedef typename base_type::position_type position_type;
    typedef typename base_type::position_evaluation_type position_evaluation_type;
    
	static position_evaluation_type f(const position_type& position)
	{
		return position.evaluate();
	}
};

} } // namespace engine, namespace game

#endif // __NATIVEEVALUATOR__H