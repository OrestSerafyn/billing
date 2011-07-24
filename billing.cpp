#include <stdio.h>
#include <conio.h>

#include "entity.h"
#include "switches.h"

int main()
{
	entity_list ent;
	int mode = initialize();

	while (1)
	{
		if (_kbhit())
		{
			switch (mode)
			{
			case MODE_MAIN:
				mode = main_switch(&ent);
				break;
			case MODE_ADD:
				mode = add_switch(&ent);
				break;
			case MODE_DEL:
				mode = delete_switch(&ent);
				break;
			case MODE_SHOW:
				mode = show_switch();
				break;
			case MODE_PING:
				mode = ping_switch(&ent);
				break;
			}
		}
		if (!ent.empty() && ent.front().isReady() && ent.front().isTimeOut())
			ent.pop_front();
	}
	return 0;
}