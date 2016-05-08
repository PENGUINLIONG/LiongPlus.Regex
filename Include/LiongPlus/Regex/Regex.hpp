//
//  rpp.cpp
//  RegexPlusPlus
//
//  Created by 梁任冬 on 16/05/06.
//  Copyright © 2015年 梁任冬. All rights reserved.
//

#pragma once
#include <array>
#include <utility>

#define L_REGEX_STR(str) [](){ return str; }

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
		class RepetitionCounter
		{
		public:
			constexpr static long From = TFrom;
			constexpr static long To = TTo;
		};

		typedef RepetitionCounter<0, 0> Never;
		typedef RepetitionCounter<0, -1> NeverOrMore;
		typedef RepetitionCounter<0, 1> OnceOrNever;
		typedef RepetitionCounter<1, -1> OnceOrMore;

        // Determinators

		// Note: Every Functor have the responsibility to advance each time it succeeds.
		//       Also, it also need to check if it is at the end of string for safety.
        //       '\0' should never be used in regex.
        
        enum class DeterResult
        {
            Succeeded,
            StepOut,
            Failed
        };
        
        template<char TC>
        class SameTo
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (*c == TC);
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        template<char TC>
        class DifFrom
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (*c != TC && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        template<typename T>
        class SameToString;
        template<char ... TStr>
        class SameToString<ConstStrParser<TStr...>>
        {
        public:
            static DeterResult Do(char*& c)
            {
                std::array<char, sizeof...(TStr)> _Str = { TStr... };
                for (auto strc : _Str)
                {
                    if (*c != strc)
                        return DeterResult::Failed;
                    ++c;
                }
                return DeterResult::Succeeded;
            }
        };
        template<typename T>
        class DifFromString;
        template<char ... TStr>
        class DifFromString<ConstStrParser<TStr...>>
        {
        public:
            static DeterResult Do(char*& c)
            {
                std::array<char, sizeof...(TStr)> _Str = { TStr... };
                for (auto strc : _Str)
                {
                    if (*c != strc)
                        return DeterResult::Succeeded;
                    ++c;
                }
                return DeterResult::Failed;
            }
        };
        template<char TFrom, char TTo>
        class InRange
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (TFrom >= *c && *c <= TTo);
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        template<char TFrom, char TTo>
        class OutOfRange
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((TFrom < *c || *c > TTo) && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class IsBlank
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (*c == ' ' || *c == '\t');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class IsDigit
        {
        public:
            static DeterResult Do(char*& c)
			{
                bool rv = ((*c >= '0' && *c <= '9') && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
			}
		};
		class NotDigit
        {
        public:
            static DeterResult Do(char*& c)
			{
                bool rv = ((*c < '0' || *c > '9') && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
			}
		};
        class IsUpper
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c >= 'A' && *c <= 'Z') && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class NotUpper
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c < 'A' || *c > 'Z') && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class IsAlpha
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z')) && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class NotAlpha
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (((*c < 'A' || *c > 'Z') && (*c < 'a' || *c > 'z')) && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class IsLower
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c >= 'a' && *c <= 'z') && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class NotLower
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c < 'A' || *c > 'Z') && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class IsSpace
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (*c == ' ' || *c == '\t' || *c == '\r' || *c == '\n' || *c == '\v' || *c == '\f');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class NotSpace
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c != ' ' && *c != '\t' && *c != '\r' && *c != '\n' && *c != '\v' && *c != '\f') && *c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class IsWord
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z') || (*c >= '0' && *c <= '9') || *c == '_');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class NotWord
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c < 'A' || *c > 'Z') && (*c < 'a' || *c > 'z') && (*c < '0' || *c > '9') && *c != '_');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        class AnyChar
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (*c != '\0');
                ++c;
                return rv ? DeterResult::Succeeded : DeterResult::Failed;
            }
        };
        // This is used to escape from loops.
        // <TStopCondition> is another determinator which decides when to step out.
        // If condition is satisfied, $c will NOT be at the end of stop condition.
        template<typename TDeterminator, typename TStopCondition>
        class Conditional
        {
        public:
            static DeterResult Do(char*& c)
            {
                auto temp = c;
                if (TStopCondition::Do(temp))
                    return DeterResult::StepOut;
                return TDeterminator::Do(c);
            }
        };
        
        template<DeterResult(*TDeterminator)(char*&)>
        class Customized
        {
        public:
            static DeterResult Do(char*& c)
            {
                return TDeterminator(c);
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
		template<typename TDeterminator, typename TCounter>
		class Match : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
				if (TCounter::From < 0) // It is illegal to have a min of negative number.
					return false;

				long counter = TCounter::From; // At least $TTime::From times.
				while (counter-- > 0)
				{
                    if (TDeterminator::Do(c) != DeterResult::Succeeded)
						return false;
					++c;
				}

				if (TCounter::To >= 0) // Negative max means there is no upper boundary.
				{
					counter = TCounter::To - TCounter::From; // At most $TTime::To times.
					while (counter-- > 0)
					{
                        if (TDeterminator::Do(c) != DeterResult::Succeeded)
							return true;
						++c;
					}

                    if (TDeterminator::Do(c) == DeterResult::Succeeded) // There should be no more now.
						return false;
				}
				else
				{
                    while (TDeterminator::Do(c) == DeterResult::Succeeded);
				}

				return true;
			}
		};
		template<typename TDeterminator>
		class Match<TDeterminator, RepetitionCounter<0, 0>> : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
                return (TDeterminator::Do(c) != DeterResult::Succeeded);
            }
		};
		template<typename TDeterminator>
		class Match<TDeterminator, RepetitionCounter<0, -1>> : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
                while (TDeterminator::Do(c) != DeterResult::Succeeded);

				return true;
			}
		};
		template<typename TDeterminator>
		class Match<TDeterminator, RepetitionCounter<0, 1>> : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
                if (TDeterminator::Do(c) != DeterResult::Succeeded || TDeterminator::Do(c) == DeterResult::Succeeded)
					return false;

				return true;
			}
		};
		template<typename TDeterminator>
		class Match<TDeterminator, RepetitionCounter<1, -1>> : public MatchBase
		{
		public:
			bool Do(char*& c) override
			{
                if (TDeterminator::Do(c) != DeterResult::Succeeded)
					return false;
                while (TDeterminator::Do(c) == DeterResult::Succeeded);

				return true;
			}
		};
        
        // Logical operation
        
        template<typename ... TMatchSeries>
        class MatchOr : public MatchBase
        {
        private:
            std::array<MatchBase*, sizeof...(TMatchSeries)> _MatchSeries;
        public:
            MatchOr()
            {
                _MatchSeries = { new TMatchSeries()... };
            }
            ~MatchOr()
            {
                for (MatchBase* ptr : _MatchSeries)
                    delete ptr;
            }
            
            bool Do(char*& c)
            {
                for (auto match : _MatchSeries)
                {
                    auto temp = c;
                    if (match->Do(temp))
                        return true;
                }
                return false;
            }
        };
        template<typename ... TMatchSeries>
        class MatchAnd : public MatchBase
        {
        private:
            std::array<MatchBase*, sizeof...(TMatchSeries)> _MatchSeries;
        public:
            MatchAnd()
            {
                _MatchSeries = { new TMatchSeries()... };
            }
            ~MatchAnd()
            {
                for (MatchBase* ptr : _MatchSeries)
                    delete ptr;
            }
            
            bool Do(char*& c)
            {
                for (auto match : _MatchSeries)
                {
                    auto temp = c;
                    if (!match->Do(temp))
                        return false;
                }
                return true;
            }
        };
        
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

				while (*strToGo != '\0')
				{
					for (MatchBase* match : _MatchSeries)
					{
						if (match->Do(strToGo))
							return true;
					}
                    ++strToGo;
				}
				return false;
			}
		};




	}
}

template<typename T, T ... TStr>
constexpr LiongPlus::Regex::ConstStrParser<TStr...> operator""_L_Regex()
{
    return {};
}

#define _L_RX(x) decltype(x##_L_Regex)
