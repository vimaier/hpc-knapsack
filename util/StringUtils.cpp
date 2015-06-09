/*
 * StringUtils.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: vimaier
 */

#include "StringUtils.h"


std::vector<std::string> StringUtils::split(std::string str, char delimiter) {
	std::vector<std::string> internal;
	std::stringstream ss(str);
	std::string tok;

	while (std::getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}
