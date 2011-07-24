#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <iterator>

#include "entity.h"
#include "switches.h"

#define ADD '1'
#define DEL '2'
#define SHOW '3'
#define PING '4'
#define EXIT '5'

#define SYM_MIN_NUM '0'
#define SYM_MAX_NUM '9'
#define SYM_A_UP 'A'
#define SYM_A_LOW 'a'
#define SYM_Z_UP 'Z'
#define SYM_Z_LOW 'z'
#define SYM_ESCAPE 0x1B
#define SYM_ENTER 0x0D

#define IS_NUMBER(x) ((x) >= SYM_MIN_NUM && (x) <= SYM_MAX_NUM)
#define IS_UPPER_CASE(x) ((x) >= SYM_A_UP && (x) <= SYM_Z_UP)
#define IS_LOWER_CASE(x) ((x) >= SYM_A_LOW && (x) <= SYM_Z_LOW)
#define IS_ESCAPE(x) ((x) == SYM_ESCAPE)
#define IS_ENTER(x)  ((x) == SYM_ENTER)

#define CHAR_TO_NUMERIC(x) ((x)-48)

//testing online cvs github

static void print_menu()
{
	system("cls");
	printf("1.Add new entity\n");
	printf("2.Delete entity\n");
	printf("3.Show list of entitys\n");
	printf("4.ping entity\n");
	printf("5.Exit\n");
}

static void print_enter_name()
{
	system("cls");
	printf("enter name of new entity\npress enter to finish or ESC to skip\n");
}

static void print_entity(entity_list *ent)
{
	system("cls");
	for (entity_list::iterator i = ent->begin(); i != ent->end(); i++)
		i->print();
	printf("press enter to return to main menu\n");
}

static void changeCount(entity_list *ent, entity_list::iterator iter)
{
	iter->increaseCount();
	ent->splice(ent->end(), *ent, iter);
}

void terminate_prog()
{
	exit(0);
}

int add_switch(entity_list *ent)
{
	char value = _getch();
	int count = 0;	
	static char name[ENTITY_LENGTH]="\0";

	while (name[count++]);

	if (IS_ENTER(value) || IS_ESCAPE(value))
	{
		if (IS_ENTER(value) && (count > 1) &&
			(findEntity(ent, name) == ent->end()))
		{
			entity_t e(name);

			ent->push_back(e);
			ent->back().startTimer();
			ent->back().setReady(true);
		}
		name[0] = '\0';
		print_menu();
		return MODE_MAIN;
	}

	if ((IS_NUMBER(value) || IS_UPPER_CASE(value) || IS_LOWER_CASE(value))
		&& (count < ENTITY_LENGTH))
	{
		_putch(value);
		name[count-1] = value;
		name[count] = '\0';
	}
	return MODE_ADD;
}

int delete_switch(entity_list *ent)
{
	char value = _getch();
	static int number = -1;

	if (IS_ESCAPE(value) || IS_ENTER(value))
	{
		if ((number >= 0) && (number < (int)ent->size()) && IS_ENTER(value))
		{
			entity_list::iterator iter = ent->begin();
			advance(iter, number);
			ent->erase(iter);
			number = -1;
		}
		print_menu();
		return MODE_MAIN;
	}

	if (IS_NUMBER(value))
		number = CHAR_TO_NUMERIC(value);
	
	return MODE_DEL;
}

int show_switch()
{
	if (IS_ENTER(_getch()))
	{
		print_menu();
		return MODE_MAIN;
	}
	return MODE_SHOW;
}

int ping_switch(entity_list *ent)
{
	char value = _getch();
	int count = 0;
	static char name[ENTITY_LENGTH] = "\0";

	while (name[count++]);

	if (IS_ENTER(value) || IS_ESCAPE(value))
	{
		entity_list::iterator iter = findEntity(ent, name);

		if (IS_ENTER(value) && (count > 1) && (iter != ent->end()))
			changeCount(ent, iter);
		name[0] = '\0';
		print_menu();
		return MODE_MAIN;
	}
	if ((IS_NUMBER(value) || IS_UPPER_CASE(value) || IS_LOWER_CASE(value)) ||
		(count < ENTITY_LENGTH))
	{
		_putch(value);
		name[count-1] = value;
		name[count] = '\0';
	}
	return MODE_PING;
}

int main_switch(entity_list *ent)
{
	switch (_getch())
	{
	case ADD:
		if (ent->size() > 9)
			return MODE_MAIN;
		print_enter_name();
		return MODE_ADD;
	case DEL:
		if (ent->size() == 0)
			return MODE_MAIN;
		print_enter_name();
		return MODE_DEL;
	case SHOW:
		print_entity(ent);
		return MODE_SHOW;
	case PING:
		if (ent->size() == 0)
			return MODE_MAIN;
		print_enter_name();
		return MODE_PING;
	case EXIT:
		terminate_prog();
	}
	return MODE_MAIN;
}

int initialize()
{
	print_menu();
	return MODE_MAIN;
}
