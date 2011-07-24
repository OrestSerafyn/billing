#ifndef TIMER_H
#define TIMER_H

#include <time.h>

#define MINUTES 60 * CLOCKS_PER_SEC
#define LIFE_TIME 1 * MINUTES 

typedef class {
	private:
		unsigned long begTime;
		unsigned long timeOut;
	public:
		void start(unsigned long seconds);
		unsigned long elapsedTime();
		bool isTimeOut();
} timer_t ;

#endif