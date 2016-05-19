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
constexpr char get1st()
{
	return TFirst;
}
template<char TFirst, char ... TElse>
constexpr ConstStrParser<TElse...> get1stRemainder()
{
	return {};
}

template<char TFirst, char TSecond, char ... TElse>
constexpr char get2nd()
{
	return TSecond;
}
template<char TFirst, char TSecond, char ... TElse>
constexpr ConstStrParser<TElse...> get2ndRemainder()
{
	return {};
}

template<char TFirst, char TSecond, char TThird, char ... TElse>
constexpr char get3rd()
{
	return TThird;
}
template<char TFirst, char TSecond, char TThird, char ... TElse>
constexpr ConstStrParser<TElse...> get3rdRemainder()
{
	return {};
}

template<char TFirst, char TSecond, char TThird, char TFourth, char ... TElse>
constexpr char get4th()
{
	return TFourth;
}
template<char TFirst, char TSecond, char TThird, char TFourth, char ... TElse>
constexpr ConstStrParser<TElse...> get4thRemainder()
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
	if (get1st<TStr...>() == '\0')
		return BuggyRegex;
	if (TTarget == get1st<TStr...>())
		return ConstStrParser<>;
	else
		return ConstStrParser<get1st<TStr...>(), substrTill<TTarget, get1stRemainder<TStr...>()>::template>;
}
template<char TTarget, char ... TStr>
constexpr auto substrAfter()
{
	if (get1st<TStr...>() == '\0')
		return BuggyRegex;
	if (TTarget == get1st<TStr...>())
		return ConstStrParser<get1stRemainder<TStr...>()>;
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
	if (!isDigit(get1st<TStr...>()))
		return BuggyRegex;
	return getRepCounterImplMax<TMin, makeNum(TMax, get1st<TStr...>()), TStr...>();
}
template<size_t TMin, size_t TMax>
constexpr auto getRepCounterImplMax<TMin, TMax>()
{
	return RepCounter<TMin, TMax>;
}

template<size_t TMin, char ... TStr>
constexpr auto getRepCounterImpl()
{
	if (!isDigit(get1st<TStr...>()))
	{
		if (get1st<TStr...>() == ',' && isDigit(get2nd<TStr...>()))
			return getRepCounterImplMax<TMin, 0, get1stRemainder<TStr...>()>();
		else
			return BuggyRegex;
	}
	return getRepCounterImpl<makeNum(TMin, get1st<TStr...>()), TStr...>();
}
template<size_t TMin>
constexpr auto getRepCounterImpl<TMin>()
{
	return RepCounter<TMin, TMin>;
}

template<char ... TStr>
constexpr auto getRepCounter()
{
	switch (get1st<TStr...>())
	{
	case '?':
		return OnceOrNever;
	case '+':
		return OnceOrMore;
	case '*':
		return NeverOrMore;
	case '{':
		if (get2nd<TStr>() == '\0')
			return BuggyRegex;
		return getRepCounterImpl<0>;
	default:
		return Once;
	}
}

template<Match ... TMatchSeries>
struct ConstMatchSeries
{
};

template<typename TMatchSeries, char ... TStr>
constexpr auto analysisOrImpl() // Note that there is no repetition counter in OR groups. 
{
	// Escape
	if (get1st<TStr...>() == '\\')
	{
		if (isSetIndicator<get2nd<TStr...>()>)
		else
			return ConstMatchSeries<>
	}
	if (get)
	return analysisOr<>
}

template<char ... TStr>
constexpr auto analysisOr
{
	
}

template<typename TMatchSeries, char ... TStr>
constexpr auto analysisChainImpl()
{
	if (get1st<TStr...>() == '\0') return TMatchSeries;
	// Escape
	if (get1st<TStr...>() == '\\')
	{
		if (isSetIndicator<get2nd<TStr...>()>)
		{
			return DeterPack<get2nd<TStr...>()>;
			/////////////////// GO ON
		}
		else
		{
			if (get3rd<TStr...>() == '{') // The length of repcounter varies.
				return analysisChainImpl<ConstMatchSeries<TMatchSeries::template Match<get3rd<TStr...>(), getRepCounter<get3ndRemainder<TStr...>()>>, substrAfter<TStr...>()>;
			else // The length of repcounter doesn't varies.
			{
				if (get4th<TStr...>())
					return analysisChainImpl<ConstMatchSeries<TMatchSeries::template Match<get3rd<TStr...>(), Once>>, get4thRemainder<TStr...>()>;
				else
					return analysisChainImpl<ConstMatchSeries<TMatchSeries::template Match<get3rd<TStr...>(), getRepCounter<get4th<TStr...>()>>, get4thRemainder <TStr...>()>;
			}
		}
	}
	
	if ()
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
	analysis<TStr ..., '\0', '\0', '\0'>();
}
