#include <iostream>

template<typename Caller>
class Functor {
	public:
	ssize_t operator()(char *buf, size_t len) {
		return ((Caller*)this)->read(buf, len);
	}
};

class Derived : public Base<Derived> {
public:
	
	void foo(int x) {
		std::cout << x * 2 << std::endl;
	};

	void foo(const char *str) {
		std::cerr << "niqcamer" << std::endl;
		(void) str;
	}
};

int main() {
	Derived obj;

	Derived			*ptr = &obj;
	Base<Derived>	*baseptr = &obj;
	
	ptr->foo(1);
	baseptr->foo(1);
	baseptr->foo("diocan");
};
