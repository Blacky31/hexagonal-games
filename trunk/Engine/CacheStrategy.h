#ifndef __CAHCE_STRATEGY_H
#define __CAHCE_STRATEGY_H

#include <boost/concept/assert.hpp>
#include <boost/static_assert.hpp>

#include <boost/intrusive/avl_set.hpp>
#include <boost/pool/singleton_pool.hpp>

#include <boost/scoped_ptr.hpp>

#include <boost/foreach.hpp>

#include <memory>

namespace game { namespace engine {

template <class POSITION>
class base_cache_strategy
{
public:
    typedef POSITION position_type;

	typedef typename position_type::cache_type position_cache_key_type;
	typedef typename position_type::evaluation_type position_evaluation_type;

//	BOOST_CONCEPT_ASSERT((Assignable<position_cache_type>));
//	BOOST_CONCEPT_ASSERT((DefaultConstructible<position_cache_type>));

	struct cached_value_type : public boost::intrusive::avl_set_base_hook<>
	{
		position_cache_key_type m_key;
		signed char m_depth;

		position_evaluation_type m_evaluated_value;
		
		cached_value_type(const position_cache_key_type& key, 
			signed char depth, 
			position_evaluation_type evaluated_value)
			:	m_key(key),
				m_depth(depth), 
				m_evaluated_value(evaluated_value) {}

		friend bool compare_key_value (const position_cache_key_type& key, const cached_value_type& value)
		{  return key < value.m_key; }		
	};

	typedef boost::intrusive::avl_set<cached_value_type, boost::intrusive::constant_time_size<false> > cache_container_type;
	typedef typename cache_container_type::iterator cache_container_iterator_type;
};


template <class POSITION, bool USE_POOL>
class cache_strategy_with_allocator;

template <class POSITION>
class cache_strategy_with_allocator<POSITION, true> : public base_cache_strategy<POSITION>
{
public:
    typedef base_cache_strategy<POSITION> base_type;
    typedef typename base_type::cached_value_type cached_value_type;

	typedef boost::singleton_pool<base_cache_strategy<POSITION>, sizeof(cached_value_type)> pool_type;

	virtual ~cache_strategy_with_allocator()
	{
		pool_type::purge_memory();
	}

	static cached_value_type& alloc_cached_value()
	{
		return *static_cast<cached_value_type*>(pool_type::malloc());
	}
	
	static void dealloc_cached_value(cached_value_type*)
	{

	}
};

template <class POSITION>
class cache_strategy_with_allocator<POSITION, false> : public base_cache_strategy<POSITION>
{
public:

    typedef base_cache_strategy<POSITION> base_type;
    typedef typename base_type::cached_value_type cached_value_type;

	static cached_value_type& alloc_cached_value()
	{
		return *static_cast<cached_value_type*>(::operator new(sizeof(cached_value_type)));
	}

	static void dealloc_cached_value(cached_value_type* p_value)
	{
		::operator delete(sizeof(p_value));
	}
};

template <class POSITION, bool USE_POOL>
class cache_strategy : public cache_strategy_with_allocator<POSITION, USE_POOL>
{
public:

    typedef cache_strategy_with_allocator<POSITION, USE_POOL> base_type;
    typedef typename base_type::cache_container_type cache_container_type;
    typedef typename base_type::cached_value_type cached_value_type;
    typedef typename base_type::position_cache_key_type position_cache_key_type;
    typedef typename base_type::cache_container_iterator_type cache_container_iterator_type;

	BOOST_STATIC_CONSTANT(bool, use_cache = true);

	cache_strategy() : m_cache(new cache_container_type())
	{}

	~cache_strategy()
	{
		if(!USE_POOL)
		{
			BOOST_FOREACH(cached_value_type& i, *m_cache)
			{
				dealloc_cached_value(&i);
			}
		}
	}

	bool find_in_cache(const position_cache_key_type& key, cache_container_iterator_type& out_iterator)
	{
		out_iterator = m_cache->find(key, base_cache_strategy<POSITION>::compare_key_value);
		if(out_iterator == m_cache->end())
		{
			return false;
		}

		return true;
	}

	void add_to_cache(const position_cache_key_type& key, signed char depth, const cached_value_type& value)
	{
		cached_value_type& cache_value = base_type::alloc_cached_value();
		cache_value.m_key = key;
		cache_value.m_depth = depth;
		cache_value.m_cached_value = value;
		m_cache->insert(cache_value);
	}	

private:
	boost::scoped_ptr<cache_container_type> m_cache;
};

template<class POSITION> 
class boostpool_cache_strategy : public cache_strategy<POSITION, true>
{};

template<class POSITION> 
class stdnew_cache_strategy : public cache_strategy<POSITION, false>
{};

template <class POSITION>
class no_cache_strategy : public base_cache_strategy<POSITION>
{
public:

    typedef base_cache_strategy<POSITION> base_type;
    typedef typename base_type::position_cache_key_type position_cache_key_type;
    typedef typename base_type::cache_container_iterator_type cache_container_iterator_type;
    typedef typename base_type::cached_value_type cached_value_type;

	BOOST_STATIC_CONSTANT(bool, use_cache = false);

	inline bool find_in_cache(const position_cache_key_type&, cache_container_iterator_type&)
	{
		return false;
	}

	inline void add_to_cache(const position_cache_key_type& key, signed char, const cached_value_type&)
	{

	}
};

}} // engine, game

#endif // __CAHCE_STRATEGY_H