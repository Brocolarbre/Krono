#pragma once

#include <chrono>

namespace krono
{
	struct ElapsedTime
	{
		double seconds = 0.0;
		double milliseconds = 0.0;
		double microseconds = 0.0;
		double nanoseconds = 0.0;
	};

	class Chronometer
	{
	protected:
		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::nanoseconds m_elapsedTime;
		bool m_stopped;

	public:
		Chronometer(bool start = true);

		void start();
		void stop();
		void reset();
		void restart();

		ElapsedTime getElapsedTime() const;
	};

	enum class TimeUnit
	{
		Seconds = 0,
		Milliseconds,
		Microseconds,
		Nanoseconds
	};

	struct RemainingTime
	{
		double seconds = 0.0;
		double milliseconds = 0.0;
		double microseconds = 0.0;
		double nanoseconds = 0.0;
	};

	class Timer
	{
	private:
		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::nanoseconds m_elapsedTime;
		std::chrono::nanoseconds m_remainingTime;
		bool m_stopped;

	public:
		Timer(double time, TimeUnit timeUnit, bool start = true);

		void start();
		void stop();
		void reset();
		void restart();

		bool timeIsUp() const;
		RemainingTime getRemainingTime() const;
	};

	struct Time
	{
		int year = 0;
		int month = 0;
		int day = 0;
		int hours = 0;
		int minutes = 0;
		int seconds = 0;
	};

	class Clock
	{
	public:
		static Time getTime();
	};

	inline Chronometer::Chronometer(bool start) :
		m_startTime(),
		m_elapsedTime(),
		m_stopped()
	{
		reset();

		if (start)
			this->start();
	}

	inline void Chronometer::start()
	{
		m_stopped = false;
		m_startTime = std::chrono::steady_clock::now();
	}

	inline void Chronometer::stop()
	{
		m_elapsedTime += std::chrono::steady_clock::now() - m_startTime;
		m_stopped = true;
	}

	inline void Chronometer::reset()
	{
		m_startTime = std::chrono::steady_clock::time_point(std::chrono::nanoseconds::zero());
		m_elapsedTime = std::chrono::nanoseconds(0);
		m_stopped = true;
	}

	inline void Chronometer::restart()
	{
		reset();
		start();
	}

	inline ElapsedTime Chronometer::getElapsedTime() const
	{
		std::chrono::nanoseconds elapsedTime = m_stopped ? m_elapsedTime : m_elapsedTime + std::chrono::steady_clock::now() - m_startTime;

		return ElapsedTime{
			static_cast<double>(elapsedTime.count()) / std::chrono::nanoseconds::period::den,
			static_cast<double>(elapsedTime.count()) / std::chrono::microseconds::period::den,
			static_cast<double>(elapsedTime.count()) / std::chrono::milliseconds::period::den,
			static_cast<double>(elapsedTime.count()) / std::chrono::seconds::period::den
		};
	}

	inline Timer::Timer(double time, TimeUnit timeUnit, bool start) :
		m_startTime(),
		m_elapsedTime(),
		m_remainingTime(),
		m_stopped()
	{
		switch (timeUnit)
		{
		case TimeUnit::Seconds:
			m_remainingTime = std::chrono::nanoseconds(static_cast<long long>(time * std::chrono::nanoseconds::period::den));
			break;
		case TimeUnit::Milliseconds:
			m_remainingTime = std::chrono::nanoseconds(static_cast<long long>(time * std::chrono::milliseconds::period::den));
			break;
		case TimeUnit::Microseconds:
			m_remainingTime = std::chrono::nanoseconds(static_cast<long long>(time * std::chrono::microseconds::period::den));
			break;
		case TimeUnit::Nanoseconds:
			m_remainingTime = std::chrono::nanoseconds(static_cast<long long>(time));
			break;
		}

		reset();

		if (start)
			this->start();
	}

	inline void Timer::start()
	{
		m_stopped = false;
		m_startTime = std::chrono::steady_clock::now();
	}

	inline void Timer::stop()
	{
		m_elapsedTime += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - m_startTime);
		m_stopped = true;
	}

	inline void Timer::reset()
	{
		m_startTime = std::chrono::steady_clock::time_point(std::chrono::nanoseconds::zero());
		m_elapsedTime = std::chrono::nanoseconds(0);
		m_stopped = true;
	}

	inline void Timer::restart()
	{
		reset();
		start();
	}

	inline bool Timer::timeIsUp() const
	{
		return getRemainingTime().nanoseconds <= 0;
	}

	inline RemainingTime Timer::getRemainingTime() const
	{
		std::chrono::nanoseconds elapsedTime = m_stopped ? m_elapsedTime : m_elapsedTime + (std::chrono::steady_clock::now() - m_startTime);
		std::chrono::nanoseconds remainingTime = m_remainingTime - elapsedTime;

		return RemainingTime{
			static_cast<double>(remainingTime.count()) / std::chrono::nanoseconds::period::den,
			static_cast<double>(remainingTime.count()) / std::chrono::microseconds::period::den,
			static_cast<double>(remainingTime.count()) / std::chrono::milliseconds::period::den,
			static_cast<double>(remainingTime.count()) / std::chrono::seconds::period::den
		};
	}

	inline Time Clock::getTime()
	{
		std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
		std::chrono::zoned_time<std::chrono::system_clock::duration> localZonedTime(std::chrono::current_zone(), time);
		std::chrono::local_time<std::chrono::seconds> localTime = std::chrono::floor<std::chrono::seconds>(localZonedTime.get_local_time());
		std::chrono::local_days localDays = std::chrono::floor<std::chrono::days>(localTime);
		std::chrono::year_month_day yearMonthDay(localDays);
		std::chrono::hh_mm_ss<std::chrono::seconds> hourMinuteSecond(localTime - localDays);

		return Time{
			static_cast<int>(yearMonthDay.year()),
			static_cast<int>(static_cast<unsigned>(yearMonthDay.month())),
			static_cast<int>(static_cast<unsigned>(yearMonthDay.day())),
			static_cast<int>(hourMinuteSecond.hours().count()),
			static_cast<int>(hourMinuteSecond.minutes().count()),
			static_cast<int>(hourMinuteSecond.seconds().count())
		};
	}
}