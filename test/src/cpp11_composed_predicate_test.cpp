#include <functional>

#include <gmock/gmock.h>

#include <predicate/composed_predicate.hpp>

#include "person.hpp"


using namespace ::testing;

namespace nonstd
{
namespace predicate
{


TEST(cpp11_composed_predicate_and,
	returns_false_when_one_of_different_type_predicates_is_not_satisfied)
{
	unsigned int drinking_age = 21;
	auto is_male_allowed_to_drink = make_composed_predicate<person>(
		std::bind2nd(std::mem_fun_ref(&person::is_older_than),
			drinking_age),
		std::mem_fun_ref(&person::is_male));

	person some_boy("male", 12);

	ASSERT_THAT(is_male_allowed_to_drink(some_boy), Eq(false));
}


} // namespace predicate.
} // namespace nonstd.
