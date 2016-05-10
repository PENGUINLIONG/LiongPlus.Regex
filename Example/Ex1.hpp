#include<iostream>
#include"../Include/LiongPlus/Regex/Regex.hpp"

void ex1()
{
    using namespace LiongPlus::Regex;
    // ((\w+:\/\/)[-a-zA-Z0-9:@;?&=\/%\+\.\*!'\(\),\$_\{\}\^~\[\]`#|]+)
    Regex<
        MatchChain<
            MatchFactor<
                Match<IsWord, OnceOrMore>,
                Match<SameToStr<_L_RX("://")>, Once>
            >,
            Once
        >,
        MatchOr<
            MatchFactor<
                Match<IsWord, Once>,
                Match<
                    SameToAny<'-', ':', '@', ';', '?', '&', '=', '/', '%', '+', '.', '*', '!', '\'', '(', ')', ',', '$', '_', '{', '}', '^', '~', '[', ']', '`', '#', '|'>,
                    Once
                >
            >,
        OnceOrNever
        >
    > regex;
    
    std::cout << (regex.Match("http://regexr.com/foo.html?q=bar") ? "true" : "false") << std::endl;
    std::cout << (regex.Match("foo@demo.net") ? "true" : "false") << std::endl;
}
