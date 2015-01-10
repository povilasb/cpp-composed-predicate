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
 * one.
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
	void
	and_(const TPredicate1& predicate)
	{
		this->predicates1_.push_back(predicate);
	}


	/**
	 * Adds the specified predicate to composed predicate list. When
	 * operator()(TObject object) will be called, logical and will be applied
	 * to these predicates.
	 */
	void
	and_(const TPredicate2& predicate)
	{
		this->predicates2_.push_back(predicate);
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

} // namespace predicate.
} // namespace nonstd.


#endif /* NONSTD_PREDICATE_COMPOSED_PREDICATE_HPP */
