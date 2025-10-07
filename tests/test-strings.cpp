#include <string>
#include <iostream>

int	main() {

	// Test 1
	std::string	str(1024, 0);
	size_t		initial_capacity = str.capacity();
	
	std::cout << "Size: " << str.size() << std::endl;
	std::cout << "Capacity: " << str.capacity() << std::endl;

	std::cout << "Resizing..." << std::endl;
	str.resize(0);

	std::cout << "Size: " << str.size() << std::endl;
	std::cout << "Capacity: " << str.capacity() << std::endl;

	std::cout << std::endl;
	if (initial_capacity == str.capacity()) {
		std::cout << "Resizing down, does not shrink memeory";
	} else {
		std::cout << "Resizing down, does shrink memeory";
	}
	std::cout << std::endl;

	// Test 2
	std::string	off(1, 0);
	
	off.resize(1024);
	off += std::string("A");


	std::cout << "Word: " << off << std::endl;
	std::cout << "Word Size: " << off.size() << std::endl;
	std::cout << "First char: " << int(off[0]) << std::endl;

	// Test 3
	
	std::string	cstr;

	cstr.resize(1024);
	cstr.resize(1);
	cstr[0] = 'b';
	char	*buff = (char *)cstr.data();

	buff[0] = 'a';

	std::cout << "cstr: " << cstr << std::endl;
	return (0);
}
