#ifndef SYSTEM_OF_2_LINEAR_EQUATIONS_H
#define SYSTEM_OF_2_LINEAR_EQUATIONS_H

#include "Constans.h"

#include <cmath>

/**
 * @brief Class solving a system of 2 linear equations
 */
class SystemOf2LinearEquations {
public:
	/**
	 * @brief Representing number of solutions of system of 2 linear equations
	 */
	enum class NumberOfSolutions {
		/**
		 * @brief System of 2 linear equations does not have solutions
		 */
		ZERO,

		/**
		 * @brief System of 2 linear equations has one solutions
		 */
		ONE,

		/**
		 * @brief System of 2 linear equations has infinitely many solutions - any point lying on the given line satisfies system of 2 linear equations
		 */
		INFINITELY_MANY
	};

	/**
	 * @brief Deactivating the class constructor because the class is supposed to be static
	 */
	SystemOf2LinearEquations() = delete;

	/**
	 * @brief Solving a system of 2 linear equation: 
	 *
	 * A1x + B1y + C1 = 0 and A2x + B2y + C2 = 0 
	 * 
	 * If system of 2 linear equations has one solution, the pair (x, y) satisfying the equation will be written to solution: x at index 0, y at index 1
	 * 
	 * @param A1 coefficient of x in the first equation
	 * @param B1 coefficient of y in the first equation
	 * @param C1 constant term in the first equation
	 * @param A2 coefficient of x in the second equation
	 * @param B2 coefficient of y in the second equation
	 * @param C2 constant term in the second equation
	 * @param solution pointer to a 2-element array into which the pair (x, y) satisfying the equation will be written
	 * @return number of solutions
	 */
	static NumberOfSolutions solve(double A1, double B1, double C1, double A2, double B2, double C2, double solution[2]);
};

#endif /* SYSTEM_OF_2_LINEAR_EQUATIONS_H */