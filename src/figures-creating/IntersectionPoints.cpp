#include "./../../inc/figures-creating/IntersectionPoints.h"

int IntersectionPoints::ofLines(LineEquation& line1, LineEquation& line2, PointEquation* result) {
	double coordinates[2];
	SystemOf2LinearEquations::NumberOfSolutions solutionsNumber = SystemOf2LinearEquations::solve(line1.getA(), line1.getB(), line1.getC(), line2.getA(), line2.getB(), line2.getC(), coordinates);
	
	if (solutionsNumber == SystemOf2LinearEquations::NumberOfSolutions::ONE) {
		*result = PointEquation(coordinates[0], coordinates[1]);
		return 1;
	}
	else {
		return 0;
	}
}

int IntersectionPoints::ofLineAndCircle(LineEquation& line, CircleEquation& circle, PointEquation result[2]) {
	if (line.getType() == LineEquation::LineType::SLANTED) {
		double xs[2];
		int solutionsNumber = QuadraticEquation::solve(
			pow(line.geta(), 2) + 1.0,
			2.0 * (line.geta() * (line.getb() - circle.getCenterPoint().getY()) - circle.getCenterPoint().getX()),
			pow(line.getb(), 2) + pow(circle.getCenterPoint().getX(), 2) + pow(circle.getCenterPoint().getY(), 2) - pow(circle.getRadius(), 2) - 2 * line.getb() * circle.getCenterPoint().getY(),
			xs);

		for (int i = 0; i < solutionsNumber; i++) {
			result[i] = PointEquation(xs[i], line.getY(xs[i]));
		}

		return solutionsNumber;
	}
	else if (line.getType() == LineEquation::LineType::HORIZONTAL) {
		double xs[2];
		int solutionsNumber = QuadraticEquation::solve(
			1.0, 
			-2.0 * circle.getCenterPoint().getX(),
			pow(line.getb(), 2) + pow(circle.getCenterPoint().getX(), 2) + pow(circle.getCenterPoint().getY(), 2) - pow(circle.getRadius(), 2) - 2.0 * line.getb() * circle.getCenterPoint().getY(),
			xs);

		for (int i = 0; i < solutionsNumber; i++) {
			result[i] = PointEquation(xs[i], line.getY(xs[i]));
		}

		return solutionsNumber;
	}
	else {
		double ys[2];
		int solutionsNumber = QuadraticEquation::solve(
			1.0,
			-2.0 * circle.getCenterPoint().getY(),
			pow(line.getb(), 2) + pow(circle.getCenterPoint().getX(), 2) + pow(circle.getCenterPoint().getY(), 2) - pow(circle.getRadius(), 2) - 2.0 * line.getb() * circle.getCenterPoint().getX(),
			ys);

		for (int i = 0; i < solutionsNumber; i++) {
			result[i] = PointEquation(line.getX(ys[i]), ys[i]);
		}

		return solutionsNumber;
	}
}

int IntersectionPoints::ofCircles(CircleEquation& circle1, CircleEquation& circle2, PointEquation result[2]) {
	if (circle1.getCenterPoint() == circle2.getCenterPoint()) {
		return 0;
	}
	
	double p = pow(circle1.getCenterPoint().getX(), 2) + pow(circle1.getCenterPoint().getY(), 2) - pow(circle1.getRadius(), 2) - pow(circle2.getCenterPoint().getX(), 2) - pow(circle2.getCenterPoint().getY(), 2) + pow(circle2.getRadius(), 2);
	
	if (fabs(circle1.getCenterPoint().getX() - circle2.getCenterPoint().getX()) <= Constans::BIG_EPSILON) {
		double e = p / 2.0 / (circle1.getCenterPoint().getY() - circle2.getCenterPoint().getY()) - circle1.getCenterPoint().getY();
		
		double xs[2];
		int solutionsNumber = QuadraticEquation::solve(
			1.0,
			-2.0 * circle1.getCenterPoint().getX(),
			pow(circle1.getCenterPoint().getX(), 2) + pow(e, 2) - pow(circle1.getRadius(), 2),
			xs);

		int k = 0;
		for (int i = 0; i < solutionsNumber; i++) {
			double ys[2];
			int ysSolutionsNumber = circle1.getYs(xs[i], ys);
			for (int j = 0; j < ysSolutionsNumber; j++) {
				PointEquation point(xs[i], ys[j]);
				if(circle2.liesOn(point)) {
					result[k] = point;
					k++;
					break;
				}
			}
		}

		return k;
	}
	else {
		double e = (circle2.getCenterPoint().getY() - circle1.getCenterPoint().getY()) / (circle1.getCenterPoint().getX() - circle2.getCenterPoint().getX());
		double f = p / 2.0 / (circle1.getCenterPoint().getX() - circle2.getCenterPoint().getX()) - circle1.getCenterPoint().getX();
		
		double ys[2];
		int solutionsNumber = QuadraticEquation::solve(
			1.0 + pow(e, 2), 
			2.0 * (e * f - circle1.getCenterPoint().getY()), 
			pow(f, 2) + pow(circle1.getCenterPoint().getY(), 2) - pow(circle1.getRadius(), 2),
			ys);

		int k = 0;
		for (int i = 0; i < solutionsNumber; i++) {
			double xs[2];
			int xsSolutionsNumber = circle1.getXs(ys[i], xs);
			for (int j = 0; j < xsSolutionsNumber; j++) {
				PointEquation point(xs[j], ys[i]);
				if (circle2.liesOn(point)) {
					result[k] = point;
					k++;
					break;
				}
			}
		}

		return k;
	}
}
