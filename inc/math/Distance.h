#ifndef DISTANCE_H
#define DISTANCE_H

#include "./equations/PointEquation.h"
#include "./equations/LineEquation.h"

#include <float.h>

class PointEquation;
class LineEquation;

/**
 * @brief Class calculating distance between figures: points and lines and angle between lines
 */
class Distance {
public:
	/**
	 * @brief Deactivating the class constructor because the class is supposed to be static
	 */
	Distance() = delete;

	/**
	 * @brief Calculating distance between points
	 * 
	 * @param point1 reference to first point object
	 * @param point2 reference to second point object
	 * @return distance between given points
	 */
	static double ofPoints(const PointEquation& point1, const PointEquation& point2);

	/**
	 * @brief Calculating distance between point and line
	 * 
	 * @param point reference to point object
	 * @param line reference to line object
	 * @return distance between given point and given line 
	 */
	static double ofPointAndLine(const PointEquation& point, const LineEquation& line);

	/**
	 * @brief Calculating tangent of the angle between lines
	 * 
	 * @param line1 reference to first line object
	 * @param line2 reference to second line object
	 * @return tangent of angle between given lines
	 */
	static double tangentOfAngleBetweenLines(const LineEquation& line1, const LineEquation& line2);
};

#endif /* DISTANCE_H */