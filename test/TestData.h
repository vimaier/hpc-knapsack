#ifndef TEST_DATA_H_
#define TEST_DATA_H_

/* Content of text file
15.0 4 5
XXL blue 0x   02.0 2.00
gray mouse    01.0 2.00
big green box 12.0 4.00
yellow daisy  04.0 10.00
salmon mousse 01.0 1.00
 */
static const char* KNAPSACK_INPUT_FILE = "res/KnapSackItemsForUnittest.txt";

/* Content of text file. Same as above but with more whitespace.
15.0 4 5
XXL blue 0x                  2.0 2.0
gray mouse                    1.0 2.0
big green box                 12.0 4.0
yellow daisy                   4.0 10.0
salmon mousse                 1.0 1.0
 */
static const char* KNAPSACK_INPUT_FILE_FIRST_EXAMPLE = "res/firstFileExample.txt";

std::string* ITEM__NAME_1 = new std::string("XXL blue 0x");
const KnapSackItem TEST_ITEM_1 = {ITEM__NAME_1, 2.0, 2.0};

std::string* ITEM__NAME_2 = new std::string("gray mouse");
const KnapSackItem TEST_ITEM_2 = {ITEM__NAME_2, 1.0, 2.0};

std::string* ITEM__NAME_3 = new std::string("big green box");
const KnapSackItem TEST_ITEM_3 = {ITEM__NAME_3, 12.0, 4.0};

std::string* ITEM__NAME_4 = new std::string("yellow daisy");
const KnapSackItem TEST_ITEM_4 = {ITEM__NAME_4, 4.0, 10.0};

std::string* ITEM__NAME_5 = new std::string("salmon mousse");
const KnapSackItem TEST_ITEM_5 = {ITEM__NAME_5, 1.0, 1.0};

/* Expected Solution of KNAPSACK_INPUT_FILE_FIRST_EXAMPLE
 * -----------------------------------
 * 3x gray mouse -> 3 weight, 6 worth
 * 3x yellow daisy -> 12 weight, 30 worth
 * -----------------------------------
 * overall 15 weight and 36 worth
 */
const std::string ASSUMED_CONTENT_FILE_1[] {"Capacity;15.0", "gray mouse;3", "yellow daisy;3", "Total weight;15.00", "Total worth;36.00"};

/**
 * Same solution as ASSUMED_CONTENT_FILE_1 but inverses the order of the items.
 */
const std::string ASSUMED_CONTENT_FILE_1_DIFFERENT_ORDER_OF_ITEMS[] {"Capacity;15.0", "yellow daisy;3", "gray mouse;3", "Total weight;15.00", "Total worth;36.00"};

/**
 * Number of elements of ASSUMED_CONTENT_FILE_1[] and ASSUMED_CONTENT_FILE_1_DIFFERENT_ORDER_OF_ITEMS[]
 */
const int ASSUMED_CONTENT_LINES_FILE_1 = 5;

/* Content of text file
15.0 1 6
XXL blue Ox           2.0 2.0
gray mouse            1.0 2.0
big green box        12.0 4.0
yellow daisy           4.0 10.0
salmon mousse    1.0 1.0
9780596521530  1.54 44.99
 */
static const char* KNAPSACK_INPUT_FILE_SECOND_EXAMPLE = "res/secondFileExample.txt";

// Only one new item in this file.
std::string* ITEM__NAME_6 = new std::string("9780596521530");
const KnapSackItem TEST_ITEM_6 = {ITEM__NAME_6, 1.54, 44.99};

/**Expected Solution of KNAPSACK_INPUT_FILE_SECOND_EXAMPLE
The items to fit into the 15.0 knapsack are:
1 gray mouse
1 9780596521530
1 yellow daisy
1 salmon mousse
1 XXL blue Ox
Total capacity used: 9.54
Total value: 59.99
 */
const std::string ASSUMED_CONTENT_FILE_2[] {"Capacity;15.0", "XXL blue 0x;1", "gray mouse;1", "yellow daisy;1", "salmon mousse;1", "9780596521530;1", "Total weight;9.54", "Total worth;59.99"};

/**
 * Same solution as ASSUMED_CONTENT_FILE_2 but inverses the order of the items.
 */
const std::string ASSUMED_CONTENT_FILE_2_DIFFERENT_ORDER[] {"Capacity;15.0", "9780596521530;1", "yellow daisy;1", "XXL blue 0x;1", "gray mouse;1", "salmon mousse;1",  "Total weight;9.54", "Total worth;59.99"};

/**
 * Number of elements of ASSUMED_CONTENT_FILE_2[] and ASSUMED_CONTENT_FILE_2_DIFFERENT_ORDER[]
 */
