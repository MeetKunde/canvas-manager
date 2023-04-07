#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#include "Constans.h"

#include <cmath>

/**
 * @brief Class solving a quadratic equation in real numbers
 */
class QuadraticEquation {
public:
	/**
	 * @brief Deactivating the class constructor because the class is supposed to be static
	 */
	QuadraticEquation() = delete;

	/**
	 * @brief Solving quadratic equation
	 * 
	 * The found roots are written into a given 2-element array.
	 * If a quadratic equation has 1 root, the root is written to solutions at index 0.
	 * If a quadratic equation has 2 roots, the greater root is written to solutions at index 0, the lower root is written to solutions at index 1
	 * 
	 * @param a coefficient of x^2 in equation
	 * @param b coefficient of x in equation
	 * @param c constant term in equation
	 * @param solutions pointer to 2-element array into which roots of equation will be written
	 * @return number of real roots(0 or 1 or 2)
	 */
	static int solve(double a, double b, double c, double solutions[2]);
};

#endif /* QUADRATIC_EQUATION_H */