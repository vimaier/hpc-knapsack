#include <omp.h>
#include <stdio.h>

#include "main/algorithms/BruteForceSolver.h"
#include "main/algorithms/DynamicProgrammingSolver.h"
#include "main/algorithms/DynamicProgrammingParallelSolver.h"
#include "main/algorithms/DynamicProgrammingLowMemorySolver.h"
#include "main/algorithms/DynamicProgrammingLowMemoryParallelSolver.h"
#include "main/algorithms/NemhauserUllmannSolver.h"
#include "main/algorithms/NemhauserUllmannParallelSolver.h"
#include "main/algorithms/NemhauserUllmannSolverRLP.h"
#include "main/algorithms/NemhauserUllmannRLPParallelSolver.h"
using namespace std;

#define PRINT_VERBOSE

static const char* FIRST_KNAPSACK_INPUT_FILE = "res/firstFileExample.txt";
static const char* SECOND_KNAPSACK_INPUT_FILE = "res/secondFileExample.txt";
static const char* THIRD_KNAPSACK_INPUT_FILE = "res/thirdFileExample.txt";
static const char* FOURTH_KNAPSACK_INPUT_FILE = "res/fourthFileExample.txt";
static const char* FIFTH_KNAPSACK_INPUT_FILE = "res/fifthFileExample.txt";
static const char* SIXTH_KNAPSACK_INPUT_FILE = "res/sixthFileExample.txt";
static const char* SEVENTH_KNAPSACK_INPUT_FILE = "res/seventhFileExample.txt";
static const char* DP_INPUT_FILE = "res/dynamicProgrammingExample.txt";
static const char* SECOND_DP_INPUT_FILE = "res/dpExample.txt";
static const char* KNAPSACK_OUTPUT_FILE = "knapSackOut.txt";

/**
 * Solves the knapsack problem found within the given input file
 * by applying the brute force algorithm n times, where n equals the numOfExecutions parameter.
 */
void executeBruteForceSolver(const char* inputFile, int numOfExecutions=1){
	KnapSackSolver* solver = new BruteForceSolver(inputFile, KNAPSACK_OUTPUT_FILE, numOfExecutions);
	solver->start();
	delete solver;
}

/**
 * Solves the knapsack problem found within the given input file
 * by applying the nemhauser ullman algorithm n times, where n equals the numOfExecutions parameter.
 */
void executeNemhauserUllmanSolver(const char* inputFile, const int numOfExecutions=1) {
	KnapSackSolver* solver = new NemhauserUllmannSolver(inputFile, KNAPSACK_OUTPUT_FILE, numOfExecutions);
	solver->start();
	delete solver;
}

/**
 * Solves the knapsack problem found within the given input file
 * by applying the parallel nemhauser ullman algorithm n times, where n equals the numOfExecutions parameter.
 */
void executeNemhauserUllmanParallelSolver(const char* inputFile, int numOfExecutions=1) {
	KnapSackSolver* solver = new NemhauserUllmannParallelSolver(inputFile, KNAPSACK_OUTPUT_FILE, numOfExecutions);
	solver->start();
	delete solver;
}

/**
 * Solves the knapsack problem found within the given input file
 * by applying the rlp improved version of the nemhauser ullman algorithm n times,
 * where n equals the numOfExecutions parameter.
 */
void executeNemhauserUllmanRLPSolver(const char* inputFile, int numOfExecutions=1) {
	KnapSackSolver* solver = new NemhauserUllmannSolverRLP(inputFile, KNAPSACK_OUTPUT_FILE, numOfExecutions);
	solver->start();
	delete solver;
}

/**
 * Solves the knapsack problem found within the given input file
 * by applying the parallel rlp improved version of the nemhauser ullman algorithm n times,
 * where n equals the numOfExecutions parameter.
 */
void executeNemhauserUllmanRLPParallelSolver(const char* inputFile, int numOfExecutions=1) {
	bool sortInputByWorth = false;
	KnapSackSolver* solver = new NemhauserUllmannRLPParallelSolver(inputFile, KNAPSACK_OUTPUT_FILE, numOfExecutions, sortInputByWorth);
	solver->start();
	delete solver;
}

/**
 * Solves the knapsack problem found within the given input file
 * by applying the dynamic programming algorithm n times,
 * where n equals the numOfExecutions parameter.
 */
void executeDynamicProgrammingSolver(const char* inputFile, int numOfExecutions=1){
	KnapSackSolver* solver = new DynamicProgrammingSolver(inputFile, KNAPSACK_OUTPUT_FILE, numOfExecutions);
	solver->start();
	delete solver;
}

/**
 * Solves the knapsack problem found within the given input file
 * by applying the parallel dynamic programming algorithm n times,
 * where n equals the numOfExecutions parameter.
 */
void executeDynamicProgrammingParallelSolver(const char* inputFile, int numOfExecutions=1){
	KnapSackSolver* solver = new DynamicProgrammingParallelSolver(inputFile, KNAPSACK_OUTPUT_FILE, numOfExecutions);
	solver->start();
	delete solver;
}

/**
 * Solves the knapsack problem found within the given input file
 * by applying the low memory version of the dynamic programming algorithm n times,
 * where n equals the numOfExecutions parameter.
 */
void executeDynamicProgrammingLowMemorySolver(const char* inputFile, int numOfExecutions=1){
	KnapSackSolver* solver = new DynamicProgrammingLowMemorySolver(inputFile, KNAPSACK_OUTPUT_FILE, numOfExecutions);
	solver->start();
	delete solver;
}

/**
 * Solves the knapsack problem found within the given input file
 * by applying the parallel low memory version of the dynamic programming algorithm n times,
 * where n equals the numOfExecutions parameter.
 */
void executeDynamicProgrammingLowMemoryParallelSolver(const char* inputFile, int numOfExecutions=1){
	KnapSackSolver* solver = new DynamicProgrammingLowMemoryParallelSolver(inputFile, KNAPSACK_OUTPUT_FILE, numOfExecutions);
	solver->start();
	delete solver;
}

/**
 * Can be used to check if open mp is supported by the current environment
 */
void checkForOpenMP(){
	int id;
	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();
		printf("%d: Hello World!\n", id);
	}
}

/**
 * Entry point of the application.
 * Can be used to determine which algorithm should be performed how often.
 * The problem which the specific algorithm shall solve, can be determined
 * by changing the respective input file parameter.
 */
int main(int argc, char* argv[]){

	int numberOfExecutions = 1;
	const char* inputFile = FIRST_KNAPSACK_INPUT_FILE;

	// Command line argumennts: program [nrOfExecutions] [filePath]
	if (3 == argc) {
		numberOfExecutions = std::atoi(argv[1]);
		inputFile = argv[2];
	}

	executeBruteForceSolver(inputFile, numberOfExecutions);
	executeNemhauserUllmanSolver(inputFile, numberOfExecutions);
	executeNemhauserUllmanParallelSolver(inputFile, numberOfExecutions);
	executeNemhauserUllmanRLPSolver(inputFile, numberOfExecutions);
	executeNemhauserUllmanRLPParallelSolver(inputFile, numberOfExecutions);
	executeDynamicProgrammingSolver(inputFile, numberOfExecutions);
	executeDynamicProgrammingParallelSolver(inputFile, numberOfExecutions);
	executeDynamicProgrammingLowMemorySolver(inputFile, numberOfExecutions);
	executeDynamicProgrammingLowMemoryParallelSolver(inputFile, numberOfExecutions);

}
