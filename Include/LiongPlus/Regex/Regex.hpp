// File: Regex.hpp
// Author: Rendong Liang (Liong)

#pragma once
#include <array>
#include <utility>

namespace LiongPlus
{
	namespace Regex
	{
        // Const string parser

        template<char ... TStr>
        struct ConstStrParser
        {
        };
        
        // RepetitionCounters
        
		template<long TFrom, long TTo>
		class RepCounter
		{
		public:
			constexpr static long From = TFrom;
			constexpr static long To = TTo;
		};

		typedef RepCounter<0, 0> Never;
		typedef RepCounter<0, -1> NeverOrMore;
		typedef RepCounter<0, 1> OnceOrNever;
		typedef RepCounter<1, -1> OnceOrMore;
		typedef RepCounter<1, 1> Once;

        // Determinators

		// Note: Every Functor MUST advance $c to the end each time it succeeds. When it fails, $c MUST retreate to the beginning.
        //       Every Not-function MUST change $c.
		//       Also, it also need to check if it is at the end of string for safety.
        //       '\0' should never be used in regex.
        
        template<char TC>
        class SameTo
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = (*c == TC);
                if (rv) return ++c, true;
                else return false;
            }
        };
		template<char ... TCs>
        class SameToAny
        {
        public:
            static bool Do(char*& c)
            {
				std::array<char, sizeof...(TCs)> rst = { (*c == TCs)... };
                for (auto flag : rst)
				{
					if (flag)
						return true;
				}
                return false;
            }
        };
        template<typename T>
        class SameToStr;
        template<char ... TStr>
        class SameToStr<ConstStrParser<TStr...>>
        {
        public:
            static bool Do(char*& c)
            {
                auto str = c;
                std::array<char, sizeof...(TStr)> _Str = { TStr... };
                for (auto strc : _Str)
                {
                    if (*str != strc)
                        return false;
                    ++str;
                }
                c = str;
                return true;
            }
        };
		template<char TC>
        class DifFrom
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = (*c != TC && *c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
		template<char ... TCs>
        class DifFromAny
        {
        public:
            static bool Do(char*& c)
            {
				std::array<char, sizeof...(TCs)> rst = { (*c == TCs)... };
                for (auto flag : rst)
				{
					if (flag)
						return false;
				}
                return true;
            }
        };
        template<typename T>
        class DifFromStr;
        template<char ... TStr>
        class DifFromStr<ConstStrParser<TStr...>>
        {
        public:
            static bool Do(char*& c)
            {
                auto str = c;
                std::array<char, sizeof...(TStr)> _Str = { TStr... };
                for (auto strc : _Str)
                {
                    if (*str != strc)
                        return true;
                    ++str;
                }
                return false;
            }
        };
        template<char TFrom, char TTo>
        class InRange
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = (TFrom >= *c && *c <= TTo);
                if (rv) return ++c, true;
                else return false;
            }
        };
        template<char TFrom, char TTo>
        class OutOfRange
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = ((TFrom < *c || *c > TTo) && *c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class IsBlank
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = (*c == ' ' || *c == '\t');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class IsDigit
        {
        public:
            static bool Do(char*& c)
			{
                bool rv = ((*c >= '0' && *c <= '9') && *c != '\0');
                if (rv) return ++c, true;
                else return false;
			}
		};
		class NotDigit
        {
        public:
            static bool Do(char*& c)
			{
                bool rv = ((*c < '0' || *c > '9') && *c != '\0');
                if (rv) return ++c, true;
                else return false;
			}
		};
        class IsUpper
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = ((*c >= 'A' && *c <= 'Z') && *c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class NotUpper
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = ((*c < 'A' || *c > 'Z') && *c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class IsAlpha
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = (((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z')) && *c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class NotAlpha
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = (((*c < 'A' || *c > 'Z') && (*c < 'a' || *c > 'z')) && *c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class IsLower
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = ((*c >= 'a' && *c <= 'z') && *c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class NotLower
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = ((*c < 'A' || *c > 'Z') && *c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class IsSpace
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = (*c == ' ' || *c == '\t' || *c == '\r' || *c == '\n' || *c == '\v' || *c == '\f');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class NotSpace
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = ((*c != ' ' && *c != '\t' && *c != '\r' && *c != '\n' && *c != '\v' && *c != '\f') && *c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class IsWord
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z') || (*c >= '0' && *c <= '9') || *c == '_');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class NotWord
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = ((*c < 'A' || *c > 'Z') && (*c < 'a' || *c > 'z') && (*c < '0' || *c > '9') && *c != '_');
                if (rv) return ++c, true;
                else return false;
            }
        };
        class AnyChar
        {
        public:
            static bool Do(char*& c)
            {
                bool rv = (*c != '\0');
                if (rv) return ++c, true;
                else return false;
            }
        };
        // This is used to escape from loops.
        // <TStopCondition> is another determinator which decides when to step out.
        // If condition is satisfied, $c MUST be at the beginning of stop condition.
        // Generally this is is used with Anychar.
        template<typename TDeter, typename TStopCondition>
        class Conditional
        {
        public:
            static bool Do(char*& c)
            {
                auto str = c;
                if (TStopCondition::Do(str))
                    return false;
                c = str;
                bool rv = TDeter::Do(c);
                if (rv) return ++c, true;
                else return false;
            }
        };
        template<bool(*TDeter)(char*&)>
        class Customized
        {
        public:
            static bool Do(char*& c)
            {
                return TDeter(c);
            }
        };
        

        // Matches

		class MatchBase
		{
        private:
            bool reserved;
		public:
            virtual ~MatchBase() {}
            virtual bool Do(char*&) = 0;
		};
		template<typename TDeter, typename TCounter>
		class Match : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
				if (TCounter::From < 0) // It is illegal to have a min of negative number.
					return false;

				long counter = TCounter::From; // At least $TCounter::From times.
				while (counter-- > 0)
				{
                    if (!TDeter::Do(c))
						return false;
				}

				if (TCounter::To >= 0) // Negative max means there is no upper boundary.
				{
					counter = TCounter::To - TCounter::From; // At most $TCounter::To times.
					while (counter-- > 0)
					{
                        if (!TDeter::Do(c))
							return true;
					}
                    auto str = c;
                    if (TDeter::Do(str)) // There should be no more now.
						return false;
				}
				else
				{
                    while (TDeter::Do(c));
				}

				return true;
			}
		};
		template<typename TDeter>
		class Match<TDeter, RepCounter<0, 0>> : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
                return (!TDeter::Do(c));
            }
		};
		template<typename TDeter>
		class Match<TDeter, RepCounter<0, -1>> : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
                while (!TDeter::Do(c));

				return true;
			}
		};
		template<typename TDeter>
		class Match<TDeter, RepCounter<0, 1>> : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
                TDeter::Do(c);
                return true;
			}
		};
		template<typename TDeter>
		class Match<TDeter, RepCounter<1, -1>> : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
                if (!TDeter::Do(c))
					return false;
                while (TDeter::Do(c));

				return true;
			}
		};
		template<typename TDeter>
		class Match<TDeter, RepCounter<1, 1>> : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
                if (TDeter::Do(c))
                    return true;
                else
                    return false;
			}
		};
        
        // Logical operation
        
		template<typename ... TMatchSeries>
		class MatchFactor
		{
		public:
            std::array<MatchBase*, sizeof...(TMatchSeries)> _MatchSeries;

            MatchFactor()
            {
                _MatchSeries = { new TMatchSeries()... };
            }
            ~MatchFactor()
            {
                for (MatchBase* ptr : _MatchSeries)
                    delete ptr;
            }
		};
		
        template<typename TFactor>
        class _MatchOr
        {
        public:
            static bool Do(char*& c)
            {
                TFactor factor;
				for (auto match : factor._MatchSeries)
                {
                    auto temp = c;
                    if (match->Do(temp))
                        return true;
                }
				return false;
            }
        };
		
		template<typename TFactor>
        class _MatchChain
        {
        public:
            static bool Do(char*& c)
            {
                TFactor factor;
                for (auto match : factor._MatchSeries)
                {
                    auto temp = c;
                    if (!match->Do(temp))
                        return false;
					c = temp;
                }
				return true;
            }
        };
		
		template<typename TFactor, typename TCounter>
		using MatchOr = Match<_MatchOr<TFactor>, TCounter>;
        
		template<typename TFactor, typename TCounter>
		using MatchChain = Match<_MatchChain<TFactor>, TCounter>;
		
        // Regex
        
		template <typename ... TMatchSeries>
		class Regex
		{
		private:
			std::array<MatchBase*, sizeof...(TMatchSeries)> _MatchSeries;
		public:
			Regex()
            {
                _MatchSeries = { new TMatchSeries()... };
			}
            ~Regex()
            {
                for (MatchBase* ptr : _MatchSeries)
                    delete ptr;
            }

			bool Match(const char* str)
			{
				char* strToGo = const_cast<char*>(str);
                bool flag = false;
				while (*strToGo != '\0')
				{
                    bool flagForThisTime = true;
					for (MatchBase* match : _MatchSeries)
					{
						if (!match->Do(strToGo))
                            flagForThisTime = false;
					}
                    if (flagForThisTime)
                        flag = true;
                    
                    ++strToGo;
				}
				return flag;
			}
		};
	}
}

template<typename T, T ... TStr>
constexpr LiongPlus::Regex::ConstStrParser<TStr...> operator""_L_Regex()
{
    return {};
}

template<char TC>
constexpr bool IsReserved()
{
	return TC == '+' || TC == '*' || TC == '?' || TC == '\\' || TC == '{' || TC == '}' || TC == '[' || TC == ']' || TC == '(' || TC == ')' || TC == '^' || TC == '$' || TC == '|';
}

template<char TC>
constexpr bool IsQuantifier()
{
	return TC == '+' || TC == '*' || TC == '?' || TC == '{' || TC == '}';
}

#define _L_RX(x) decltype(x##_L_Regex)
