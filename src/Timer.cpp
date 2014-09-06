#include "Timer.h"

Timer::Timer()
{
	paused = true;
	restart();
}

sf::Time Timer::getTime()
{
	if(!paused) return clock.getElapsedTime() - time_started;
	else return time_paused - time_started;
}

void Timer::restart()
{
	time_started = clock.getElapsedTime();
	time_paused = time_started;
}

void Timer::pause()
{
	if(!paused)
	{
		time_paused = clock.getElapsedTime();
		paused = true;
	}
}

void Timer::resume()
{
	if(paused)
	{
		time_started = clock.getElapsedTime() - (time_paused - time_started);
		paused = false;
	}
}
