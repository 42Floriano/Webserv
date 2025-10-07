#include <iostream>

#define NEW_METHOD(name)\
template<class Owner>\
class has_##name {\
	public:\
	void	(Owner::*ptr)(void);\
\
	public:\
	has_##name(void (Owner::*cb)(void) = NULL): ptr(cb) {\
\
	};\
\
	void	name(void) {\
		if (ptr)\
			((Owner *)this->*ptr)();\
	};\
}

NEW_METHOD(foo);
NEW_METHOD(lol);


class	X: public has_foo<X>, public has_lol<X> {
	
	public:
	void	hello(void) {
		std::cout << "Hello" << std::endl;	
	};

	public:
	X(void): has_foo(&X::hello), has_lol() {

	};
};

int	main () {
	X x;	
	x.foo();
	x.lol();
	x.has_lol::ptr = &X::hello;
	x.lol();
	x.has_lol::ptr = &X::hello;
}
