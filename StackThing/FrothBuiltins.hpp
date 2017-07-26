#pragma once
#include <functional>
#include <tuple>
#include <vector>
#include <string>
#include "FrothFuncs.hpp"

#define BUILTIN_DEF(x) void BUILTIN ## x (stack& execution_stack, queue& instruction_queue)
#define BUILTIN_FUNC(x) __builtins::BUILTIN ## x
#define BUILTIN(x, s) {##x,##s,BUILTIN_FUNC(x)}

namespace froth
{
	namespace __builtins
	{
		BUILTIN_DEF(EVAL_N);
		BUILTIN_DEF(FSIZE);
		BUILTIN_DEF(UNPACK);

        BUILTIN_DEF(NOP) {}



		BUILTIN_DEF(PLUS) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) { execution_stack.push(get_int(a, execution_stack) + get_int(b, execution_stack)); }
			else { execution_stack.push(get_real(a, execution_stack) + get_real(b, execution_stack)); }
		}

		BUILTIN_DEF(MINUS) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) { execution_stack.push(get_int(b, execution_stack) + get_int(a, execution_stack)); }
			else { execution_stack.push(get_real(b, execution_stack) + get_real(a, execution_stack)); }
		}

		BUILTIN_DEF(MUL) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) { execution_stack.push(get_int(b, execution_stack) * get_int(a, execution_stack)); }
			else { execution_stack.push(get_real(b, execution_stack) * get_real(a, execution_stack)); }
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

			if (is_int(a) && is_int(b)) { execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) < get_int(b, execution_stack))); }
			else { execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) < get_real(b, execution_stack))); }
		}

		BUILTIN_DEF(GREATER) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) { execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) > get_int(b, execution_stack))); }
			else { execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) > get_real(b, execution_stack))); }
		}

		BUILTIN_DEF(EQUAL) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) { execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) == get_int(b, execution_stack))); }
			else { execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) == get_real(b, execution_stack))); }
		}

		BUILTIN_DEF(LESS_EQ) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) { execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) <= get_int(b, execution_stack))); }
			else { execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) <= get_real(b, execution_stack))); }
		}

		BUILTIN_DEF(GREATER_EQ) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) { execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) >= get_int(b, execution_stack))); }
			else { execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) >= get_real(b, execution_stack))); }
		}

		BUILTIN_DEF(NOT_EQ ) {
			val a = pop(execution_stack), b = pop(execution_stack);

			if (is_int(a) && is_int(b)) { execution_stack.push(static_cast<int64_t>(get_int(a, execution_stack) != get_int(b, execution_stack))); }
			else { execution_stack.push(static_cast<int64_t>(get_real(a, execution_stack) != get_real(b, execution_stack))); }
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
            while (!execution_stack.empty()) { pop(execution_stack); }
        }



		BUILTIN_DEF(SWAP) {
			val a = pop(execution_stack), b = pop(execution_stack);

			execution_stack.push(a);
			execution_stack.push(b);
		}

        BUILTIN_DEF(FLIP_N) {
            int64_t n = get_int(pop(execution_stack), execution_stack);
            list execution_stack_list;
            
            while(n--) {execution_stack_list.push_back(pop(execution_stack));}
            
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
            int n = get_int(pop(execution_stack), execution_stack);
            list eval_list;

            while (!execution_stack.empty() && n--> 0) { eval_list.push_back(pop(execution_stack)); }
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
            std::string fname = get_string(pop(execution_stack), execution_stack);
            val com = pop(execution_stack);
            command c(NOP);

            if (is_command(com) && (c = get_command(com, execution_stack), c.com == FEND))
            {
                int indend = 1;
                list func_body;
                while (indend > 0 && !is_error(com))
                {
                    com = pop(execution_stack);
                    func_body.push_back(com);
                    if (is_command(com))
                    {
                        c = get_command(com, execution_stack);
                        if (c.com == FBEGIN) { indend--; }
                        if (c.com == FEND) { indend++; }
                    }
                }

                func_body.erase(func_body.end() - 1, func_body.end());
                std::reverse(func_body.begin(), func_body.end());
                funcs[fname] = func_body;
            }
            else { funcs[fname] = list{ com }; }
        }

        BUILTIN_DEF(IS_DEF) {
            val name = pop(execution_stack);
            std::string fname = get_string(name, execution_stack);

            execution_stack.push(static_cast<int64_t>(funcs[fname].size() > 0));
        }

        BUILTIN_DEF(UNDEF) {
            std::string fname = get_string(pop(execution_stack), execution_stack);
            funcs[fname] = {};
        }



		BUILTIN_DEF(CONDITIONAL) {
			val a = pop(execution_stack), b = pop(execution_stack), c = pop(execution_stack);

			if (get_bool(a)) { execution_stack.push(b); }
			else { execution_stack.push(c); }
		}

		

		BUILTIN_DEF(INVOKE) {
			val name = pop(execution_stack);
			std::string fname = get_string(name, execution_stack);

			if (funcs[fname].size() == 0) 
			{ 
				if (is_command(name))
				{
					command c = get_command(name, execution_stack);
					auto builtin_iter = std::find_if(builtins_begin(), builtins_end(), [&c](auto& v) {return std::get<0>(v) == c.com; });
					if (builtin_iter != builtins_end())
					{
						if (std::get<0>(*builtin_iter) == FEND) 
						{ 
							execution_stack.push(name); 
							BUILTIN_FUNC(FSIZE)(execution_stack, instruction_queue); 
							int64_t n = get_int(pop(execution_stack), execution_stack);
							BUILTIN_FUNC(UNPACK)(execution_stack, instruction_queue); 
							execution_stack.push(n - 2); 
							BUILTIN_FUNC(EVAL_N)(execution_stack, instruction_queue); 
						}
						else { std::get<2>(*builtin_iter)(execution_stack, instruction_queue); }
					}
					else execution_stack.push(error(std::string("LolwutError: Unimplemented builtin.")));
				}
				else
				{
					execution_stack.push(name);
				}
			}
			else
			{
				queue cur_instruction_queue = instruction_queue;
				queue new_instruction_queue;
				list func_body = funcs[fname];

				for (val& v : func_body) { new_instruction_queue.push(v); }
				while (!cur_instruction_queue.empty()) { new_instruction_queue.push(pop(cur_instruction_queue)); }
				instruction_queue = new_instruction_queue;
			}
		}

		BUILTIN_DEF(INVOKE_PRINT_FUNC) {
			val name = pop(execution_stack);
			std::string fname = get_string(name, execution_stack);

			if (funcs[fname].size() == 0) { execution_stack.push(name); }
			else { list func_body = funcs[fname]; for (val& v : func_body) { execution_stack.push(v); } }
		}

        BUILTIN_DEF(INVOKE_FORCE)
        {
            val name = pop(execution_stack);
            std::string fname = get_string(name, execution_stack);

            if (funcs[fname].size() == 0)
            {
                if (is_command(name))
                {
                    command c = get_command(name, execution_stack);
                    auto builtin_iter = std::find_if(builtins_begin(), builtins_end(), [&c](auto& v) {return std::get<0>(v) == c.com; });
                    if (builtin_iter != builtins_end())
                    {
                        if (std::get<0>(*builtin_iter) == FEND)
                        {
                            execution_stack.push(name);
                            BUILTIN_FUNC(FSIZE)(execution_stack, instruction_queue);
                            int64_t n = get_int(pop(execution_stack), execution_stack);
                            BUILTIN_FUNC(UNPACK)(execution_stack, instruction_queue);
                            execution_stack.push(n - 2);
                            BUILTIN_FUNC(EVAL_N)(execution_stack, instruction_queue);
                        }
                        else { std::get<2>(*builtin_iter)(execution_stack, instruction_queue); }
                    }
                    else execution_stack.push(error(std::string("LolwutError: Unimplemented builtin.")));
                }
                else
                {
                    execution_stack.push(name);
                }
            }
        }



		BUILTIN_DEF(FBEGIN) {}

		BUILTIN_DEF(FEND) {}

        BUILTIN_DEF(FSIZE) {


            val com = pop(execution_stack);
            command c(NOP);

            if (is_command(com) && (c = get_command(com, execution_stack), c.com == FEND))
            {
                int indend = 1;
                list func_body{ com };
                while (indend > 0 && !is_error(com))
                {
                    com = pop(execution_stack);
                    func_body.push_back(com);
                    if (is_command(com))
                    {
                        c = get_command(com, execution_stack);
                        if (c.com == FBEGIN) { indend--; }
                        if (c.com == FEND) { indend++; }
                    }
                }

                int64_t k = func_body.size();
                std::reverse(func_body.begin(), func_body.end());
                for (val& v : func_body) { execution_stack.push(v); }
                execution_stack.push(k);
            }
            else { execution_stack.push(com); execution_stack.push(static_cast<int64_t>(1)); }
        }

        BUILTIN_DEF(UNPACK) {
            BUILTIN_FUNC(FSIZE)(execution_stack, instruction_queue);

            //print_container(execution_stack);

            int64_t siz = get_int(pop(execution_stack), execution_stack);
            if (siz >= 2)
            {
                pop(execution_stack);
                list vals;
                while (--siz > 1) { vals.push_back(pop(execution_stack)); }
                pop(execution_stack);
                std::reverse(vals.begin(), vals.end());
                for (val& v : vals) { execution_stack.push(v); }
            }

            //print_container(execution_stack);
        }



		BUILTIN_DEF(QUOTE) {
			execution_stack.push(pop(instruction_queue));
		}

		BUILTIN_DEF(CONCAT) {
			execution_stack.push(get_string(pop(execution_stack), execution_stack) + get_string(pop(execution_stack), execution_stack));
		}

		

        BUILTIN_DEF(DEBUG_PRINT) {
            val v = pop(execution_stack);
            std::cout << "\n" << get_type_string(v) << " | " << get_string(v, execution_stack) << "\n";
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
            std::string s;
            std::getline(std::cin, s);
            execution_stack.push(s);
        }

        BUILTIN_DEF(WRITE_STR) {
            std::cout << get_string(pop(execution_stack), execution_stack);
        }



        BUILTIN_DEF(STRING_GET) {
            std::string str = get_string(pop(execution_stack), execution_stack);
            int64_t n = get_int(pop(execution_stack), execution_stack);

            if (n >= str.size()) {execution_stack.push(error("StringError: Trying to access a string out of bounds."s));}
            else {char c = str[n]; str.clear(); str += c; execution_stack.push(str); }
        }

        BUILTIN_DEF(STRING_SET) {
            std::string str = get_string(pop(execution_stack), execution_stack);
            int64_t n = get_int(pop(execution_stack), execution_stack);
            std::string rep = get_string(pop(execution_stack), execution_stack);

            if (n >= str.size()) { execution_stack.push(error("StringError: Trying to access a string out of bounds."s)); }
            else 
            {
                str.erase(str.begin() + n, str.begin() + n + 1); 
                std::copy(str.begin() + n, str.end(), std::back_inserter(rep)); 
                str.erase(str.begin() + n, str.end); 
                std::copy(rep.begin(), rep.end(), std::back_inserter(str)); 
                execution_stack.push(str);
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
            int64_t n = get_int(pop(execution_stack), execution_stack);
            list keep_list;
            while (n--) {keep_list.push_back(pop(execution_stack));}
            val v = pop(execution_stack);
            std::reverse(keep_list.begin(), keep_list.end());
            for (auto& val : keep_list) {execution_stack.push(val);}
            execution_stack.push(v);
        }

        BUILTIN_DEF(BURY) {
            int64_t n = get_int(pop(execution_stack), execution_stack);
            list keep_list;
            val v = pop(execution_stack);
            while (n--) { keep_list.push_back(pop(execution_stack)); }
            execution_stack.push(v);
            std::reverse(keep_list.begin(), keep_list.end());
            for (auto& val : keep_list) { execution_stack.push(val); }
        }



        BUILTIN_DEF(GET_TYPE) {
            val v = pop(execution_stack);
            if (is_int(v)) {execution_stack.push(static_cast<int64_t>(0));}
            else if (is_real(v)) { execution_stack.push(static_cast<int64_t>(1)); }
            else if (is_string(v)) { execution_stack.push(static_cast<int64_t>(2)); }
            else if (is_command(v)) { execution_stack.push(static_cast<int64_t>(3)); }
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