
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

template<char ... TStr>
constexpr auto analysis
{
	// If the first char is a reserved char.
	if (isReserved<getFirstChar<TStr...>()>)
	{
		// Check it is leading a escape sequence.
		if (getFirstChar<TStr...> == '\\')
		{
			// Is it a set indicator?
			if (isSetIndicator<getSecondChar<TStr...>()>())
			{
				// Is is a quantifier following?
				if (isQuantifier<getThirdChar<TStr...>()>)
					// Yes, so we have got an entire one, return the Match.
					return Match<typename DeterPack<getSecondChar<TStr...>()>::Type, typename QuantifierPack<getThirdChar<TStr...>()>::Type>;
			}
				
			if (isReserved<getSecondChar>)
				return analysis<getFirstCharRemainder<TStr...>()>;
			
		}
	}
	
	
	
}

template<char ... TStr>
constexpr auto makeRegex()
{
	analysis<TStr ..., '\0', '\0'>();
}
