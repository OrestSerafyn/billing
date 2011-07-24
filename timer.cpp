#include "timer.h"

unsigned long timer_t::elapsedTime() 
{
	return ((unsigned long) clock() - begTime);
}

void timer_t::start(unsigned long seconds) 
{
	begTime = clock();
	timeOut = seconds;
}

bool timer_t::isTimeOut() 
{
	return timeOut <= elapsedTime();
}