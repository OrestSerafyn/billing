#ifndef SWITCHES_H
#define SWITCHES_H

#define MODE_MAIN 1
#define MODE_ADD  2
#define MODE_DEL  3
#define MODE_SHOW 4
#define MODE_PING 5

int add_switch(entity_list *ent);
int main_switch(entity_list *ent);
int delete_switch(entity_list *ent);
int show_switch();
int ping_switch(entity_list *ent);
int initialize();

#endif