#ifndef __BASEEVALUATOR__H
#define __BASEEVALUATOR__H

#include "boost/concept/assert.hpp"

#include "boost/intrusive/avl_set.hpp"

namespace game { namespace engine {

template<class POSITION>
class base_position_evaluator
{
public:
	typedef POSITION position_type;
	typedef typename position_type::cache_type position_cache_type;
	typedef typename position_type::evaluation_type position_evaluation_type;
	typedef typename position_type::successor_positions_enumerator_type 
			position_successor_positions_enumerator_type;
	
	BOOST_CONCEPT_ASSERT((Assignable<position_evaluation_type>));
	BOOST_CONCEPT_ASSERT((DefaultConstructible<position_evaluation_type>));
	BOOST_CONCEPT_ASSERT((SignedInteger<position_evaluation_type>));

	BOOST_CONCEPT_ASSERT((Assignable<position_cache_type>));
	BOOST_CONCEPT_ASSERT((DefaultConstructible<position_cache_type>));

	BOOST_STATIC_ASSERT((boost::is_class<position_type>::value));
};

template<class POSITION>
class base_position_evaluator_with_cache : public base_position_evaluator<POSITION>
{
public:
	struct cached_value_type : public boost::intrusive::avl_set_base_hook<>
	{
		position_cache_type m_key;
		signed char m_depth;

		position_evaluation_type m_evaluated_value;
		
		cached_value_type(const position_cache_type& key, 
			signed char depth, 
			position_evaluation_type evaluated_value)
			:	m_key(key),
				m_depth(depth), 
				m_evaluated_value(evaluated_value) {}

		friend bool operator< (const cached_value_type &a, const cached_value_type &b)
		{  return a.m_key < b.m_key; }		
	};

	typedef boost::intrusive::avl_set<cached_value_type, boost::intrusive::constant_time_size<false> > cache_container_type;
	typedef typename cache_container_type::iterator cache_container_iterator_type;
};

template<
	class POSITION, 
	template <class> class FINALLY_EVALUATOR>
class base_evaluator : public base_position_evaluator_with_cache<POSITION>
{
public:
	typedef FINALLY_EVALUATOR<position_type> finally_evaluator_type;
	typedef typename finally_evaluator_type::position_type finally_position_type;

	typedef typename finally_position_type::evaluation_type finally_evaluation_type;

	BOOST_CONCEPT_ASSERT((Convertible<finally_position_type, position_type>));
	BOOST_CONCEPT_ASSERT((Convertible<finally_evaluation_type, position_evaluation_type>));
};

} } // namespace engine, namespace game

#endif // __BASEEVALUATOR__H