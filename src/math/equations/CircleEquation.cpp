#include "./../../../inc/math/equations/CircleEquation.h"

CircleEquation::CircleEquation()
: centerPoint(PointEquation(0.0, 0.0)), radius(10.0) { }

CircleEquation::CircleEquation(const PointEquation& centerPoint, double radius) noexcept(false) {
	if (radius <= 1.0) {
		throw(NegativeRadiusException());
	}

	this->centerPoint = PointEquation(centerPoint);
	this->radius = radius;
}

CircleEquation::CircleEquation(const CircleEquation& circle) 
: centerPoint(PointEquation(circle.centerPoint)), radius(circle.radius) { }

CircleEquation& CircleEquation::operator=(const CircleEquation& circle) {
	centerPoint = PointEquation(circle.centerPoint);
	radius = circle.radius;

	return *this;
}

int CircleEquation::getYs(double x, double ys[2]) {
	double sqrtArg = radius * radius - (x - centerPoint.getX()) * (x - centerPoint.getX());
	if (fabs(sqrtArg) <= Constans::BIG_EPSILON) {
		ys[0] = centerPoint.getY();
		return 1;
	}
	else if (sqrtArg < 0.0) {
		return 0;
	}
	else {
		double s = sqrt(sqrtArg);
		ys[0] = centerPoint.getY() + s;
		ys[1] = centerPoint.getY() - s;
		return 2;
	}
}

int CircleEquation::getXs(double y, double xs[2]) {
	double sqrtArg = radius * radius - (y - centerPoint.getY()) * (y - centerPoint.getY());
	if (fabs(sqrtArg) <= Constans::BIG_EPSILON) {
		xs[0] = centerPoint.getX();
		return 1;
	}
	else if (sqrtArg < 0.0) {
		return 0;
	}
	else {
		double s = sqrt(sqrtArg);
		xs[0] = centerPoint.getX() + s;
		xs[1] = centerPoint.getX() - s;
		return 2;
	}
}

bool CircleEquation::liesOn(const PointEquation& point) {
	double leftSide = pow(point.getX() - centerPoint.getX(), 2) + pow(point.getY() - centerPoint.getY(), 2);
	double rightSide = radius * radius;

	return fabs(leftSide - rightSide) <= Constans::BIG_EPSILON;
}

PointEquation CircleEquation::getCenteredPoint(PointEquation& point) {
	double xs[2], ys[2];
	int xsCount = getXs(point.getY(), xs);
	int ysCount = getYs(point.getX(), ys);

	for (int i = xsCount; i < 2; i++) {
		xs[i] = point.getX();
	}
	for (int i = ysCount; i < 2; i++) {
		ys[i] = point.getY();
	}

	PointEquation point1 = PointEquation(xs[0], point.getY());
	PointEquation point2 = PointEquation(xs[1], point.getY());

	double distance1 = Distance::ofPoints(point, point1);
	double distance2 = Distance::ofPoints(point, point2);

	if (distance2 < distance1) {
		xs[0] = xs[1];
	}

	point1 = PointEquation(point.getX(), ys[0]);
	point2 = PointEquation(point.getX(), ys[1]);

	distance1 = Distance::ofPoints(point, point1);
	distance2 = Distance::ofPoints(point, point2);

	if (distance2 < distance1) {
		ys[0] = ys[1];
	}

	point1 = PointEquation(xs[0], point.getY());
	point2 = PointEquation(point.getY(), ys[0]);

	distance1 = Distance::ofPoints(point, point1);
	distance2 = Distance::ofPoints(point, point2);

	if (distance1 < distance2) {
		return point1;
	}
	else {
		return point2;
	}
}

bool operator==(const CircleEquation& circle1, const CircleEquation& circle2) { 
	return circle1.centerPoint == circle2.centerPoint && fabs(circle1.radius - circle2.radius) <= Constans::NORMAL_EPSILON;
}

bool operator!=(const CircleEquation& circle1, const CircleEquation& circle2) {
	return !(circle1 == circle2);
}

std::ostream& operator<<(std::ostream& stream, const CircleEquation& circle) {
	stream << "{" << circle.centerPoint << ", " << circle.radius << "}";

	return stream;
}
