#pragma once
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

namespace froth
{
	template <typename T, typename ConT>
	bool is_contained(T val, ConT con) { return std::find(std::begin(con), std::end(con), val) != std::end(con); }

	std::string trim(std::string_view str) { std::string r; std::copy_if(str.begin(), str.end(), std::back_inserter(r), [](char c) {return !std::isspace(c); }); return r; }

	std::vector<std::string> split(std::string& str, const std::string& delim)
	{
		std::vector<std::string> ret;
		size_t pos = 0;
		while ((pos = str.find(delim)) != std::string::npos) {
			std::string s = str.substr(0, pos);
			if (trim(s) != "") { ret.push_back(trim(s)); }
			str.erase(0, pos + delim.length());
		}
		if (trim(str) != "") { ret.push_back(str); }
		return ret;
	}
}