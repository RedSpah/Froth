#include <iostream>
#include "FrothParse.hpp"

using namespace froth;

int main()
{
	queue instruction_queue;
	stack execution_stack;
	std::string inp; 

	while (1)
	{
		std::cout << "Input Froth:\n";
		std::getline(std::cin, inp, '\n');	
		if (inp == "end") { break; }
		if (inp == "clear") { execution_stack = stack(); continue; }
		if (inp == "reset") 
		{ 
			execution_stack = stack(); 
			funcs.clear(); 
			continue;
		}
		instruction_queue = full_parse(inp);

		std::cout << "Input Queue:\n";
		print_container(instruction_queue);
		std::cout << '\n';

		froth::eval(execution_stack, instruction_queue);
		
		std::cout << "Result Stack:\n";
		print_container(execution_stack);
		std::cout << "\n";
	}
	return 0;
}