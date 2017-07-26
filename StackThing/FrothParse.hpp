#pragma once
#include "FrothBuiltins.hpp"
#include "FrothHelper.hpp"

namespace froth
{
	val parse_val(std::string& string_to_parse)
	{
		std::stringstream parse_stream, error_stream;
        string_to_parse = trim(string_to_parse);
		parse_stream << string_to_parse;

		auto builtin_iter = ::std::find_if(builtins_begin(), builtins_end(), [&string_to_parse](auto p) {return string_to_parse == std::get<1>(p); });

		if (builtin_iter != builtins_end()) { return command(std::get<0>(*builtin_iter)); }
		else if (std::all_of(string_to_parse.begin(), string_to_parse.end(), [](char c) {return is_contained(c, std::string("-.0123456789")); }))
		{
			try
			{
				if (std::find(string_to_parse.begin(), string_to_parse.end(), '.') == string_to_parse.end())
				{
					int64_t int_val;
					parse_stream >> int_val;

					if (parse_stream.fail())
					{
						error_stream << "Can't parse integer {" << string_to_parse << "}, with error of " << ((parse_stream.rdstate() == std::ios_base::badbit) ? "std::ios_base::badbit (FormatError)." : "std::ios_base::failbit (StreamError).");
						return error(error_stream.str());
					}
					else return int_val;
				}
				else
				{
					double real_val;
					parse_stream >> real_val;

					if (parse_stream.fail())
					{
						error_stream << "Can't parse real {" << string_to_parse << "}, with error of " << ((parse_stream.rdstate() == std::ios_base::badbit) ? "std::ios_base::badbit (FormatError)." : "std::ios_base::failbit (StreamError).");
						return error(error_stream.str());
					}
					else return real_val;
				}
			}
			catch (std::exception e)
			{
				error_stream << "Exception when parsing {" << string_to_parse << "}, with error of " << e.what() << ".";
			}
		}
		else if (error_stream.str() == "") { return parse_stream.str(); }
		return error_stream.str();
	}

	void eval(stack& execution_stack, queue& instruction_queue)
	{
		int indentation_level = 0;
		while (!instruction_queue.empty())
		{
			val val = instruction_queue.front();
			instruction_queue.pop();

			if (is_command(val))
			{
				auto builtin_iter = std::find_if(builtins_begin(), builtins_end(), [&val](auto& v) {return std::get<0>(v) == std::get<command>(val).com; });
				if (builtin_iter != builtins_end())
				{
					
					if (std::get<0>(*builtin_iter) == FBEGIN) { indentation_level++; execution_stack.push(val);}
					else if (std::get<0>(*builtin_iter) == FEND) { indentation_level--; execution_stack.push(val);}
					else if (std::get<0>(*builtin_iter) == INVOKE_FORCE && indentation_level < 2) { std::get<2>(*builtin_iter)(execution_stack, instruction_queue); }
					else if (indentation_level > 0) { execution_stack.push(val); }
					else { std::get<2>(*builtin_iter)(execution_stack, instruction_queue);}			
				}
				else execution_stack.push(error(std::string("LolwutError: Unimplemented builtin.")));
			}
			else if (is_error(val) && indentation_level == 0) { std::cout << std::get<error>(val).what << std::endl;}
			else {execution_stack.push(val);}
		}
	}

	queue full_parse(std::string& s)
	{
		queue instruction_queue;
		for (std::string str : split(s, std::string(" "))) { instruction_queue.push(parse_val(str)); }
		return instruction_queue;
	}
}