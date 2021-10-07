#pragma once

#include <cstdlib>
#include <cstring>

struct IntList {
	int			value = 0.0;
	IntList*	next = nullptr;
	//possede un membre qui est le prochain élément
	//de la liste ( a priori un ??? )
};

IntList* remove(IntList* l, int value);
IntList* appendFirst(IntList* l, int value);
IntList* appendLast(IntList* l, int value);
IntList* appendLastIterative(IntList* l, int value);
int length(IntList* l);

