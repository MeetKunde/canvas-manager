#include "./../../../inc/math/equations/LineEquation.h"

LineEquation::LineEquation() 
: A(1.0), B(-1.0), C(0.0), a(1.0), b(0.0), lineType(LineType::SLANTED) { }

LineEquation::LineEquation(const PointEquation& point1, const PointEquation& point2) noexcept(false){
	if (point1 == point2) {
		std::cout << "...EQUAL POINTS EQUAL POINTS..." << std::endl;
		throw(EqualPointsException());
	}

	if (fabs(point1.getX() - point2.getX()) < Constans::SMALL_EPSILON) {
		A = 1.0;
		B = 0.0;
		C = -point1.getX();
		a = 0.0;
		b = point1.getX();
		lineType = LineType::VERTICAL;
	}
	else if (fabs(point1.getY() - point2.getY()) < Constans::SMALL_EPSILON) {
		A = 0.0;
		B = 1.0;
		C = -point1.getY();
		a = 0.0;
		b = point1.getY();
		lineType = LineType::HORIZONTAL;
	}
	else {
		A = (point1.getY() - point2.getY()) / (point1.getX() - point2.getX());
		B = -1.0;
		C = point1.getY() - A * point1.getX();
		a = A;
		b = C;
		lineType = LineType::SLANTED;
	}
}

LineEquation::LineEquation(double coefficientA, double coefficientB, double coefficientC) noexcept(false) {
	if (fabs(coefficientA) <= Constans::SMALL_EPSILON && fabs(coefficientB) <= Constans::SMALL_EPSILON) {
		throw(ZeroCoefficientsException());
	}

	A = coefficientA;
	B = coefficientB;
	C = coefficientC;

	if (fabs(coefficientA) <= Constans::SMALL_EPSILON) {
		a = 0.0;
		b = -C / B;
		lineType = LineEquation::LineType::HORIZONTAL;
	}
	else if (fabs(coefficientB) <= Constans::SMALL_EPSILON) {
		a = 0.0;
		b = -C / A;
		lineType = LineEquation::LineType::VERTICAL;
	}
	else {
		a = -A / B;
		b = -C / B;
		lineType = LineEquation::LineType::SLANTED;
	}
}

LineEquation::LineEquation(const LineEquation& line) 
: A(line.A), B(line.B), C(line.C), a(line.a), b(line.b), lineType(line.lineType) { }

LineEquation& LineEquation::operator=(const LineEquation& line) {
	A = line.A;
	B = line.B;
	C = line.C;
	a = line.a;
	b = line.b;
	lineType = line.lineType;

	return *this;
}

double LineEquation::getY(double x) noexcept(false) {
	if (lineType == LineEquation::LineType::VERTICAL) {
		throw(AmbiguousQueryException());
	}
	else if (lineType == LineEquation::LineType::HORIZONTAL) {
		return b;
	}
	else {
		return a * x + b;
	}
}

double LineEquation::getX(double y) noexcept(false) {
	if (lineType == LineEquation::LineType::HORIZONTAL) {
		throw(AmbiguousQueryException());
	}
	else if (lineType == LineEquation::LineType::VERTICAL) {
		return b;
	}
	else {
		return (y - b) / a;
	}
}

bool LineEquation::liesOn(const PointEquation& point) {
	return (fabs(A * point.getX() + B * point.getY() + C) / sqrt(A * A + B * B)) <= Constans::BIG_EPSILON;
}

PointEquation LineEquation::getCenteredPoint(PointEquation& point) {
	if (lineType == LineEquation::LineType::VERTICAL) {
		return PointEquation(b, point.getY());
	}
	else if (lineType == LineEquation::LineType::HORIZONTAL) {
		return PointEquation(point.getX(), b);
	}
	else {
		PointEquation point1(point.getX(), a * point.getX() + b);
		PointEquation point2((point.getY() - b) / a, point.getY());

		double distance1 = Distance::ofPoints(point, point1);
		double distance2 = Distance::ofPoints(point, point2);

		if (distance1 < distance2) {
			return point1;
		}
		else {
			return point2;
		}
	}
}

PointEquation LineEquation::getPointBetweenPointsWithDistance(PointEquation& point1, PointEquation& point2, double distance) {
	if(lineType == LineType::HORIZONTAL) {
		double sign = (point2.getX() - point1.getX()) / fabs(point2.getX() - point1.getX());

		return PointEquation(point1.getX() + sign * distance, point1.getY());
	}
	else if(lineType == LineType::VERTICAL) {
		double sign = (point2.getY() - point1.getY()) / fabs(point2.getY() - point1.getY());

		return PointEquation(point1.getX(), point1.getY() + sign * distance);
	}
	else {
		double sign = (point2.getX() - point1.getX()) / fabs(point2.getX() - point1.getX());
		
		// dy = dx * a 
		// (dx)^2 + (dy)^2 = d^2
		// (dx)^2(1 + a^2) = d^2 => dx = d / sqrt(1 + a^2)

		double dx = distance / sqrt(1 + a * a);
		double newX = point1.getX() + sign * dx;

		return PointEquation(newX, getY(newX));
	}
}

std::string LineEquation::getStringHash() {
	if (lineType == LineType::VERTICAL) {
		return "V" + std::to_string(0.001 * round(b * 1000));
	}
	else if (lineType == LineType::HORIZONTAL) {
		return "H" + std::to_string(0.001 * round(b * 1000));
	}
	else {
		return "S" + std::to_string(0.001 * round(a * 1000)) + "|" + std::to_string(0.001 * round(b * 1000));
	}
}

bool operator==(const LineEquation& line1, const LineEquation& line2) {
	if (line1.lineType != line2.lineType) {
		return false;
	}

	return fabs(line1.A - line2.A) <= 10 * Constans::SMALL_EPSILON && fabs(line1.B - line2.B) <= 10 * Constans::SMALL_EPSILON && fabs(line1.C - line2.C) <= 10 * Constans::SMALL_EPSILON;
}

bool operator!=(const LineEquation& line1, const LineEquation& line2) {
	return !(line1 == line2);
}

std::ostream& operator<<(std::ostream& stream, const LineEquation& line) {
	stream << line.A << "x + " << line.B << "y + " << line.C << " = 0.0";

	return stream;
}