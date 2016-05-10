#include<iostream>
#include"../Include/LiongPlus/Regex/Regex.hpp"

void ex2()
{
	using namespace LiongPlus::Regex;
	// [\?&](\w+)=(\w+)
	Regex<
		Match<SameToAny<'?', '&'>, Once>,
		Match<IsWord, OnceOrMore>,
		Match<SameTo<'='>, Once>,
		Match<IsWord, OnceOrMore>
	> regex;
	
	std::cout << (regex.Match("http://regexr.com/foo.html?q=bar&aaa=bv123d") ? "true" : "false") << std::endl;
	std::cout << (regex.Match("http://regexr.com/foo.html") ? "true" : "false") << std::endl;	
}