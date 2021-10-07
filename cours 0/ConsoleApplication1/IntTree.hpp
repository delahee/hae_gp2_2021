#pragma once

#include <cstdlib>
#include <cstring>

struct IntTree {
	int			value = 0.0;

	IntTree*	fg = nullptr;
	IntTree*	fd = nullptr;

	// le fils gauche de l'arbre ici
	// 	   ???
	// 
	// le fils droit de l'arbre ici
	// ???

	// relation d'ordre 
	// valeur de fils gauche < ma valeur < valeur fils droit
};

int			count(IntTree* head);
IntTree*	create(int value );
IntTree*	insert(IntTree* head, int value );
IntTree*	remove(IntTree* head, int value );
IntTree*	merge(IntTree* a, IntTree* b);




