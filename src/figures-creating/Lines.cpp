#include "./../../inc/figures-creating/Lines.h"

LineEquation Lines::getParallelLine(const LineEquation& line, const PointEquation& point) {
    if (line.getType() == LineEquation::LineType::HORIZONTAL) {
        return LineEquation(0.0, 1.0, -point.getX());
    }
    else if (line.getType() == LineEquation::LineType::VERTICAL) {
        return LineEquation(1.0, 0.0, -point.getY());
    }
    else {
        return LineEquation(line.getA(), line.getB(), -(line.getA() * point.getX() + line.getB() * point.getY()));
    }
}

LineEquation Lines::getPerpendicularLine(const LineEquation& line, const PointEquation& point) {
    if (line.getType() == LineEquation::LineType::HORIZONTAL) {
        return LineEquation(1.0, 0.0, -point.getX());
    }
    else if (line.getType() == LineEquation::LineType::VERTICAL) {
        return LineEquation(0.0, 1.0, -point.getY());
    }
    else {
        return LineEquation(-1.0 / line.getA(), 1.0 / line.getB(), point.getX() / line.getA() - point.getY() / line.getB());
    }
}

std::vector<LineEquation> Lines::getBisectorLines(const PointEquation& point1, const PointEquation& vertex, const PointEquation& point2) {
    LineEquation arm1Equation = LineEquation(point1, vertex);
    LineEquation arm2Equation = LineEquation(point2, vertex);

    double module1 = sqrt(pow(arm1Equation.getA(), 2) + pow(arm1Equation.getB(), 2));
    double module2 = sqrt(pow(arm2Equation.getA(), 2) + pow(arm2Equation.getB(), 2));
    
    LineEquation bisector1Equation = LineEquation(
        arm1Equation.getA() * module2 - arm2Equation.getA() * module1,
        arm1Equation.getB() * module2 - arm2Equation.getB() * module1,
        arm1Equation.getC() * module2 - arm2Equation.getC() * module1
        );

    LineEquation bisector2Equation = LineEquation(
        arm1Equation.getA() * module2 + arm2Equation.getA() * module1,
        arm1Equation.getB() * module2 + arm2Equation.getB() * module1,
        arm1Equation.getC() * module2 + arm2Equation.getC() * module1
    );

    std::vector<LineEquation> result{};
    result.push_back(bisector1Equation);
    result.push_back(bisector2Equation);

    return result;
}

LineEquation Lines::getBisectorLineOfConvexAngle(const PointEquation& point1, const PointEquation& vertex, const PointEquation& point2) {
    std::vector<LineEquation> bisectors = Lines::getBisectorLines(point1, vertex, point2);
    LineEquation bisector1Equation = bisectors[0];
    LineEquation bisector2Equation = bisectors[1];

    LineEquation sideOppositeVertex = LineEquation(point1, point2);
    PointEquation intersection1, intersection2;
    int intersectionNumber1 = IntersectionPoints::ofLines(sideOppositeVertex, bisector1Equation, &intersection1);
    int intersectionNumber2 = IntersectionPoints::ofLines(sideOppositeVertex, bisector2Equation, &intersection2);

    if (intersectionNumber1 == 1) {
        if(sideOppositeVertex.getType() == LineEquation::LineType::VERTICAL) {
            if(minimum(point1.getY(), point2.getY()) < intersection1.getY() && intersection1.getY() < maximum(point1.getY(), point2.getY())) {
                return bisector1Equation;
            }
            else {
                return bisector2Equation;
            }
        }
        else {
            if(minimum(point1.getX(), point2.getX()) < intersection1.getX() && intersection1.getX() < maximum(point1.getX(), point2.getX())) {
                return bisector1Equation;
            }
            else {
                return bisector2Equation;
            }
        }
    }
    else {
        return bisector2Equation;
    }
}

LineEquation Lines::getBisectorLineOfConcaveAngle(const PointEquation& point1, const PointEquation& vertex, const PointEquation& point2) {
    std::vector<LineEquation> bisectors = Lines::getBisectorLines(point1, vertex, point2);
    LineEquation bisector1Equation = bisectors[0];
    LineEquation bisector2Equation = bisectors[1];

    LineEquation sideOppositeVertex = LineEquation(point1, point2);
    PointEquation intersection1, intersection2;
    int intersectionNumber1 = IntersectionPoints::ofLines(sideOppositeVertex, bisector1Equation, &intersection1);
    int intersectionNumber2 = IntersectionPoints::ofLines(sideOppositeVertex, bisector2Equation, &intersection2);

    if (intersectionNumber1 == 1) {
        if(sideOppositeVertex.getType() == LineEquation::LineType::VERTICAL) {
            if(minimum(point1.getY(), point2.getY()) < intersection1.getY() && intersection1.getY() < maximum(point1.getY(), point2.getY())) {
                return bisector2Equation;
            }
            else {
                return bisector1Equation;
            }
        }
        else {
            if(minimum(point1.getX(), point2.getX()) < intersection1.getX() && intersection1.getX() < maximum(point1.getX(), point2.getX())) {
                return bisector2Equation;
            }
            else {
                return bisector1Equation;
            }
        }
    }
    else {
        return bisector1Equation;
    }
}