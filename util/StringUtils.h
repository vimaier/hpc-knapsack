#ifndef UTIL_STRINGUTILS_H_
#define UTIL_STRINGUTILS_H_

#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <vector>
#include <sstream>

/**
 * Helper class which provides string helper functions
 */
class StringUtils {
public:
	/**
	 * Trims white spaces from the beginning of the given string
	 */
	static inline std::string& ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	/**
	 * Trims white spaces from the end of the given string
	 */
	static inline std::string& rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	/**
	 * Trims white spaces from the beginning and the end of the given string
	 */
	static inline std::string& trim(std::string &s) {
		return ltrim(rtrim(s));
	}

	/**
	 * Removes all spaces from the given string
	 */
	static inline std::string& removeAllSpaces(std::string &s) {
		std::string::iterator end_pos = std::remove(s.begin(), s.end(), ' ');
		s.erase(end_pos, s.end());
		return s;
	}

	static std::vector<std::string> split(std::string str, char delimiter){
		std::vector<std::string> internal;
		std::stringstream ss(str);
		std::string tok;

		while (std::getline(ss, tok, delimiter)) {
			internal.push_back(tok);
		}

		return internal;
	}

};

#endif /* UTIL_STRINGUTILS_H_ */
