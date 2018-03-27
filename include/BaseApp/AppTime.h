#pragma once

namespace App
{
	class Time
	{
	public:

		Time(bool noinit = false);
		Time(const Time &t);
		Time& operator= (const Time &t);
		~Time();

		static Time Milli(unsigned long long int t);
		static Time Micro(unsigned long long int t);
		static Time Seconds(unsigned long long int t);

		Time operator+ (const Time &t) const;
		Time operator- (const Time &t) const;
		void operator+= (const Time &t);
		void operator-= (const Time &t);

		bool operator< (const Time &t) const;
		bool operator> (const Time &t) const;
		bool operator<= (const Time &t) const;
		bool operator>= (const Time &t) const;
		bool operator== (const Time &t) const;
		bool operator!= (const Time &t) const;

		unsigned long long toSeconds() const;
		float toRoundedSeconds() const;
		unsigned long long toMilliseconds() const;
		float toRoundedMilliseconds() const;
		unsigned long long toMicroseconds() const;
		float toRoundedMicroseconds() const;

	private:

		unsigned long long int _time;
	};
}
