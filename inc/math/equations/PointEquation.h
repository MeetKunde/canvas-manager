#ifndef POINT_EQUATION_H
#define POINT_EQUATION_H

#include "./../Constans.h"

#include <cmath>
#include <iostream>

/**
 * @brief Class representing equation of point on XY plane
 */
class PointEquation {
private:
	/**
	 * @brief X coordinate of point
	 */
	double x;

	/**
	 * @brief Y coordinate of point
	 */
	double y;

public:
	/**
	 * @brief Constructor of a new PointEquation object
	 */
	PointEquation();

	/**
	 * @brief Constructor of a new PointEquation object
	 * 
	 * @param x X coordinate of a point
	 * @param y Y coordinate of a point
	 */
	PointEquation(double x, double y);

	/**
	 * @brief Constructor of a new PointEquation object
	 * 
	 * @param point other PointEquation object
	 */
	PointEquation(const PointEquation& point);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param point object to be assigned 
	 * @return new PointEquation object
	 */
    PointEquation& operator=(const PointEquation& point);

	/**
	 * @brief X coordinate getter
	 * 
	 * @return value of object X coordinate
	 */
	inline double getX() const { return x; }

	/**
	 * @brief Y coordinate getter
	 * 
	 * @return value of object Y coordinate
	 */
	inline double getY() const { return y; }

	/**
	 * @brief Override of equality operator 
	 * 
	 * Points are equal if their two coordinates are equal to each other with some accuracy - Constans::BIG_EPSILON
	 * 
	 * @param point1 first object to compare
	 * @param point2 second object to compare
	 * @return true if given points are equal
	 * @return false if given points are not equal
	 */
	friend bool operator== (const PointEquation& point1, const PointEquation& point2);

	/**
	 * @brief Override of inequality operator 
	 * 
	 * Points are equal if their two coordinates are equal to each other with some accuracy - Constans::BIG_EPSILON
	 * 
	 * @param point1 first object to compare
	 * @param point2 second object to compare
	 * @return true if given points are not equal
	 * @return false if given points are equal
	 */
	friend bool operator!= (const PointEquation& point1, const PointEquation& point2);

	/**
	 * @brief Override of stream insertion operator 
	 * 
	 * @param stream object of ostream class
	 * @param point object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const PointEquation& point);
};

#endif /* POINT_EQUATION_H */