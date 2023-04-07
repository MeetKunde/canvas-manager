#include "./../../inc/math/SystemOf2LinearEquations.h"

SystemOf2LinearEquations::NumberOfSolutions SystemOf2LinearEquations::solve(double A1, double B1, double C1, double A2, double B2, double C2, double solution[2]) {
    /*
    System of equations is solved by the determinant method
    */
   
    double w = A1 * B2 - A2 * B1;
    double wx = C2 * B1 - C1 * B2;
    double wy = C1 * A2 - C2 * A1;

    if (fabs(w) > Constans::SMALL_EPSILON) {
        solution[0] = wx / w;
        solution[1] = wy / w;

        return NumberOfSolutions::ONE;
    }
    else if (fabs(wx) <= Constans::SMALL_EPSILON && fabs(wy) <= Constans::SMALL_EPSILON) {
        return NumberOfSolutions::INFINITELY_MANY;
    }
    else {
        return NumberOfSolutions::ZERO;
    }
}
