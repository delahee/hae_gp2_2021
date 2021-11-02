#pragma once

class List {
public:
	double  val = 0.0;
	List*	next = nullptr;

	List(double elem) {
		val = elem;
	}

	List(double elem, List* _next ) {
		val = elem;
		next = _next;
	}

	List* push_first(double nu_elem) {
		auto l = new List(nu_elem);
		l->next = this;
		return l;
	}

	List* remove(double elem) {
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

	List* push_back(double nu_elem) {
		if (!next) {
			next = new List(nu_elem);
		}
		else {
			next->push_back(nu_elem);
		}
		return this;
	}
};