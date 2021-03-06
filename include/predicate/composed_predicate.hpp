#ifndef NONSTD_PREDICATE_COMPOSED_PREDICATE_HPP
#define NONSTD_PREDICATE_COMPOSED_PREDICATE_HPP 1


#include <vector>


namespace nonstd
{
namespace predicate
{
namespace impl
{

/**
 * Default predicate always returning true.
 */
template <typename TObject>
struct default_predicate {
	bool
	operator()(const TObject&) const
	{
		return true;
	}
};


template <typename TPredicate, typename TObject>
bool
evaluate_predicates(const std::vector<TPredicate>& predicates,
	const TObject& object)
{
	for (typename std::vector<TPredicate>::const_iterator it =
		predicates.begin(); it != predicates.end(); ++it) {

		if ((*it)(object) != true) {
			return false;
		}
	}

	return true;
}

} // namespace impl.


/**
 * Composed predicate allows you to combine multiple predicates into single
 * one. Implements fluent interface, e.g.:
 *	composed_predicate.and_(predicate1).and_(predicate2);
 */
template <typename TObject, typename TPredicate1,
	typename TPredicate2 = impl::default_predicate<TObject> >
class composed_predicate {
public:
	/**
	 * Adds the specified predicate to composed predicate list. When
	 * operator()(TObject object) will be called, logical and will be applied
	 * to these predicates.
	 */
	composed_predicate<TObject, TPredicate1, TPredicate2>&
	and_(const TPredicate1& predicate)
	{
		this->predicates1_.push_back(predicate);
		return *this;
	}


	/**
	 * Adds the specified predicate to composed predicate list. When
	 * operator()(TObject object) will be called, logical and will be applied
	 * to these predicates.
	 */
	composed_predicate<TObject, TPredicate1, TPredicate2>&
	and_(const TPredicate2& predicate)
	{
		this->predicates2_.push_back(predicate);
		return *this;
	}


	bool
	operator()(const TObject& object) const
	{
		return impl::evaluate_predicates(this->predicates1_, object)
			&& impl::evaluate_predicates(this->predicates2_, object);
	}


private:
	std::vector<TPredicate1> predicates1_;
	std::vector<TPredicate2> predicates2_;
};


/**
 * Deduces predicate types from the specified arguments and creates appropriate
 * composed predicate. This factory is used when two different types of
 * predicates are used to compose predicates.
 */
template <typename TObject, typename TPredicate1, typename TPredicate2>
composed_predicate<TObject, TPredicate1, TPredicate2>
make_composed_predicate(const TPredicate1& predicate1,
	const TPredicate2& predicate2)
{
	composed_predicate<TObject, TPredicate1, TPredicate2> retval;
	retval.and_(predicate1).and_(predicate2);

	return retval;
}


/**
 * Deduces predicate type from the specified argument and creates appropriate
 * composed predicate. This factory is used only when one type of predicates
 * are used to compose predicates.
 */
template <typename TObject, typename TPredicate1>
composed_predicate<TObject, TPredicate1>
make_composed_predicate(const TPredicate1& predicate1)
{
	composed_predicate<TObject, TPredicate1> retval;
	retval.and_(predicate1);

	return retval;
}

} // namespace predicate.
} // namespace nonstd.


#endif /* NONSTD_PREDICATE_COMPOSED_PREDICATE_HPP */
