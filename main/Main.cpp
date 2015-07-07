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
static const char* KNAPSACK_OUTPUT_FILE = "knapSackOut.txt";

void executeNemhauserUllmanSolver() {
	KnapSackSolver* solver = new NemhauserUllmannSolver(FIRST_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void executeNemhauserUllmanParallelSolver() {
	KnapSackSolver* solver = new NemhauserUllmannParallelSolver(FIRST_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void executeNemhauserUllmanRLPSolver() {
	KnapSackSolver* solver = new NemhauserUllmannSolverRLP(FIRST_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void executeBruteForceSolver(){
	KnapSackSolver* solver = new BruteForceSolver(FIRST_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void executeDynamicProgrammingSolver(){
	KnapSackSolver* solver = new DynamicProgrammingSolver(FIFTH_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void executeDynamicProgrammingParallelSolver(){
	KnapSackSolver* solver = new DynamicProgrammingParallelSolver(FIFTH_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void executeDynamicProgrammingLowMemorySolver(){
	KnapSackSolver* solver = new DynamicProgrammingLowMemorySolver(SIXTH_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void executeDynamicProgrammingLowMemoryParallelSolver(){
	KnapSackSolver* solver = new DynamicProgrammingLowMemoryParallelSolver(SIXTH_KNAPSACK_INPUT_FILE, KNAPSACK_OUTPUT_FILE);
	solver->start();
	delete solver;
}

void checkForOpenMP(){
	int id;
	#pragma omp parallel private(id)
	{
		id = omp_get_thread_num();
		printf("%d: Hello World!\n", id);
	}
}

int main(int argc, char* argv[]){

	//checkForOpenMP();

	//executeBruteForceSolver();
	//executeNemhauserUllmanSolver();
	//executeNemhauserUllmanParallelSolver();
	//executeNemhauserUllmanRLPSolver();
	//executeDynamicProgrammingSolver();
	//executeDynamicProgrammingParallelSolver();
	executeDynamicProgrammingLowMemorySolver();
	executeDynamicProgrammingLowMemoryParallelSolver();
}
