#ifndef INTERSECTION_POINTS_H
#define INTERSECTION_POINTS_H

#include "./../math/equations/PointEquation.h"
#include "./../math/equations/LineEquation.h"
#include "./../math/equations/CircleEquation.h"

#include "./../math/SystemOf2LinearEquations.h"
#include "./../math/QuadraticEquation.h"

#include <cmath>

/**
 * @brief Class finding intersection points of lines and circles
 */
class IntersectionPoints {
public:
	/**
	 * @brief Deactivating the class constructor because the class is supposed to be static
	 */
	IntersectionPoints() = delete;

	/**
	 * @brief Finding intersection points of two lines
	 * 
	 * @param line1 reference to first line object
	 * @param line2 reference to second line object
	 * @param result pointer to object into which the intersection point will be written
	 * @return number of points found(0 or 1)
	 */
	static int ofLines(LineEquation& line1, LineEquation& line2, PointEquation* result);

	/**
	 * @brief Finding intersection points of line and circle 
	 * 
	 * @param line reference to line object
	 * @param circle reference to circle object
	 * @param result pointer to a 2-element array into which intersection points will be written
	 * @return number of points found(0 or 1 or 2) 
	 */
	static int ofLineAndCircle(LineEquation& line, CircleEquation& circle, PointEquation result[2]);

	/**
	 * @brief Finding intersection points of two circles
	 * 
	 * @param circle1 reference to first circle object
	 * @param circle2 reference to second circle object
	 * @param result pointer to a 2-element array into which intersection points will be written
	 * @return number of points found(0 or 1 or 2)  
	 */
	static int ofCircles(CircleEquation& circle1, CircleEquation& circle2, PointEquation result[2]);
};

#endif /* INTERSECTION_POINTS_H */