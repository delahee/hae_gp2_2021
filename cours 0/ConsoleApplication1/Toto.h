#pragma once

/* version C uniquement
struct Toto {
	float x = 0.0f;
};
*/

class D {

};

class Toto : public D{
public:
	float x = 0.0f;
};

template<typename MaClasse>
class Foo {
	MaClasse* ptr = nullptr;
};

typedef Foo<float>  A;
typedef Foo<int>  B;
typedef Foo<double>  C;

