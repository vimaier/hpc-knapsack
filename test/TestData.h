#ifndef TEST_DATA_H_
#define TEST_DATA_H_

static const char* KNAPSACK_INPUT_FILE = "../hpc-knapsack/res/KnapSackItemsForUnittest.txt";
/* Content of text file
15.0 4 5
XXL blue 0x   02.0 2.00
gray mouse    01.0 2.00
big green box 12.0 4.00
yellow daisy  04.0 10.00
salmon mousse 01.0 1.00

 */

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


// First example file

static const char* KNAPSACK_INPUT_FILE_FIRST_EXAMPLE = "../hpc-knapsack/res/firstFileExample.txt";
/* Content of text file. Same as above but with more whitespace.
15.0 4 5
XXL blue 0x                  2.0 2.0
gray mouse                    1.0 2.0
big green box                 12.0 4.0
yellow daisy                   4.0 10.0
salmon mousse                 1.0 1.0
 */

//  The items are the same as in KnAPSACK_INPUT_FILE


// Second example file

static const char* KNAPSACK_INPUT_FILE_SECOND_EXAMPLE = "../hpc-knapsack/res/secondFileExample.txt";
/* Content of text file
15.0 1 6
XXL blue Ox           2.0 2.0
gray mouse            1.0 2.0
big green box        12.0 4.0
yellow daisy           4.0 10.0
salmon mousse    1.0 1.0
9780596521530  1.54 44.99
 */

// Only one new item in this file.
std::string* ITEM__NAME_6 = new std::string("9780596521530");
const KnapSackItem TEST_ITEM_6 = {ITEM__NAME_6, 1.54, 44.99};


// Third example file

static const char* KNAPSACK_INPUT_FILE_THIRD_EXAMPLE = "../hpc-knapsack/res/thirdFileExample.txt";
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


#endif /* TEST_DATA_H_ */
