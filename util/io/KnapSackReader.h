#ifndef IO_KNAPSACKREADER_H_
#define IO_KNAPSACKREADER_H_

#include "main/KnapSack.h"
#include "util/StringUtils.h"
#include <cstdlib>
#include <fstream>
#include <string>

/**
 *  Helper class used to interpret knapsack problems from input files.
 *
 *	Example File:
 *
 *	------------------------
 *	10.0 4 2
 *	XXL blue Ox		3.0 2.00
 *	gray mouse		1.0 2.45
 *	------------------------
 *
 *	Means:
 *	Capacity = 10.0
 *	MaxNumPerItem = 4
 *	NumOfItems = 2
 *	Item 1: Name(XXL blue Ox), Weight(3.0), Worth(2.00)
 *	Item 2: Name(gray mouse), Weight(1.0), Worth(2.45)
 *	Itemnames are always STRLENGTH_ITEMNAME characters long
 *
 */
class KnapSackReader{
private:
	//Input file constraints
	static const int STRLENGTH_ITEMNAME = 13;
	KnapSackReader();

public:

	/**
	 * Reads the knapsack problem file found at the given path and
	 * creates a KnapSack object representing the read problem.
	 * Returns the created knapsack.
	 */
	static KnapSack readKnapSackFrom(const char* fileName);
	
};

#endif /* IO_KNAPSACKREADER_H_ */
