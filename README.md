# long_arrow
A little experimental library to achieve unified call syntax using the long arrow --> (operator -- combined with operator >). 

Here's an example of what you can do with it:
```C++
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
```

## Build
It uses CMake and a compiler compliant with C++20. The example needs gcc12, if you have an older version just remove the __constexpr__ from the examples and it should work.

## Add it to your project
It is a header only library with only one file, so just add the file __lib/long_arrow_long_arrow.hpp__ to your project else use something like [CPM](https://github.com/cpm-cmake/CPM.cmake) or [CMake's FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html).
