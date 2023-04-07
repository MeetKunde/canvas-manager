#include "./../../inc/figures-creating/Circles.h"

CircleEquation Circles::getInscribedCircle(std::vector<PointEquation>& vertices) noexcept(false) {
	int n = vertices.size();

	if(n == 3) {
		PointEquation A = vertices.at(0);
		PointEquation B = vertices.at(1);
		PointEquation C = vertices.at(2);
		double abLen = Distance::ofPoints(A, B);
		double bcLen = Distance::ofPoints(B, C);
		double acLen = Distance::ofPoints(A, C);

		double m = abLen + bcLen + acLen;

		double centerX = (abLen * C.getX() + bcLen * A.getX() + acLen * B.getX()) / m;
		double centerY = (abLen * C.getY() + bcLen * A.getY() + acLen * B.getY()) / m;

		LineEquation oneSide = LineEquation(A, B);
		PointEquation center =  PointEquation(centerX, centerY);

		return CircleEquation(center, Distance::ofPointAndLine(center, oneSide));
	}
	else if(n > 3) {
		// bierzemy dwie dwusieczne i sprawdzamy czy reszta punktow sie dostosowuje
		double sumOfCenterX = 0.0;
		double sumOfCenterY = 0.0;

		PointEquation point1, vertex, point2;
		LineEquation bisector1, bisector2;
		for(int i = 0; i<vertices.size(); i++) {
			point1 = vertices[i];
			vertex = vertices[(i+1) % n];
			point2 = vertices[(i+2) % n];
			bisector1 = Lines::getBisectorLineOfConvexAngle(point1, vertex, point2);

			point1 = vertices[(i+1) % n];
			vertex = vertices[(i+2) % n];
			point2 = vertices[(i+3) % n];
			bisector2 = Lines::getBisectorLineOfConvexAngle(point1, vertex, point2);

			PointEquation intersectionPoint;
			IntersectionPoints::ofLines(bisector1, bisector2, &intersectionPoint);

			sumOfCenterX += intersectionPoint.getX();
			sumOfCenterY += intersectionPoint.getY();
		}

		double centerX = sumOfCenterX / n;
		double centerY = sumOfCenterY / n;

		LineEquation oneSide = LineEquation(vertices.at(0), vertices.at(1));
		PointEquation center =  PointEquation(centerX, centerY);
		double radius = Distance::ofPointAndLine(center, oneSide);

		// sprawdzenie czy wyznaczony okrag ma sens
		LineEquation sideEquation;
		double currentRadius;
		for(int i = 0; i<n; i++) {
			sideEquation = LineEquation(vertices[i], vertices[(i+1) % n]);
			currentRadius = Distance::ofPointAndLine(center, sideEquation);

			if(fabs(radius - currentRadius) > Constans::BIG_EPSILON) {
				std::cout << "TESTY NIE TAK " << fabs(radius - currentRadius) << std::endl;
				throw(InvalidPointsException());
			}
		}

		return CircleEquation(PointEquation(centerX, centerY), radius);
	}
	else {
		std::cout << "COS PO DRODZE NIE TAK " << std::endl;
		throw(InvalidPointsException());
	}
}

CircleEquation Circles::getCircumscribedCircle(std::vector<PointEquation>& vertices) noexcept(false) {
	if(vertices.size() >= 3) {
		int n = vertices.size();
		double centerX = 0.0;
		double centerY = 0.0;
		
		for(int i = 0; i<n; i++) {
			PointEquation A = vertices[i];
			PointEquation B = vertices[(i+1)%n];
			PointEquation C = vertices[(i+2)%n];

			double mA = A.getX() * A.getX() + A.getY() * A.getY();
			double mB = B.getX() * B.getX() + B.getY() * B.getY();
			double mC = C.getX() * C.getX() + C.getY() * C.getY();

			double m = 2 * (A.getX() * (B.getY() - C.getY()) + B.getX() * (C.getY() - A.getY()) + C.getX() * (A.getY() - B.getY()));

			centerX += (mA * (B.getY() - C.getY()) + mB * (C.getY() - A.getY()) + mC * (A.getY() - B.getY())) / m;
			centerY += (mA * (C.getX() - B.getX()) + mB * (A.getX() - C.getX()) + mC * (B.getX() - A.getX())) / m;
		}

		PointEquation center = PointEquation(centerX / n, centerY / n);

		double radius = 0.0;

		for(int i = 0; i<n; i++) {
			radius += Distance::ofPoints(center, vertices[i]);
		}

		radius /= n;

		for(int i = 0; i<n; i++) {
			if(fabs(Distance::ofPoints(center, vertices[i]) - radius) > Constans::BIG_EPSILON) {
				throw(InvalidPointsException());
			}
		}

		return CircleEquation(center, radius);
	}
	else {
		throw(InvalidPointsException());
	}
}

CircleEquation Circles::getEscribedCircle(const PointEquation& sideEnd1, const PointEquation& sideEnd2, const LineEquation& sideEquation, const PointEquation& point) {
	LineEquation bisector1 = Lines::getBisectorLineOfConcaveAngle(point, sideEnd1, sideEnd2);
	LineEquation bisector2 = Lines::getBisectorLineOfConcaveAngle(point, sideEnd2, sideEnd1);

	PointEquation intersectionPoint;
	IntersectionPoints::ofLines(bisector1, bisector2, &intersectionPoint);

	return CircleEquation(intersectionPoint, Distance::ofPointAndLine(intersectionPoint, sideEquation));
}
