/*
 * MyMath.h
 *
 *  Contains multiple helpful functions.
 */

#ifndef UTIL_MYMATH_H_
#define UTIL_MYMATH_H_

#include <cmath>

class MyMath {
public:
	static const double EPSILON;

	static bool almostEqual(const double& a, const double& b) {
		return almostEqual(a, b, EPSILON);
	}

	static bool almostEqual(const double& a, const double& b, const double& epsilon) {
		return std::abs(a-b) < epsilon;
	}
};

#endif /* UTIL_MYMATH_H_ */
