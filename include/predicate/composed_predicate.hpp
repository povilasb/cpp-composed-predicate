#ifndef NONSTD_PREDICATE_COMPOSED_PREDICATE_HPP
#define NONSTD_PREDICATE_COMPOSED_PREDICATE_HPP 1


#include <vector>


namespace nonstd
{
namespace predicate
{

/**
 * Composed predicate allows you to combine multiple predicates into single
 * one.
 */
template <typename TPredicate, typename TObject>
class composed_predicate {
public:
	/**
	 * Adds the specified predicate to composed predicate list. When
	 * operator()(TObject object) will be called, logical and will be applied
	 * to these predicates.
	 */
	void
	and_(const TPredicate& predicate)
	{
		this->predicates_.push_back(predicate);
	}


	bool
	operator()(const TObject& object) const
	{
		for (typename std::vector<TPredicate>::const_iterator it =
			this->predicates_.begin();
			it != this->predicates_.end(); ++it) {

			if ((*it)(object) != true) {
				return false;
			}

		}
		return true;
	}


private:
	std::vector<TPredicate> predicates_;
};

} // namespace predicate.
} // namespace nonstd.


#endif /* NONSTD_PREDICATE_COMPOSED_PREDICATE_HPP */
