# Krono

Krono is a header-only C++ library that allows the user to **measure time** in three different ways :
- Chronometer
- Timer
- Clock

## Usage

### Chronometer

The chronometer counts a time that can be retrieved in **different time units** (from seconds up to nanoseconds).

Here is an example :
```c++
#include <Krono/Krono.hpp>

int main()
{
	krono::Chronometer chronometer;

	while (chronometer.getElapsedTime().milliseconds < 2000);
		std::cout << "Elapsed time : " << chronometer.getElapsedTime().milliseconds << "ms" << std::endl;
}
```

### Timer

The timer works like a countdown. The duration can be set by the user with a specific time unit. The remaining time can be retrieved as well as a boolean that indicates if the timer as reached 0.
These two classes take an optional boolean to start on construction if true or later if false.

Here is an example :
```c++
#include <Krono/Krono.hpp>

int main()
{
	krono::Timer timer(2.4, krono::TimeUnit::Seconds);

	while (!timer.timeIsUp());
		std::cout << "Remaining time : " << timer.getRemainingTime().seconds << "s" << std::endl;
}
```

### Clock

The clock tells the current time from years up to second.

Here is an example :
```c++
#include <Krono/Krono.hpp>

int main()
{
	krono::Time time = krono::Clock::getTime();
	std::cout << "Current time : " << time.day << "/" << time.month << "/" << time.year << " -> " << time.hours << ":" << time.minutes << ":" << time.seconds << std::endl;
}
```

## Test application

**KronoTest** is a test application that you can use to try the library with ease. It implements a few **use cases**.

## Setup

To use the library :
- Include the `Krono/Krono.hpp` header file

### External dependencies

**TimeTools** has no external dependencies

**TimeToolsTest** has no following external dependencies