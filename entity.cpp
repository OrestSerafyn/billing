#include <string.h>
#include "entity.h"
#include "timer.h"

entity_t::entity_t(char* str)
{
	ready = false;
	count = 0;
	strcpy_s(name, str);
}
int entity_t::getCount()
{
	return count;
}
void entity_t::increaseCount()
{
	count++;
	startTimer();
}

bool entity_t::isReady()
{
	return ready;
}
void entity_t::setReady(bool value)
{
	ready = value;
}

void entity_t::startTimer()
{
	timer.start(LIFE_TIME);
}
bool entity_t::isTimeOut()
{
	return timer.isTimeOut();
}

void entity_t::print()
{
	printf("%s has %d tics, last for %d seconds\n", name, count, timer.elapsedTime()/CLOCKS_PER_SEC);
}

entity_list::iterator findEntity(entity_list *ent, char* name)
{
	for (entity_list::iterator i = ent->begin(); i != ent->end(); i++)
		if (!strcmp(name, i->name))
			return i;
	return ent->end();
}

