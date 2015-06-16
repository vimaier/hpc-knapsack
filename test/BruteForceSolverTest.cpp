/**
 * Tests whether the brute force algorithm for solving the knapsack problem works correctly.
 */

#include "main/algorithms/BruteForceSolver.h"

const char* KNAPSACK_INPUT_FILE = "../hpc-knapsack/res/KnapSackItemsForUnittest.txt";
/* Content of text file
15.0 4 5
XXL blue Ox   02.0 2.00
gray mouse    01.0 2.00
big green box 12.0 4.00
yellow daisy  04.0 10.00
salmon mousse 01.0 1.00
 */

/* Expected Solution
 * -----------------------------------
 * 3x yellow daisy -> 12 weight, 30 worth
 * 3x gray mouse -> 3 weight, 6 worth
 * -----------------------------------
 * overall 15 weight and 36 worth
*/

const char* KNAPSACK_OUTPUT_FILE = "outputForTesting.txt";
