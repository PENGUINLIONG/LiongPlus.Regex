//
//  rpp.cpp
//  LiongPlus.Regex
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

		// Note: Every Functor MUST advance $c to the end each time it succeeds. When it fails, $c MUST retreate to the beginning.
        //       Every Not-function MUST change $c.
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
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        template<char TC>
        class DifFrom
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (*c != TC && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
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
                auto str = c;
                std::array<char, sizeof...(TStr)> _Str = { TStr... };
                for (auto strc : _Str)
                {
                    if (*str != strc)
                        return DeterResult::Failed;
                    ++str;
                }
                c = str;
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
                auto str = c;
                std::array<char, sizeof...(TStr)> _Str = { TStr... };
                for (auto strc : _Str)
                {
                    if (*str != strc)
                        return DeterResult::Succeeded;
                    ++str;
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
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        template<char TFrom, char TTo>
        class OutOfRange
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((TFrom < *c || *c > TTo) && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class IsBlank
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (*c == ' ' || *c == '\t');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class IsDigit
        {
        public:
            static DeterResult Do(char*& c)
			{
                bool rv = ((*c >= '0' && *c <= '9') && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
			}
		};
		class NotDigit
        {
        public:
            static DeterResult Do(char*& c)
			{
                bool rv = ((*c < '0' || *c > '9') && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
			}
		};
        class IsUpper
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c >= 'A' && *c <= 'Z') && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class NotUpper
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c < 'A' || *c > 'Z') && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class IsAlpha
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z')) && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class NotAlpha
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (((*c < 'A' || *c > 'Z') && (*c < 'a' || *c > 'z')) && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class IsLower
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c >= 'a' && *c <= 'z') && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class NotLower
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c < 'A' || *c > 'Z') && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class IsSpace
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (*c == ' ' || *c == '\t' || *c == '\r' || *c == '\n' || *c == '\v' || *c == '\f');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class NotSpace
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c != ' ' && *c != '\t' && *c != '\r' && *c != '\n' && *c != '\v' && *c != '\f') && *c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class IsWord
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z') || (*c >= '0' && *c <= '9') || *c == '_');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class NotWord
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = ((*c < 'A' || *c > 'Z') && (*c < 'a' || *c > 'z') && (*c < '0' || *c > '9') && *c != '_');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        class AnyChar
        {
        public:
            static DeterResult Do(char*& c)
            {
                bool rv = (*c != '\0');
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
            }
        };
        // This is used to escape from loops.
        // <TStopCondition> is another determinator which decides when to step out.
        // If condition is satisfied, $c MUST be at the beginning of stop condition.
        // Generally this is is used with Anychar.
        template<typename TDeterminator, typename TStopCondition>
        class Conditional
        {
        public:
            static DeterResult Do(char*& c)
            {
                auto str = c;
                if (TStopCondition::Do(str))
                    return DeterResult::StepOut;
                c = str;
                bool rv = TDeterminator::Do(c);
                if (rv) return ++c, DeterResult::Succeeded;
                else return DeterResult::Failed;
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

				long counter = TCounter::From; // At least $TCounter::From times.
				while (counter-- > 0)
				{
                    if (TDeterminator::Do(c) != DeterResult::Succeeded)
						return false;
				}

				if (TCounter::To >= 0) // Negative max means there is no upper boundary.
				{
					counter = TCounter::To - TCounter::From; // At most $TCounter::To times.
					while (counter-- > 0)
					{
                        if (TDeterminator::Do(c) != DeterResult::Succeeded)
							return true;
					}
                    auto str = c;
                    if (TDeterminator::Do(str) == DeterResult::Succeeded) // There should be no more now.
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
                if (TDeterminator::Do(c) == DeterResult::Succeeded)
                {
                    auto str = c;
                    if (TDeterminator::Do(str) == DeterResult::Succeeded)
                        return false;
                }
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
        
        template<typename ... T>
        class MatchOr; // Do determinator or and match or ////////////////
        
        template<typename TDeterminator>
        class MatchFactor; // Used to parse determinators when doing determinator or //////////////
        
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

#define _L_RX(x) decltype(x##_L_Regex)
