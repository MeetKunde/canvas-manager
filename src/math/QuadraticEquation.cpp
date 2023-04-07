#include "./../../inc/math/QuadraticEquation.h"

int QuadraticEquation::solve(double a, double b, double c, double solutions[2]) {
	/*
    Quadratic equation is solved by the discriminant method
    */

	double delta = b * b - 4 * a * c;
	
	if (fabs(delta) < Constans::SMALL_EPSILON) {
		solutions[0] = -0.5 * b / a;
		return 1;
	}
	else if (delta < 0.0) {
		return 0;
	}
	else {
		double sqrtOfDelta = sqrt(delta);
		double x1 = -0.5 * (b + sqrtOfDelta) / a;
		double x2 = -0.5 * (b - sqrtOfDelta) / a;
		if (x1 > x2) {
			solutions[0] = x1;
			solutions[1] = x2;
		}
		else {
			solutions[0] = x2;
			solutions[1] = x1;
		}
		return 2;
	}
}
