#ifndef UTIL_MYMATH_H_
#define UTIL_MYMATH_H_

#include <cmath>

/**
 * Helper class which provides mathematical helper functions
 */
class MyMath {
public:

	/**
	 * Range that two floating point numbers may differ to still be considered as equal
	 */
	static const double EPSILON;

	/**
	 * Compares two floating point numbers and checks if they are equal within the constant EPSLION range
	 */
	static bool almostEqual(const double& a, const double& b) {
		return almostEqual(a, b, EPSILON);
	}

	/**
	 * Compares two floating point numbers and checks if they are equal within the given epsilon range
	 */
	static bool almostEqual(const double& a, const double& b, const double& epsilon) {
		return std::abs(a-b) < epsilon;
	}
};

#endif /* UTIL_MYMATH_H_ */
