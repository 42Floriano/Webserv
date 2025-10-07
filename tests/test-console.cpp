#include "Console.hpp"
void	foo(std::string bar) {

	(void) bar;
	console::debug(__PRETTY_FUNCTION__);
	++console::debug;
	console::debug << "Fuck" << std::endl;
	++console::debug;
	console::debug << "Damn" << std::endl;
	console::debug("");
	--console::debug;
	--console::debug;
}
int	main() {

	console::info << "Salut" << std::endl;
	console::debug << "Hello" << std::endl;
	console::error << "Ciao" << std::endl;
	foo("");
	
}
