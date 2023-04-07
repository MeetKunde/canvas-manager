#include "./../../inc/math/Distance.h"

double Distance::ofPoints(const PointEquation& point1, const PointEquation& point2) {
    return sqrt(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2));
}

double Distance::ofPointAndLine(const PointEquation& point, const LineEquation& line) {
    return fabs(line.getA() * point.getX() + line.getB() * point.getY() + line.getC()) / sqrt(pow(line.getA(), 2) + pow(line.getB(), 2));
}

double Distance::tangentOfAngleBetweenLines(const LineEquation& line1, const LineEquation& line2) {
    double denominator = line1.getA() * line2.getA() + line1.getB() * line2.getB();
    if (fabs(denominator) < Constans::NORMAL_EPSILON) {
        return DBL_MAX;
    }
    else {
        return (line1.getA() * line2.getB() - line2.getA() * line1.getB()) / denominator;
    }
}
