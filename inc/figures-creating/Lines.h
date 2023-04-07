#ifndef LINES_H
#define LINES_H

#include "./../math/equations/PointEquation.h"
#include "./../math/equations/LineEquation.h"
#include "./../math/equations/CircleEquation.h"
#include "IntersectionPoints.h"

#include <vector>
#include <stdexcept>

/**
 * @brief Class creating specific line equations
 */
class Lines {
public:
	/**
	 * @brief Deactivating the class constructor because the class is supposed to be static
	 */
	Lines() = delete;

	/**
	 * @brief Finding parallel line equation to given through given point
	 * 
	 * @param line reference to base line equation object
	 * @param point reference to base point object
	 * @return LineEquation 
	 */
	static LineEquation getParallelLine(const LineEquation& line, const PointEquation& point);

	/**
	 * @brief Finding perpendicular line equation to given through given point
	 * 
	 * @param line reference to base line equation object
	 * @param point reference to base point object
	 * @return LineEquation 
	 */
	static LineEquation getPerpendicularLine(const LineEquation& line, const PointEquation& point);

	/**
	 * @brief Finding line equations of bisector lines of angle
	 * 
	 * @param point1 reference to first angle point object
	 * @param vertex reference to vertex point object
	 * @param point2 reference to second angle point object
	 * @return 2-element vector with line equations representing bisector
	 */
	static std::vector<LineEquation> getBisectorLines(const PointEquation& point1, const PointEquation& vertex, const PointEquation& point2);

	/**
	 * @brief Finding line equation of bisector line of convex angle
	 * 
	 * @param point1 reference to first angle point object
	 * @param vertex reference to vertex point object
	 * @param point2 reference to second angle point object
	 * @return line equation representing bisector of convex angle 
	 */
	static LineEquation getBisectorLineOfConvexAngle(const PointEquation& point1, const PointEquation& vertex, const PointEquation& point2);

	/**
	 * @brief Finding line equation of bisector line of concave angle
	 * 
	 * @param point1 reference to first angle point object
	 * @param vertex reference to vertex point object
	 * @param point2 reference to second angle point object
	 * @return line equation representing bisector of concave angle  
	 */
	static LineEquation getBisectorLineOfConcaveAngle(const PointEquation& point1, const PointEquation& vertex, const PointEquation& point2);

private:
	/**
	 * @brief Calculating minimal value of 2 numbers
	 * 
	 * @param x first number
	 * @param y second number
	 * @return minimal value of given numbers 
	 */
	static inline double minimum(double x, double y) { return x < y ? x : y; }

	/**
	 * @brief Calculating maximal value of 2 numbers
	 * 
	 * @param x first number
	 * @param y second number
	 * @return maximal value of given numbers  
	 */
	static inline double maximum(double x, double y) { return x > y ? x : y; }
};

#endif /* LINES_H */