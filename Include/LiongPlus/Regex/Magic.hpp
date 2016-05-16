// File: Magic.hpp
// Author: Rendong Liang (Liong)

#pragma once
#include "Regex.hpp"

struct BuggyRegex {};

template<char TC>
constexpr bool isSetIndicator()
{
	return TC == 'a' || TC == 'A' || TC == 'w' || TC == 'W' || TC == 's' || TC == 'S' || TC == 'd' || TC == 'D';
}

template<char TC>
struct DeterPack;
struct DeterPack<'a'> { typedef IsAlpha Type; };
struct DeterPack<'A'> { typedef NotAlpha Type; };
struct DeterPack<'w'> { typedef IsWord Type; };
struct DeterPack<'W'> { typedef NotWord Type; };
struct DeterPack<'s'> { typedef IsSpace Type; };
struct DeterPack<'S'> { typedef NotSpace Type; };
struct DeterPack<'d'> { typedef IsDigit Type; };
struct DeterPack<'D'> { typedef NotDigit Type; };

template<char TC>
constexpr DeterPack<TC>::Type getSet()
{
	return {};
}

template<char TC>
constexpr bool isReserved()
{
	return TC == '+' || TC == '*' || TC == '?' || TC == '\\' || TC == '{' || TC == '}' || TC == '[' || TC == ']' || TC == '(' || TC == ')' || TC == '^' || TC == '$' || TC == '|';
}

template<char TC>
constexpr bool isQuantifier()
{
	return TC == '+' || TC == '*' || TC == '?';
}

// Get the number until it comes a non-digit char.
template<char TC, char TElse>
constexpr size_t getNumber()
{
	if (int)
	return 
}


template<char TC>
struct QuantifierPack;
struct QuantifierPack<'+'> { typedef OnceOrMore Type; };
struct QuantifierPack<'*'> { typedef NeverOrMore Type; };
struct QuantifierPack<'?'> { typedef OnceOrNever Type; };

template<char TFirst, char ... TElse>
constexpr char getFirstChar()
{
	return TFirst;
}
template<char TFirst, char ... TElse>
constexpr ConstStrParser<TElse...> getFirstCharRemainder()
{
	return {};
}

template<char TFirst, char TSecond, char ... TElse>
constexpr char getSecondChar()
{
	return TSecond;
}
template<char TFirst, char TSecond, char ... TElse>
constexpr ConstStrParser<TElse...> getSecondCharRemainder()
{
	return {};
}

template<char TFirst, char TSecond, char TThird, char ... TElse>
constexpr char getThirdChar()
{
	return TThird;
}
template<char TFirst, char TSecond, char TThird, char ... TElse>
constexpr ConstStrParser<TElse...> getThirdCharRemainder()
{
	return {};
}

template<char TC, char ... TElse>
constexpr char findNextReserved()
{
	if (isReserved<TC>()) return TC;
	else return findNextReserved<TElse...>;
}

template<char TTarget, char ... TStr>
constexpr auto substrTill()
{
	if (getFirstChar<TStr...>() == '\0')
		return BuggyRegex;
	if (TTarget == getFirstChar<TStr...>())
		return ConstStrParser<>;
	else
		return ConstStrParser<getFirstChar<TStr...>(), substrTill<TTarget, getFirstCharRemainder<TStr...>()>::template>;
}

constexpr size_t makeNum(size_t num, char c)
{
	return num * 10 + (c - '0');
}
constexpr bool isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

// If the counter is limited, call this function
template<size_t TMin, size_t TMax, char ... TStr>
constexpr auto getRepCounterImplMax()
{
	if (!isDigit(getFirstChar<TStr...>()))
		return BuggyRegex;
	return getRepCounterImplMax<TMin, makeNum(TMax, getFirstChar<TStr...>()), TStr...>();
}
template<size_t TMin, size_t TMax>
constexpr auto getRepCounterImplMax<TMin, TMax>()
{
	return RepCounter<TMin, TMax>;
}

template<size_t TMin, char ... TStr>
constexpr auto getRepCounterImpl()
{
	if (!isDigit(getFirstChar<TStr...>()))
	{
		if (getFirstChar<TStr...>() == ',' && isDigit(getSecondChar<TStr...>()))
			return getRepCounterImplMax<TMin, 0, TStr...>();
		else
			return BuggyRegex;
	}
	return getRepCounterImpl<makeNum(TMin, getFirstChar<TStr...>()), TStr...>();
}
template<size_t TMin>
constexpr auto getRepCounterImpl<TMin>()
{
	return RepCounter<TMin, TMin>;
}

template<char ... TStr>
constexpr auto getRepCounter()
{
	switch (getFirstChar<TStr...>())
	{
	case '?':
		return OnceOrNever;
	case '+':
		return OnceOrMore;
	case '*':
		return NeverOrMore;
	case '{':
		if (getSecondChar<TStr>() == '\0')
			return BuggyRegex;
		return getRepCounterImpl<0>;
	default:
		return Once;
	}
}

template<char ... TStr>
constexpr auto analysisOr()
{
	// Escape
	if (getFirstChar<TStr...>() == '\\')
		return Match<>, analysisOr<getSecondCharRemainder<TStr...>()>();
	if (get)
	return analysisOr<>
}

template<char ... TStr>
constexpr auto analysisChain()
{
	
}

template<char ... TStr>
constexpr auto analysis()
{
	if (isReserved<TC>())
	{
		switch (TC)
		{
			case '(':
				analysis<substrTill<')', TElse>()>();
				break;
			case '[':
				analysis<substrTill<']', TElse>()>();
		}
	}
	else
		return Regex<analysis<>()>;
}

template<char ... TStr>
constexpr auto makeRegex()
{
	analysis<TStr ..., '\0', '\0'>();
}
