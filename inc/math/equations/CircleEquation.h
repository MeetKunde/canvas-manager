#ifndef CIRCLE_EQUATION_H
#define CIRCLE_EQUATION_H

#include "PointEquation.h"
#include "./../Constans.h"
#include "./../Distance.h"

#include <cmath>

/**
 * @brief Class representing equation of circle on XY plane
 */
class CircleEquation {
public:
	/**
	 * @brief Class implementing a custom exception used in CircleEquation class methods 
	 * when an attempt is made to create a circle based on radius with negative length 
	 */
	class NegativeRadiusException : public virtual std::invalid_argument {
	public:
		/**
		 * @brief Constructor of a new NegativeRadiusException object
		 */
		NegativeRadiusException() : std::invalid_argument("Radius cannot be nagative number! Radius must be number greater then 1.0") { }
	};

private:
	/**
	 * @brief Center point of circle
	 */
	PointEquation centerPoint;

	/**
	 * @brief Radius length of circle
	 */
	double radius;

public:
	/**
	 * @brief Constructor of a new CircleEquation object
	 */
	CircleEquation();

	/**
	 * @brief Constructor of a new CircleEquation object
	 * 
	 * @param centerPoint center point of circle
	 * @param radius radius length of circle
	 * @throws NegativeRadiusException if given radius is negative number
	 */
	CircleEquation(const PointEquation& centerPoint, double radius) noexcept(false);

	/**
	 * @brief Constructor of a new CircleEquation object
	 * 
	 * @param circle other CircleEquation object
	 */
	CircleEquation(const CircleEquation& circle);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param circle object to be assigned 
	 * @return new CircleEquation object
	 */
    CircleEquation& operator=(const CircleEquation& circle);
	
	/**
	 * @brief Center point of circle getter
	 * 
	 * @return reference to center point of object 
	 */
	inline const PointEquation& getCenterPoint() const { return centerPoint; }

	/**
	 * @brief Radius length of circle getter
	 * 
	 * @return radius lenght of object 
	 */
	inline double getRadius() const { return radius; }

	/**
	 * @brief Calculating Y coordinates of points on a circle from their X coordinate
	 * 
	 * @param x value of point X coordinate 
	 * @param ys pointer to 2-element array into which Y coordinates of points will be written
	 * @return number of points which have the given coordinate X and lie on the circle 
	 */
	int getYs(double x, double ys[2]);

	/**
	 * @brief Calculating X coordinates of points on a circle from their Y coordinate
	 * 
	 * @param y value of point Y coordinate 
	 * @param xs pointer to 2-element array into which X coordinates of points will be written
	 * @return number of points which have the given coordinate Y and lie on the circle 
	 */
	int getXs(double y, double xs[2]);

	/**
	 * @brief Checking whether a point lies on a circle 
	 * 
	 * @param point point to check 
	 * @return true if given point lies on circle
	 * @return false if given point does not lies on circle
	 */
	bool liesOn(const PointEquation& point);

	/**
	 * @brief Creating a point that lies perfectly on the circle and is closest to the given one
	 * 
	 * @param point point which is a reference to a new point to be created
	 * @return point which lies perfectly on the circle 
	 */
	PointEquation getCenteredPoint(PointEquation& point);

	/**
	 * @brief Override of equality operator 
	 * 
	 * Circles are equal if centers are equal with some accuracy - Constans::BIG_EPSILON and radiuses are equal with some  accuracy - Constans::NORMAL_EPSILON
	 * 
	 * @param circle1 first object to compare
	 * @param circle2 second object to compare
	 * @return true if given circles are equal
	 * @return false if given circles are not equal
	 */
	friend bool operator== (const CircleEquation& circle1, const CircleEquation& circle2);

	/**
	 * @brief Override of equality operator 
	 * 
	 * Circles are equal if centers are equal with some accuracy - Constans::BIG_EPSILON and radiuses are equal with some accuracy - Constans::NORMAL_EPSILON
	 * 
	 * @param circle1 first object to compare
	 * @param circle2 second object to compare
	 * @return true if given circles are not equal
	 * @return false if given circles are equal
	 */
	friend bool operator!= (const CircleEquation& circle1, const CircleEquation& circle2);

	/**
	 * @brief Override of stream insertion operator 
	 * 
	 * @param stream object of ostream class
	 * @param circle object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const CircleEquation& circle);
};

#endif /* CIRCLE_EQUATION_H */