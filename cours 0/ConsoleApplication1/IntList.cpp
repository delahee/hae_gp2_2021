#include "IntList.hpp"

int length(IntList* l) {
	if (!l)		
		return 0;
	else		
		return 1 + length(l->next);
}



IntList* remove(IntList* l, int value)
{
	if (!l)
		return nullptr;

	if (l->value == value) {
		IntList* rest = l->next;
		free(l);
		return rest;
	}
	else {
		l->next = remove(l->next, value);
		return l;
	}
}

IntList* appendFirst(IntList* l, int value)
{
	IntList* v = (IntList*)malloc(sizeof(IntList));
	v->value = value;
	v->next = l;
	return v;
}

IntList* appendLast(IntList* l, int value) {
	if (!l)
		return appendFirst(l, value);
	if (l->next)
		appendLast(l->next, value);
	else
		l->next = appendFirst(nullptr, value);
	return l;
}

IntList* appendLastIterative(IntList* l, int value)
{
	//si la liste est vide
	if (!l)
		return appendFirst(l, value);
	if (l->next)
	{
		IntList* before = l->next;
		while (before->next) {
			before = before->next;
		}
		before->next = appendFirst(nullptr, value);
	}
	else
		l->next = appendFirst(nullptr, value);
	return l;
}

