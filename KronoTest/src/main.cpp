#include <Krono/Krono.hpp>
#include <iostream>

int main()
{
	std::cout << "Krono" << std::endl;

	krono::Chronometer chronometer;

	float chronometerDisplay = 0.0f;
	while (chronometer.getElapsedTime().milliseconds < 2000.0f)
	{
		if (chronometer.getElapsedTime().milliseconds > chronometerDisplay)
		{
			chronometerDisplay += 200.0f;
			std::cout << "Elapsed time : " << chronometer.getElapsedTime().milliseconds << "ms" << std::endl;
		}
	}

	krono::Timer timer(2.4, krono::TimeUnit::Seconds);

	float timerDisplay = 2000.0f;
	while (!timer.timeIsUp())
	{
		if (timer.getRemainingTime().milliseconds < timerDisplay)
		{
			timerDisplay -= 200.0f;
			std::cout << "Remaining time : " << timer.getRemainingTime().milliseconds << "ms" << std::endl;
		}
	}

	krono::Time time = krono::Clock::getTime();
	std::cout << "Current time : " << time.day << "/" << time.month << "/" << time.year << " -> " << time.hours << ":" << time.minutes << ":" << time.seconds << std::endl;

	std::cout << "Press enter to exit..." << std::endl;
	std::cin.get();

	return 0;
}