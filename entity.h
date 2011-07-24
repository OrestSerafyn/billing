#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include "timer.h"

using namespace std;

#define ENTITY_LENGTH 10

typedef class entity_t
{
	int count;
	bool ready;
	timer_t timer;
public:
	entity_t (char* str);
	char name[ENTITY_LENGTH];

	int getCount();
	void increaseCount();

	bool isReady();
	void setReady(bool value);

	void startTimer();
	bool isTimeOut();

	void print();
} entity_t;

typedef list<entity_t> entity_list;

entity_list::iterator findEntity(entity_list *ent, char* name);

#endif