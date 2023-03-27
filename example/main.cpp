#include <iostream>

#include <long_arrow/long_arrow.hpp>


LONG_ARROW_GENERATE_OPERATOR_POST_DECREMENT(std::string)

constexpr std::string concat_const(const std::string& str, char c)
{
	return str + c;
}

constexpr void concat_mut(std::string& str, char c)
{
	str += c;
}

constexpr std::string concat_rvalue(std::string&& str, char c)
{
	return std::move(str += c);
}



int main()
{
	using long_arrow::operator>;

	{
		auto concat = LONG_ARROW_GENERATE_PROXY(concat_const);
		std::string str = "Hell";
		std::string res = str-->concat('o');
		std::cout << res << std::endl; // Hello
	}
	{
		auto concat = LONG_ARROW_GENERATE_PROXY(concat_mut);
		std::string str = "Hell";
		str-->concat('o');
		std::cout << str << std::endl;
	}
	{
		auto concat = LONG_ARROW_GENERATE_PROXY(concat_rvalue);
		std::string str = std::string("Hell")-->concat('o');
		std::cout << str << std::endl;
	}
}
