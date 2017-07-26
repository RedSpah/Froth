#pragma once
#include <functional>
#include <tuple>
#include <vector>
#include <string>
#include "FrothFuncs.hpp"

#define BUILTIN_DEF(x) void BUILTIN_ ## x (stack& execution_stack, queue& instruction_queue)
#define BUILTIN_FUNC(x) builtins_impl::BUILTIN_ ## x
#define BUILTIN(x, s) {##x,##s,BUILTIN_FUNC(x)}

namespace froth
{
	namespace builtins_impl
	{
		BUILTIN_DEF(EVAL_N);
		BUILTIN_DEF(FSIZE);
		BUILTIN_DEF(UNPACK);

        BUILTIN_DEF(NOP) {}



		BUILTIN_DEF(PLUS) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) 
            {
                execution_stack.push(get_int(a, execution_stack) + get_int(b, execution_stack)); 
            }
			else 
            { 
                execution_stack.push(get_real(a, execution_stack) + get_real(b, execution_stack)); 
            }
		}

		BUILTIN_DEF(MINUS) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) 
            { 
                execution_stack.push(get_int(b, execution_stack) + get_int(a, execution_stack)); 
            }
			else 
            { 
                execution_stack.push(get_real(b, execution_stack) + get_real(a, execution_stack)); 
            }
		}

		BUILTIN_DEF(MUL) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) 
            { 
                execution_stack.push(get_int(b, execution_stack) * get_int(a, execution_stack)); 
            }
			else 
            { 
                execution_stack.push(get_real(b, execution_stack) * get_real(a, execution_stack)); 
            }
		}

		BUILTIN_DEF(DIV) {
			val a = pop(execution_stack), b = pop(execution_stack);

			execution_stack.push(get_real(b, execution_stack) / get_real(a, execution_stack));
		}

		BUILTIN_DEF(MOD) {
			val a = pop(execution_stack), b = pop(execution_stack);

			execution_stack.push(get_int(b, execution_stack) % get_int(a, execution_stack));
		}



		BUILTIN_DEF(LESS) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) 
            { 
                execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) < get_int(b, execution_stack))); 
            }
            else if (is_string(a) && is_string(b))
            {
                execution_stack.push(static_cast<int64_t>(get_string(a, execution_stack) < get_string(b, execution_stack)));
            }
			else 
            { 
                execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) < get_real(b, execution_stack))); 
            }
		}

		BUILTIN_DEF(GREATER) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) 
            { 
                execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) > get_int(b, execution_stack))); 
            }
            else if (is_string(a) && is_string(b))
            {
                execution_stack.push(static_cast<int64_t>(get_string(a, execution_stack) > get_string(b, execution_stack)));
            }
			else 
            { 
                execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) > get_real(b, execution_stack))); 
            }
		}

		BUILTIN_DEF(EQUAL) {
			val a = pop(execution_stack), b = pop(execution_stack);

            if (is_int(a) && is_int(b))
            {
                execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) == get_int(b, execution_stack)));
            }
            else if (is_string(a) && is_string(b))
            {
                execution_stack.push(static_cast<int64_t>(get_string(a, execution_stack) == get_string(b, execution_stack)));
            }
            else if (is_command(a) && is_command(b))
            {
                execution_stack.push(static_cast<int64_t>(get_command(a, execution_stack) == get_command(b, execution_stack)));
            }
            else
            {
                execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) == get_real(b, execution_stack)));
            }
        }

		BUILTIN_DEF(LESS_EQ) {
			val a = pop(execution_stack), b = pop(execution_stack);

            if (is_int(a) && is_int(b))
            {
                execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) <= get_int(b, execution_stack)));
            }
            else if (is_string(a) && is_string(b))
            {
                execution_stack.push(static_cast<int64_t>(get_string(a, execution_stack) <= get_string(b, execution_stack)));
            }
            else
            {
                execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) <= get_real(b, execution_stack)));
            }
        }

		BUILTIN_DEF(GREATER_EQ) {
			val a = pop(execution_stack), b = pop(execution_stack);

            if (is_int(a) && is_int(b))
            {
                execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) >= get_int(b, execution_stack)));
            }
            else if (is_string(a) && is_string(b))
            {
                execution_stack.push(static_cast<int64_t>(get_string(a, execution_stack) >= get_string(b, execution_stack)));
            }
            else
            {
                execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) >= get_real(b, execution_stack)));
            }
        }

		BUILTIN_DEF(NOT_EQ) {
			val a = pop(execution_stack), b = pop(execution_stack);

            if (is_int(a) && is_int(b))
            {
                execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) != get_int(b, execution_stack)));
            }
            else if (is_string(a) && is_string(b))
            {
                execution_stack.push(static_cast<int64_t>(get_string(a, execution_stack) != get_string(b, execution_stack)));
            }
            else if (is_command(a) && is_command(b))
            {
                execution_stack.push(static_cast<int64_t>(get_command(a, execution_stack) != get_command(b, execution_stack)));
            }
            else
            {
                execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) != get_real(b, execution_stack)));
            }
        }



		BUILTIN_DEF(AND) {
			val a = pop(execution_stack), b = pop(execution_stack);

			execution_stack.push(static_cast<int64_t>(get_bool(a) && get_bool(b)));
		}

		BUILTIN_DEF(OR) {
			val a = pop(execution_stack), b = pop(execution_stack);

			execution_stack.push(static_cast<int64_t>(get_bool(a) || get_bool(b)));
		}

		BUILTIN_DEF(NOT) {
			val a = pop(execution_stack);

			execution_stack.push(static_cast<int64_t>(!get_bool(a)));
		}



        BUILTIN_DEF(DUPE) {
            val a = pop(execution_stack);

            execution_stack.push(a);
            execution_stack.push(a);
        }

        BUILTIN_DEF(DUPE_N) {
            int64_t n = get_int(pop(execution_stack), execution_stack);
            val a = pop(execution_stack);

            while (n--) { execution_stack.push(a); }
        }

        BUILTIN_DEF(DUPE_ALL) {
            stack copy = execution_stack;

            while (!copy.empty()) { execution_stack.push(pop(copy)); }
        }



		BUILTIN_DEF(POP) {
			pop(execution_stack);
		}

        BUILTIN_DEF(POP_N) {
            int64_t n = get_int(pop(execution_stack), execution_stack);
            while (n--) {pop(execution_stack);}
        }
        
        BUILTIN_DEF(POP_ALL) {
            execution_stack = stack();
        }



		BUILTIN_DEF(SWAP) {
			val a = pop(execution_stack), b = pop(execution_stack);

			execution_stack.push(a);
			execution_stack.push(b);
		}

        BUILTIN_DEF(FLIP_N) {
            int64_t n = get_int(pop(execution_stack), execution_stack);
            list execution_stack_list;
            
            while (n--) {execution_stack_list.push_back(pop(execution_stack));}
            
            for (auto& v : execution_stack_list) {execution_stack.push(v);}
        }

        BUILTIN_DEF(FLIP) {
            list execution_stack_list;

            while (!execution_stack.empty()) { execution_stack_list.push_back(pop(execution_stack)); }
            std::reverse(execution_stack_list.begin(), execution_stack_list.end());
            for (auto& v : execution_stack_list) { execution_stack.push(v); }
        }



        BUILTIN_DEF(EVAL) {
            list eval_list;

            while (!execution_stack.empty()) { eval_list.push_back(pop(execution_stack)); }
            std::reverse(eval_list.begin(), eval_list.end());
            for (auto& v : eval_list) { instruction_queue.push(v); }
        }     

        BUILTIN_DEF(EVAL_N) {
            int64_t n = get_int(pop(execution_stack), execution_stack);
            list eval_list;

            while (!execution_stack.empty() && n--) { eval_list.push_back(pop(execution_stack)); }
            std::reverse(eval_list.begin(), eval_list.end());
            for (auto& v : eval_list) { instruction_queue.push(v); }
        }

        BUILTIN_DEF(EVAL_KEEP) {
            stack copy_execution_stack = execution_stack;
            list eval_list;

            while (!copy_execution_stack.empty()) { eval_list.push_back(pop(copy_execution_stack)); }
            std::reverse(eval_list.begin(), eval_list.end());
            for (auto& v : eval_list) { instruction_queue.push(v); }
        }



        BUILTIN_DEF(ASSIGN) {
            std::string func_name = get_string(pop(execution_stack), execution_stack);
            val test_command = pop(execution_stack);

            if (is_command(test_command) && (get_command(test_command, execution_stack) == FEND))
            {
                int indend_level = 1;
                list func_body;
                val current_val;

                while (indend_level > 0 && !is_error(current_val))
                {
                    current_val = pop(execution_stack);
                    func_body.push_back(current_val);
                    if (is_command(current_val))
                    {
                        builtin current_builtin = get_command(current_val, execution_stack);
                        if (current_builtin == FBEGIN) { indend_level--; }
                        else if (current_builtin == FEND) { indend_level++; }
                    }
                }

                func_body.erase(func_body.end() - 1, func_body.end());
                std::reverse(func_body.begin(), func_body.end());
                funcs[func_name] = func_body;
            }
            else { funcs[func_name] = list{ test_command }; }
        }

        BUILTIN_DEF(IS_DEF) {
            std::string func_name = get_string(pop(execution_stack), execution_stack);
            execution_stack.push(static_cast<int64_t>(funcs[func_name].size() > 0));
        }

        BUILTIN_DEF(UNDEF) {
            std::string func_name = get_string(pop(execution_stack), execution_stack);
            funcs[func_name] = {};
        }



		BUILTIN_DEF(CONDITIONAL) {
			val a = pop(execution_stack), b = pop(execution_stack), c = pop(execution_stack);

			if (get_bool(a)) { execution_stack.push(b); } else { execution_stack.push(c); }			
		}

		

		BUILTIN_DEF(INVOKE) {
			val invoked_val = pop(execution_stack);
			std::string func_name = get_string(invoked_val, execution_stack);

			if (funcs[func_name].size() == 0)
			{ 
				if (is_command(invoked_val))
				{
					builtin invoked_builtin = get_command(invoked_val, execution_stack);
					auto builtin_iter = std::find_if(builtins_begin(), builtins_end(), [&invoked_builtin](auto& v) {return std::get<0>(v) == invoked_builtin; });
					if (builtin_iter != builtins_end())
					{
						if (std::get<0>(*builtin_iter) == FEND) 
						{ 
							execution_stack.push(invoked_val); 
							BUILTIN_FUNC(FSIZE)(execution_stack, instruction_queue); 
							int64_t n = get_int(pop(execution_stack), execution_stack);
							BUILTIN_FUNC(UNPACK)(execution_stack, instruction_queue); 
							execution_stack.push(n - 2); 
							BUILTIN_FUNC(EVAL_N)(execution_stack, instruction_queue); 
						}
						else std::get<2>(*builtin_iter)(execution_stack, instruction_queue); 
					}
					else execution_stack.push(error(std::string("BuiltinError: Unimplemented builtin.")));
				}
				else execution_stack.push(invoked_val);				
			}
			else
			{
				queue cur_instruction_queue = instruction_queue;
				queue new_instruction_queue;
				list func_body = funcs[func_name];

				for (val& v : func_body) { new_instruction_queue.push(v); }
				while (!cur_instruction_queue.empty()) { new_instruction_queue.push(pop(cur_instruction_queue)); }
				instruction_queue = new_instruction_queue;
			}
		}

		BUILTIN_DEF(INVOKE_PRINT_FUNC) {
			val invoked_val = pop(execution_stack);
			std::string func_name = get_string(invoked_val, execution_stack);

			if (funcs[func_name].size() == 0) { execution_stack.push(invoked_val); }
			else { list func_body = funcs[func_name]; for (val& v : func_body) { execution_stack.push(v); } }
		}

        BUILTIN_DEF(INVOKE_FORCE)
        {
            BUILTIN_FUNC(INVOKE)(execution_stack, instruction_queue);
        }



		BUILTIN_DEF(FBEGIN) {}

		BUILTIN_DEF(FEND) {}

        BUILTIN_DEF(FSIZE) {
            val sized_val = pop(execution_stack);

            if (is_command(sized_val) && (get_command(sized_val, execution_stack) == FEND))
            {
                int indend_level = 1;
                list func_body { sized_val };
                while (indend_level > 0 && !is_error(sized_val))
                {
                    
                    sized_val = pop(execution_stack);
                    func_body.push_back(sized_val);
                    if (is_command(sized_val))
                    {
                        builtin current_builtin = get_command(sized_val, execution_stack);
                        if (current_builtin == FBEGIN) { indend_level--; }
                        if (current_builtin == FEND) { indend_level++; }
                    }
                }

                int64_t func_size = func_body.size();
                std::reverse(func_body.begin(), func_body.end());
                for (val& v : func_body) { execution_stack.push(v); }
                execution_stack.push(func_size);
            }
            else { execution_stack.push(sized_val); execution_stack.push(static_cast<int64_t>(1)); }
        }

        BUILTIN_DEF(UNPACK) {
            BUILTIN_FUNC(FSIZE)(execution_stack, instruction_queue);

            int64_t function_block_size = get_int(pop(execution_stack), execution_stack);
            if (function_block_size >= 2)
            {
                pop(execution_stack);
                list function_block_body;
                while (--function_block_size > 1) { function_block_body.push_back(pop(execution_stack)); }
                pop(execution_stack);
                std::reverse(function_block_body.begin(), function_block_body.end());
                for (val& v : function_block_body) { execution_stack.push(v); }
            }
        }



		BUILTIN_DEF(QUOTE) {
			execution_stack.push(pop(instruction_queue));
		}

		BUILTIN_DEF(CONCAT) {
			execution_stack.push(get_string(pop(execution_stack), execution_stack) + get_string(pop(execution_stack), execution_stack));
		}

		

        BUILTIN_DEF(DEBUG_PRINT) {
            val v = pop(execution_stack);
            pretty_print_val(v);
        }

		

        BUILTIN_DEF(TO_INT) {
            execution_stack.push(get_int(pop(execution_stack), execution_stack));
        }

        BUILTIN_DEF(TO_REAL) {
            execution_stack.push(get_real(pop(execution_stack), execution_stack));
        }

        BUILTIN_DEF(TO_STRING) {
            execution_stack.push(get_string(pop(execution_stack), execution_stack));
        }

        BUILTIN_DEF(TO_COM) {
            execution_stack.push(get_command(pop(execution_stack), execution_stack));
        }

        BUILTIN_DEF(TO_BOOL) {
            execution_stack.push(static_cast<int64_t>(get_bool(pop(execution_stack))));
        }

		

        BUILTIN_DEF(READ_STR) {
            std::cout << "Insert string: ";
            std::string input_string;
            std::getline(std::cin, input_string);
            execution_stack.push(input_string);
        }

        BUILTIN_DEF(WRITE_STR) {
            std::cout << get_string(pop(execution_stack), execution_stack);
        }



        BUILTIN_DEF(STRING_GET) {
            std::string accessed_string = get_string(pop(execution_stack), execution_stack);
            int64_t access_offset = get_int(pop(execution_stack), execution_stack);

            if (access_offset >= static_cast<int64_t>(accessed_string.size())) {execution_stack.push(error("StringError: Trying to access a string out of bounds."s));}
            else 
            {
                char c = accessed_string[access_offset]; 
                accessed_string.clear(); 
                accessed_string += c; 
                execution_stack.push(accessed_string); 
            }
        }

        BUILTIN_DEF(STRING_SET) {
            std::string original_string = get_string(pop(execution_stack), execution_stack);
            int64_t replacement_offset = get_int(pop(execution_stack), execution_stack);
            std::string inserted_string = get_string(pop(execution_stack), execution_stack);

            if (replacement_offset >= static_cast<int64_t>(original_string.size())) { execution_stack.push(error("StringError: Trying to access a string out of bounds."s)); }
            else 
            {
                original_string.erase(original_string.begin() + replacement_offset, original_string.begin() + replacement_offset + 1); 
                std::copy(original_string.begin() + replacement_offset, original_string.end(), std::back_inserter(inserted_string)); 
                original_string.erase(original_string.begin() + replacement_offset, original_string.end()); 
                std::copy(inserted_string.begin(), inserted_string.end(), std::back_inserter(original_string)); 
                execution_stack.push(original_string);
            }
        }



        BUILTIN_DEF(BITWISE_AND) {
            execution_stack.push(get_int(pop(execution_stack), execution_stack) & get_int(pop(execution_stack), execution_stack));
        }

        BUILTIN_DEF(BITWISE_OR) {
            execution_stack.push(get_int(pop(execution_stack), execution_stack) | get_int(pop(execution_stack), execution_stack));
        }

        BUILTIN_DEF(BITWISE_NOT) {
            execution_stack.push(~get_int(pop(execution_stack), execution_stack));
        }



        BUILTIN_DEF(DIG) {
            int64_t depth = get_int(pop(execution_stack), execution_stack);
            list keep_list;

            while (depth--) {keep_list.push_back(pop(execution_stack));}
            val target_val = pop(execution_stack);

            std::reverse(keep_list.begin(), keep_list.end());
            for (auto& val : keep_list) {execution_stack.push(val);}
            execution_stack.push(target_val);
        }

        BUILTIN_DEF(BURY) {
            int64_t depth = get_int(pop(execution_stack), execution_stack);
            list keep_list;
            val target_val = pop(execution_stack);

            while (depth--) { keep_list.push_back(pop(execution_stack)); }
            execution_stack.push(target_val);
            std::reverse(keep_list.begin(), keep_list.end());
            for (auto& val : keep_list) { execution_stack.push(val); }
        }



        BUILTIN_DEF(GET_TYPE) {
            val tested_val = pop(execution_stack);
            if (is_int(tested_val)) {execution_stack.push(static_cast<int64_t>(0));}
            else if (is_real(tested_val)) { execution_stack.push(static_cast<int64_t>(1)); }
            else if (is_string(tested_val)) { execution_stack.push(static_cast<int64_t>(2)); }
            else if (is_command(tested_val)) { execution_stack.push(static_cast<int64_t>(3)); }
            else { execution_stack.push(static_cast<int64_t>(4)); }
        }


        
        BUILTIN_DEF(COUNTER) {
            static int64_t counter = 0;
            execution_stack.push(counter++);
        }

	}

	const std::vector<builtin_definition> builtins
	{
        BUILTIN(NOP, ".|"),
		BUILTIN(PLUS, "+"),	BUILTIN(MINUS, "-"), BUILTIN(MUL, "*"), BUILTIN(DIV, "/"), BUILTIN(MOD, "%"),
		BUILTIN(LESS, ">"),	BUILTIN(GREATER, "<"), BUILTIN(EQUAL, "=="), BUILTIN(LESS_EQ, ">="), BUILTIN(GREATER_EQ, "<="), BUILTIN(NOT_EQ, "<>"),
		BUILTIN(AND, "&&"), BUILTIN(OR, "||"), BUILTIN(NOT, "!"), 
        BUILTIN(DUPE, "&"), BUILTIN(DUPE_N, "&@"), BUILTIN(DUPE_ALL, "&!!"),
		BUILTIN(POP, "^"), BUILTIN(POP_N, "^@"), BUILTIN(POP_ALL, "^!!"),
        BUILTIN(SWAP, "$"), BUILTIN(FLIP_N, "$@"), BUILTIN(FLIP, "$!!"),
        BUILTIN(EVAL, "#"), BUILTIN(EVAL_N, "#@"), BUILTIN(EVAL_KEEP, "#!!"), 
        BUILTIN(CONDITIONAL, "?:"), 
        BUILTIN(ASSIGN, "="), BUILTIN(IS_DEF, "=?"), BUILTIN(UNDEF, "?"),
        BUILTIN(INVOKE, "`"), BUILTIN(INVOKE_PRINT_FUNC, "`\""), BUILTIN(INVOKE_FORCE, "`!!"),
		BUILTIN(FBEGIN, "{"), BUILTIN(FEND, "}"), BUILTIN(FSIZE, "@"), BUILTIN(UNPACK, ">/"),
        BUILTIN(QUOTE, "\""), BUILTIN(CONCAT, ".."),
        BUILTIN(TO_INT, "_"), BUILTIN(TO_REAL, "_."), BUILTIN(TO_STRING, "_\""), BUILTIN(TO_COM, "_!!"), BUILTIN(TO_BOOL, "_?"),
        BUILTIN(READ_STR, "(~"), BUILTIN(WRITE_STR, ")~"),
        BUILTIN(STRING_GET, "~["), BUILTIN(STRING_SET, "~]"),
        BUILTIN(BITWISE_AND, "/&"), BUILTIN(BITWISE_OR, "/|"), BUILTIN(BITWISE_NOT, "/~"),
        BUILTIN(DIG, "%^"), BUILTIN(BURY, "%|"),
		BUILTIN(DEBUG_PRINT, "[=]"),
        BUILTIN(GET_TYPE, "*?"),
        BUILTIN(COUNTER, "++")		
	};

	std::vector<builtin_definition>::const_iterator builtins_begin() { return builtins.begin(); };
	std::vector<builtin_definition>::const_iterator builtins_end() { return builtins.end(); };
}