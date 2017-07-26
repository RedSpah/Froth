#pragma once
#include <utility>
#include <sstream>
#include <iostream>
#include <string>
#include "FrothCore.hpp"

namespace froth
{

	val pop(stack& stack_to_pop)
	{
		if (stack_to_pop.empty()) { return error("PopError: Tried to Pop an empty stack."); }
		else {
			val v = stack_to_pop.top();
            stack_to_pop.pop();
			return v;
		}
	}

	val pop(queue& queue_to_pop)
	{
		if (queue_to_pop.empty()) { return error("PopError: Tried to Pop an empty queue."); }
		else {
			val v = queue_to_pop.front();
            queue_to_pop.pop();
			return v;
		}
	}

	bool is_int(const val& val) { return std::holds_alternative<int64_t>(val); }
	bool is_real(const val& val) { return std::holds_alternative<double>(val); }
	bool is_string(const val& val) { return std::holds_alternative<std::string>(val); }
	bool is_command(const val& val) { return std::holds_alternative<command>(val); }
	bool is_error(const val& val) { return std::holds_alternative<error>(val); }

	std::string get_type_string(val& val)
	{
		if (is_real(val)) { return "real   "; }
		else if (is_int(val)) { return "int    "; }
		else if (is_command(val)) { return "command"; }
		else if (is_error(val)) { return "error  "; }
		else return "string ";
	}

	std::string get_string(val& val, stack& stack)
	{
		if (is_real(val)) { return std::to_string(std::get<double>(val)); }
		else if (is_int(val)) { return std::to_string(std::get<int64_t>(val)); }
		else if (is_command(val)) { return std::get<1>(*std::find_if(builtins_begin(), builtins_end(), [&val](auto b) {return std::get<0>(b) == std::get<command>(val).com; })); }
		else if (is_error(val)) { return std::get<error>(val).what; }
		else return std::get<std::string>(val);
	}

	int64_t get_int(val& val, stack& stack)
	{
		if (is_real(val)) { return static_cast<int64_t>(std::get<double>(val)); }
		else if (is_int(val)) { return std::get<int64_t>(val); }
		else
		{
			std::stringstream ss;
			ss << "TypeError, unable to convert value {" << get_string(val, stack) << "} to an integer.";
			stack.push(error(ss.str()));
			return 0;
		}
	}

	double get_real(val& val, stack& stack)
	{
		if (is_real(val)) { return std::get<double>(val); }
		else if (is_int(val)) { return static_cast<double>(std::get<int64_t>(val)); }
		else
		{
			std::stringstream ss;
			ss << "TypeError, unable to convert value {" << get_string(val, stack) << "} to a real.";
			stack.push(error(ss.str()));
			return 0;
		}
	}

	command get_command(val& val, stack& stack)
	{
		if (is_command(val)) { return std::get<command>(val); }
		else
		{
			std::stringstream ss;
			ss << "TypeError, unable to convert value {" << get_string(val, stack) << "} to a command.";
			stack.push(error(ss.str()));
			return command(NOP);
		}
	}

	bool get_bool(val& val)
	{
		if (is_real(val)) { return get_real(val, unused_stack) != 0; }
		else if (is_int(val)) { return get_int(val, unused_stack) != 0; }
		else if (is_command(val)) { return true; }
		else if (is_error(val)) { return false; }
		else return trim(get_string(val, unused_stack)) != "";
	}

	void interrupt()
	{
		std::cin.clear();
		std::cin.get();
	}

	std::string pretty_print_val(val& val) { return std::string("\t| ") + get_type_string(val) + "\t| " + get_string(val, unused_stack); }

	void print_container(stack& stack_to_print)
	{
		stack s = stack_to_print;
		int id = 0;
		std::cout << '\n';
		while (!s.empty())
		{
			std::cout << id++ << pretty_print_val(pop(s)) << '\n';
		}
	}

	void print_container(queue& queue_to_print)
	{
		queue q = queue_to_print;
		int id = 0;
		std::cout << '\n';
		while (!q.empty())
		{
			std::cout << id++ << pretty_print_val(pop(q)) << '\n';
		}
	}
}
