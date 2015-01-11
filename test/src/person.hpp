#ifndef NONSTD_TEST_PERSON_HPP
#define NONSTD_TEST_PERSON_HPP 1


#include <string>


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


#endif /* NONSTD_TEST_PERSON_HPP */
