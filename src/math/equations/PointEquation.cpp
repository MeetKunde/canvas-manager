#include "./../../../inc/math/equations/PointEquation.h"

PointEquation::PointEquation() 
: x(0), y(0) { }

PointEquation::PointEquation(double x, double y)
: x(x), y(y) { }

PointEquation::PointEquation(const PointEquation& point) 
: x(point.x), y(point.y) { }

PointEquation& PointEquation::operator=(const PointEquation& point) {
	x = point.x;
	y = point.y;

	return *this;
}

bool operator==(const PointEquation& point1, const PointEquation& point2) {
	return fabs(point1.x - point2.x) <= Constans::BIG_EPSILON && fabs(point1.y - point2.y) <= Constans::BIG_EPSILON;
}

bool operator!=(const PointEquation& point1, const PointEquation& point2) {
	return !(point1 == point2);
}

std::ostream& operator<<(std::ostream& stream, const PointEquation& point) {
	stream << "(" << point.x << ", " << point.y << ")";

	return stream;
}