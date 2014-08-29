#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics.hpp>

class Timer
{
	private:
		sf::Time time_started;
		sf::Time time_paused;
		sf::Clock clock;
		bool paused;
	public:
		Timer();
		void restart();
		void pause();
		void resume();
		sf::Time getTime();
};

#endif