const int ASSUMED_CONTENT_LINES_FILE_2 = 8;


/* Content of text file
645.0 7 8
EINS                      153.0 232.0
ZWEI                      54.0 73.0
DREI                     191.0 201.0
VIERE                     66.0 50.0
FUENF                     239.0 141.0
SECHS                     137.0 79.0
SIEBEN                   148.0 48.0
ACHT                      249.0 38.0
 */
static const char* KNAPSACK_INPUT_FILE_THIRD_EXAMPLE = "res/thirdFileExample.txt";

std::string* ITEM__EINS = new std::string("EINS");
const KnapSackItem TEST_ITEM_EINS = {ITEM__EINS, 153.0, 232.0};

std::string* ITEM__ZWEI = new std::string("ZWEI");
const KnapSackItem TEST_ITEM_ZWEI = {ITEM__ZWEI, 54.0, 73.0};

std::string* ITEM__DREI = new std::string("DREI");
const KnapSackItem TEST_ITEM_DREI = {ITEM__DREI, 191.0, 201.0};

std::string* ITEM__VIERE = new std::string("VIERE");
const KnapSackItem TEST_ITEM_VIERE = {ITEM__VIERE, 66.0, 50.0};

std::string* ITEM__FUENF = new std::string("FUENF");
const KnapSackItem TEST_ITEM_FUENF = {ITEM__FUENF, 239.0, 141.0};

std::string* ITEM__SECHS = new std::string("SECHS");
const KnapSackItem TEST_ITEM_SECHS = {ITEM__SECHS, 137.0, 79.0};

std::string* ITEM__SIEBEN = new std::string("SIEBEN");
const KnapSackItem TEST_ITEM_SIEBEN = {ITEM__SIEBEN, 148.0, 48.0};

std::string* ITEM__ACHT = new std::string("ACHT");
const KnapSackItem TEST_ITEM_ACHT = {ITEM__ACHT, 249.0, 38.0};

/**Expected Solution of KNAPSACK_INPUT_FILE_THIRD_EXAMPLE
The items to fit into the 645.0 knapsack are:
4x EINS
Total capacity used: 612.00
Total value: 928.00
 */
const std::string ASSUMED_CONTENT_FILE_3[] {"Capacity;645.0", "EINS;4", "Total weight;612.00", "Total worth;928.00"};

/**
 * Number of elements of ASSUMED_CONTENT_FILE_3[]
 */
const int ASSUMED_CONTENT_LINES_FILE_3 = 4;


/* Content of text file
5.0 1 4
item_01                 2.0 3.0
item_02                 3.0 4.0
item_03                 4.0 5.0
item_04                 5.0 6.0
 */
static const char* KNAPSACK_INPUT_FILE_DP_EXAMPLE = "res/dynamicProgrammingExample.txt";

std::string* ITEM__DP_01 = new std::string("item_01");
const KnapSackItem TEST_ITEM_DP_01 = {ITEM__DP_01, 2.0, 3.0};

std::string* ITEM__DP_02 = new std::string("item_02");
const KnapSackItem TEST_ITEM_DP_02 = {ITEM__DP_02, 3.0, 4.0};

std::string* ITEM__DP_03 = new std::string("item_03");
const KnapSackItem TEST_ITEM_DP_03 = {ITEM__DP_03, 4.0, 5.0};

std::string* ITEM__DP_04 = new std::string("item_04");
const KnapSackItem TEST_ITEM_DP_04 = {ITEM__DP_04, 5.0, 6.0};

/* Expected Solution
 * -----------------------------------
 * 1x item_02 -> 3 weight, 4 worth
 * 1x item_01 -> 2 weight, 3 worth
 * -----------------------------------
 * overall 5 weight and 7 worth
*/
const std::string ASSUMED_CONTENT_FILE_DP[] {"Capacity;5.0", "item_02;1", "item_01;1", "Total weight;5.00", "Total worth;7.00"};

/**
 * Same solution as ASSUMED_CONTENT_FILE_DP but inverses the order of the items.
 */
const std::string ASSUMED_CONTENT_FILE_DP_DIFFERENT_ORDER[] {"Capacity;5.0", "item_01;1", "item_02;1", "Total weight;5.00", "Total worth;7.00"};

/**
 * Number of elements of ASSUMED_CONTENT_FILE_DP[] and ASSUMED_CONTENT_FILE_DP_DIFFERENT_ORDER[]
 */
const int ASSUMED_CONTENT_LINES_FILE_DP = 5;

/**
 * The file to where the test output is written to
 */
const char* TEST_OUTPUT_FILE = "outputForTesting.txt";

#endif /* TEST_DATA_H_ */
