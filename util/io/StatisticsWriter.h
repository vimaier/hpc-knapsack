#ifndef IO_STATISTICSWRITER_H_
#define IO_STATISTICSWRITER_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

class StatisticsWriter {
public:
	StatisticsWriter(std::string filename, std::string algorithmname);
	virtual ~StatisticsWriter();

	void addDuration(const double seconds);
	void clearDurations();
	bool writeToFile();

private:
	std::string filename;
	std::string algorithmname;
	std::vector<double> durations;

	double calcAvg();
	double calcRms(const double avg);
};

#endif /* IO_STATISTICSWRITER_H_ */
