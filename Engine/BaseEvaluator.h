#ifndef __BASEEVALUATOR__H
#define __BASEEVALUATOR__H

#include <boost/concept/assert.hpp>
#include <boost/static_assert.hpp>

namespace game { namespace engine {

template<class POSITION>
class base_position_evaluator
{
public:
	typedef POSITION position_type;
	typedef typename position_type::evaluation_type position_evaluation_type;
	typedef typename position_type::successor_positions_iterator_type 
			successor_positions_iterator_type;
            
            
//	BOOST_CONCEPT_ASSERT((boost::concept::Assignable<position_evaluation_type>));
//	BOOST_CONCEPT_ASSERT((DefaultConstructible<position_evaluation_type>));
//	BOOST_CONCEPT_ASSERT((SignedInteger<position_evaluation_type>));

	BOOST_STATIC_ASSERT((boost::is_class<position_type>::value));
};

template<
	class POSITION, 
	template <class> class FINALLY_EVALUATOR,
	template <class> class CACHE_STRATEGY>
class base_evaluator : public base_position_evaluator<POSITION>
{
public:

    typedef base_position_evaluator<POSITION> base_type;

	typedef typename base_type::position_type position_type;
	typedef typename base_type::position_evaluation_type position_evaluation_type;
	typedef typename base_type::successor_positions_iterator_type successor_positions_iterator_type;    

	typedef FINALLY_EVALUATOR<position_type> finally_evaluator_type;
	typedef typename finally_evaluator_type::position_type finally_position_type;
	typedef typename finally_position_type::evaluation_type finally_evaluation_type;

	typedef CACHE_STRATEGY<position_type> cahce_strategy_type;
	typedef typename cahce_strategy_type::cache_container_iterator_type cache_container_iterator_type;
	typedef typename cahce_strategy_type::position_cache_key_type position_cache_key_type;

//	BOOST_CONCEPT_ASSERT((Convertible<finally_position_type, position_type>));
//	BOOST_CONCEPT_ASSERT((Convertible<finally_evaluation_type, position_evaluation_type>));
};

} } // namespace engine, namespace game

#endif // __BASEEVALUATOR__H