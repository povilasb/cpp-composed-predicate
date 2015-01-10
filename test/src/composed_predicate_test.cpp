#include <string>
#include <functional>

#include <gmock/gmock.h>

#include <predicate/composed_predicate.hpp>


using namespace ::testing;

class person;

class person {
public:
	person(const std::string& gender, unsigned int age) : gender_(gender),
		age_(age)
	{
	}

	bool
	is_adult() const
	{
		return this->age_ >= 18;
	}

	bool
	is_male() const
	{
		return this->gender_ == "male";
	}

	bool
	is_older_than(unsigned int age) const
	{
		return this->age_ > age;
	}


private:
	std::string gender_;
	unsigned int age_;
};


namespace nonstd
{
namespace predicate
{


TEST(composed_predicate_and, returns_true_when_all_predicates_satisfy)
{
	typedef std::const_mem_fun_ref_t<bool, person> predicate_type;
	composed_predicate<person, predicate_type> is_adult_male;

	is_adult_male.and_(std::mem_fun_ref(&person::is_adult));
	is_adult_male.and_(std::mem_fun_ref(&person::is_male));

	person me("male", 24);

	ASSERT_THAT(is_adult_male(me), Eq(true));
}


TEST(composed_predicate_and,
	returns_false_when_one_of_predicates_is_not_satisfied)
{
	typedef std::const_mem_fun_ref_t<bool, person> predicate_type;
	composed_predicate<person, predicate_type> is_adult_male;

	is_adult_male.and_(std::mem_fun_ref(&person::is_adult));
	is_adult_male.and_(std::mem_fun_ref(&person::is_male));

	person not_me("female", 24);

	ASSERT_THAT(is_adult_male(not_me), Eq(false));
}


TEST(composed_predicate_and,
	returns_true_when_all_different_type_predicates_satisfy)
{
	typedef std::const_mem_fun_ref_t<bool, person> predicate1_type;
	typedef std::binder2nd<std::const_mem_fun1_ref_t<bool, person,
		unsigned int> > predicate2_type;
	composed_predicate<person, predicate1_type, predicate2_type>
		is_male_allowed_to_drink;

	is_male_allowed_to_drink.and_(std::mem_fun_ref(&person::is_male));
	unsigned int drinking_age = 21;
	is_male_allowed_to_drink.and_(std::bind2nd(
		std::mem_fun_ref(&person::is_older_than), drinking_age));


	person me("male", 24);

	ASSERT_THAT(is_male_allowed_to_drink(me), Eq(true));
}


TEST(composed_predicate_and,
	returns_false_when_one_of_different_type_predicates_is_not_satisfied)
{
	typedef std::const_mem_fun_ref_t<bool, person> predicate1_type;
	typedef std::binder2nd<std::const_mem_fun1_ref_t<bool, person,
		unsigned int> > predicate2_type;

	composed_predicate<person, predicate1_type, predicate2_type>
		is_male_allowed_to_drink;

	unsigned int drinking_age = 21;
	is_male_allowed_to_drink
		.and_(std::bind2nd(std::mem_fun_ref(&person::is_older_than),
			drinking_age))
		.and_(std::mem_fun_ref(&person::is_male));


	person some_boy("male", 12);

	ASSERT_THAT(is_male_allowed_to_drink(some_boy), Eq(false));
}

} // namespace predicate.
} // namespace nonstd.
