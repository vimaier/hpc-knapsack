#ifndef IO_STATISTICSWRITER_H_
#define IO_STATISTICSWRITER_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

/**
 * Helper class used to create an output file representing the statistics collected
 * while solving a knapsack problem in a KnapSackSolver
 *
 * Example output file:
 *
 * ------------------------------
	Alogrithmus;Dynamic Programming Low Memory (Sequential)
	Anzahl Durchlaeufe;3
	Durchschnittliche Laufzeit;2.1608
	Quadratisches Mittel;0.0243
	1;2.1265
	2;2.1772
	3;2.1788
 * ------------------------------
 *
 * Meaning:
 * - Alogrithmus = The name of the solver algorithm
 * - The problem was solved 3 times with this algorithm
 * - The average time to solve the problem was 2.1608s
 * - The root mean square for solving was 0.0243s
 * - The first solving took 2.1265s
 * - The second solving took 2.1772s
 * - The third solving took 2.1788s
 */
class StatisticsWriter {
public:
	StatisticsWriter(std::string filename, std::string algorithmname);
	virtual ~StatisticsWriter();

	/**
	 * Adds a duration in seconds to the duration list.
	 */
	void addDuration(const double seconds);

	/**
	 * Clears the list of durations, meaning it removes all entries from the list.
	 */
	void clearDurations();

	/**
	 * Writes the statistics to the specified output file.
	 */
	bool writeToFile();

private:
	/**
	 * The path to the output file
	 */
	std::string filename;

	/**
	 * The name of the algorithm that was measured while solving the problem
	 */
	std::string algorithmname;

	/**
	 * The duration list represents the durations of the respective solve iterations.
	 * There should be one measured duration for each time the problem was solved.
	 * It serves as base for calculating the average needed time and the root mean square.
	 */
	std::vector<double> durations;

	/**
	 * Calculates the average time needed to solve the problem and returns it.
	 */
	double calcAvg();

	/**
	 * Calculates the root mean square error among the collected durations and returns it.
	 */
	double calcRmsError(const double avg);
};

#endif /* IO_STATISTICSWRITER_H_ */
