#pragma once
#include <vector>
#include <stack>
#include <variant>
#include <cstdint>
#include <string>
#include <queue>
#include <unordered_map>
#include <functional>

using std::string_literals::operator ""s;

namespace froth
{
	enum builtin : uint8_t {
		NOP, 
        PLUS, MINUS, MUL, DIV, MOD, 
        LESS, GREATER, EQUAL, LESS_EQ, GREATER_EQ, NOT_EQ,
		AND, OR, NOT,
        DUPE, DUPE_N, DUPE_ALL,
        POP, POP_N, POP_ALL,
        SWAP, FLIP_N, FLIP,
        EVAL, EVAL_N, EVAL_KEEP,
        ASSIGN, IS_DEF, UNDEF,
        INVOKE, INVOKE_PRINT_FUNC, INVOKE_FORCE,
        FBEGIN, FEND, FSIZE, UNPACK,
        QUOTE, CONCAT,
        DEBUG_PRINT,
        TO_INT, TO_REAL, TO_STRING, TO_COM, TO_BOOL,
        READ_STR, WRITE_STR,
        STRING_GET, STRING_SET,
        BITWISE_AND, BITWISE_OR, BITWISE_NOT,
        DIG, BURY,
        CONDITIONAL,    
        GET_TYPE,
        COUNTER
	};
	
	struct command
	{
		command(builtin c) : com(c) {};
		command() : com(NOP) {};
		builtin com;
	};

	struct error
	{
		error(const std::string& s) : what(s) {};

		std::string what;
	};

	using val = std::variant<double, int64_t, std::string, command, error>;
	using queue = std::queue<val>;
	using list = std::vector<val>;
	using stack = std::stack<val>;
    using builtin_definition = std::tuple<builtin, const char*, std::function<void(stack&, queue&)>>;

	static const std::unordered_map<std::string, std::string> stdlib
	{
		{ "__inc", "{ 0 __intr_ctr __intr_ctr ? ?: ` 1 + __intr_ctr = __intr_ctr ` } __inc = " },
		{ "inc", "{ 0 __counter __counter ? ?: ` 1 + __counter = __counter ` } inc = " },
		{ "ctr", "{ 0 __counter __counter ? ?: ` } ctr = " },
		{ "succ", "{ 0 __counter __counter ? ?: ` 1 + __counter = } succ = " },
		{ "res", "{ 0 __counter = } res = " },
		{ "while", "{ __inc ` __w_cr = __w_check __w_cr ` .. __w_ch = __w_body __w_cr ` .. __w_bd = __w_loop __w_cr ` .. __w_lp = __w_ch ` = __w_lp ` $ \" ` $ __w_bd ` = { __w_bd `!! /\\ __w_ch `!! ` ?: ` } __w_lp ` = __w_lp ` ` } while = "},
	};

	static std::unordered_map<std::string, std::vector<val>> funcs{};

	static stack unused_stack;

	std::vector<builtin_definition>::const_iterator builtins_begin();
	std::vector<builtin_definition>::const_iterator builtins_end();

	//void Invoke(stack& stack, queue& queue);
}