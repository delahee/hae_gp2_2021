#pragma once

template<typename Type>
class List {
public:
	Type	val = {};
	List*	next = nullptr;

	List(Type elem) {
		val = elem;
	}

	List(Type elem, List* _next ) {
		val = elem;
		next = _next;
	}

	List* push_first(Type nu_elem) {
		auto l = new List(nu_elem);
		l->next = this;
		return l;
	}

	List* remove(Type elem) {
		if (val == elem) {
			List* n = next;
			delete this;
			return n;
		}
		else {
			if (next) 
				next->remove(elem);
			return this;
		}
	};

	List* push_back(Type nu_elem) {
		if (!next) {
			next = new List(nu_elem);
		}
		else {
			next->push_back(nu_elem);
		}
		return this;
	}
};

template<typename Type>
void bsearch(Type* arr, int size);