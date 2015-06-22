#include "main/algorithms/BruteForceSolver.h"
using namespace std;

static const char* FIRST_KNAPSACK_INPUT_FILE = "../res/firstFileExample.txt";
static const char* SECOND_KNAPSACK_INPUT_FILE = "../res/secondFileExample.txt";
static const char* THIRD_KNAPSACK_INPUT_FILE = "../res/thirdFileExample.txt";
static const char* KNAPSACK_OUTPUT_FILE = "knapSackOut.txt";

int main(int argc, char* argv[]){

	BruteForceSolver* solver = new BruteForceSolver(FIRST_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);

	solver->start();
}
