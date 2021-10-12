#include "IntTree.hpp"

IntTree* create(int value) {
	IntTree* node = (IntTree*)malloc(sizeof(IntTree));
	node->value = value;
	node->fg = node->fd = nullptr;
	return node;
}

int count(IntTree* head){
	if (!head) return 0;
	return 1 + count(head->fg) + count(head->fd);
}


// prouve P(0)
// prouve qu'il existe P(n+1) = Y(Pn)
// => implique que ca se termine correctement et que ca fait ce qu'on veut


IntTree* insert(IntTree* head, int value){
	if (!head) return create(value);
	if (value < head->value) 
		head->fg = insert(head->fg, value);
	else 
		head->fd = insert(head->fd, value);
	return head;
}

IntTree* remove(IntTree* head, int value){
	if (!head)
		return head;

	if (value == head->value) {
		IntTree* merged = merge(head->fg, head->fd);
		free(head);
		head = merged;
	}
	else {
		head->fg = remove(head->fg,value);
		head->fd = remove(head->fd,value);
	}
	return head;
}

IntTree* merge(IntTree* a, IntTree* b)
{
	if (!a) return b;
	if (!b) return a;

	IntTree* fg = a->fg;
	IntTree* fd = a->fd;
	int value = a->value;
	free(a);

	b = insert(b, value);

	b = merge(fg, b);
	b = merge(fd, b);

	return b;
}
