#ifndef LINE_EQUATION_H
#define LINE_EQUATION_H

#include "PointEquation.h"
#include "./../Constans.h"
#include "./../Distance.h"

#include <string>
#include <stdexcept>

/**
 * @brief Class representing equation of line on XY plane
 */
class LineEquation {
public:
	/**
	 * @brief Representing type of line 
	 */
	enum class LineType{
		/**
		 * @brief The equation is of the form x = b
		 */
		VERTICAL,

		/**
		 * @brief The equation is of the form y = b
		 */
		HORIZONTAL,

		/**
		 * @brief The equation is of the form y = ax + b
		 */
		SLANTED
	};	

	/**
	 * @brief Class implementing a custom exception used in LineEquation class methods 
	 * when an attempt is made to create a line based on two equal points 
	 */
	class EqualPointsException : public virtual std::invalid_argument {
	public:
		/**
		 * @brief Constructor of a new EqualPointsException object
		 */
		EqualPointsException() : std::invalid_argument("Points cannot be equal! Points must be different!") { }
	};

	/**
	 * @brief Class implementing a custom exception used in LineEquation class methods 
	 * when an attempt is made to create a line based on two zero coefficients
	 */
	class ZeroCoefficientsException : public virtual std::invalid_argument {
	public:
		/**
		 * @brief Constructor of a new ZeroCoefficientsException object
		 */
		ZeroCoefficientsException() : std::invalid_argument("Coefficients A and B cannot be 0.0 at the same time!") { }
	};

	/**
	 * @brief A class implementing a custom exception used in LineEquation class methods 
	 * when an attempt is made to get the coordinates of a point lying on a line that is ambiguous 
	 */
	class AmbiguousQueryException : public virtual std::invalid_argument {
	public:
		/**
		 * @brief Constructor of a new AmbiguousQueryException object
		 */
		AmbiguousQueryException() : std::invalid_argument("The query cannot return a unique value! This is due to the characteristics of this line equation!") { }
	};


private:
	/**
	 * @brief Coefficient of x in standard form of line equation
	 */
	double A;

	/**
	 * @brief Coefficient of y in standard form of line equation
	 */
	double B;

	/**
	 * @brief Constant term in standard form of line equation
	 */
	double C;

	/**
	 * @brief Coefficient of x in point slope form of line equation
	 */
	double a;

	/**
	 * @brief Constant term in point slope form of line equation
	 */
	double b;
	
	/**
	 * @brief Type of line equation
	 */
	LineType lineType;

public:
	/**
	 * @brief Constructor a new LineEquation object
	 */
	LineEquation();

	/**
	 * @brief Constructor of a new LineEquation object
	 * 
	 * @param point1 the first point through which the line will pass 
	 * @param point2 the second point through which the line will pass 
	 * @throws EqualPointsException if point1 and point2 are equal
	 */
	LineEquation(const PointEquation& point1, const PointEquation& point2) noexcept(false);

	/**
	 * @brief Constructor of a new LineEquation object
	 * 
	 * @param coefficientA coefficient of x in standard form of line equation
	 * @param coefficientB coefficient of y in standard form of line equation
	 * @param coefficientC constant term in standard form of line equation
	 * @throws ZeroCoefficientsException if coefficientA and coefficientB are equal to 0
	 */
	LineEquation(double coefficientA, double coefficientB, double coefficientC) noexcept(false);
	
	/**
	 * @brief Constructor of a new LineEquation object
	 * 
	 * @param line other LineEquation object
	 */
	LineEquation(const LineEquation& line);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param line object to be assigned 
	 * @return new LineEquation object
	 */
    LineEquation& operator=(const LineEquation& line);

	/**
	 * @brief Line type getter
	 * 
	 * @return value of object line type 
	 */
	inline LineType getType() const { return lineType; };

	/**
	 * @brief Coefficient of x in standard form of line equation getter
	 * 
	 * @return value of object coefficient of x in standard form
	 */
	inline double getA() const { return A; };

	/**
	 * @brief Coefficient of y in standard form of line equation getter
	 * 
	 * @return value of object coefficient of y in standard form
	 */
	inline double getB() const { return B; };

	/**
	 * @brief Constant term in standard form of line equation getter
	 * 
	 * @return value of object constant term in standard form
	 */
	inline double getC() const { return C; };

	/**
	 * @brief Coefficient of x in point slope form of line equation getter
	 * 
	 * @return value of object coefficient of x in point slope form
	 */
	inline double geta() const { return a; };

	/**
	 * @brief Constant term in point slope form of line equation getter
	 * 
	 * @return value of object constant term in point slope form
	 */
	inline double getb() const { return b; };

	/**
	 * @brief Calculating the Y coordinate of a point on a line from its X coordinate
	 * 
	 * @param x value of point X coordinate 
	 * @return value of point Y coordinate  
	 * @throws AmbiguousQueryException if result is ambiguous
	 */
	double getY(double x) noexcept(false);

	/**
	 * @brief Calculating the X coordinate of a point on a line from its Y coordinate
	 * 
	 * @param y value of point Y coordinate 
	 * @return value of point X coordinate  
	 * @throws AmbiguousQueryException if result is ambiguous
	 */
	double getX(double y) noexcept(false);

	/**
	 * @brief Checking whether a point lies on a line 
	 * 
	 * @param point point to check 
	 * @return true if given point lies on line
	 * @return false if given point does not lies on line
	 */
	bool liesOn(const PointEquation& point);

	/**
	 * @brief Creating a point that lies perfectly on the line and is closest to the given one
	 * 
	 * @param point point which is a reference to a new point to be created
	 * @return point which lies perfectly on the line 
	 */
	PointEquation getCenteredPoint(PointEquation& point);

	/**
	 * @brief Zwraca punkt odlegly o distance od point1 w kierunku point2
	 * 
	 * @param point1 
	 * @param point2 
	 * @return PointEquation 
	 */
	PointEquation getPointBetweenPointsWithDistance(PointEquation& point1, PointEquation& point2, double distance);

	/**
	 * @brief Getting string representing object. Function generates different strings for two different objects
	 * 
	 * Lines are equal if their coefficients are equal to each other with some accuracy - 10 * Constans::SMALL_EPSILON and types are consistent
	 * 
	 * @return string representing object
	 */
	std::string getStringHash();

	/**
	 * @brief Override of equality operator 
	 * 
	 * Lines are equal if their coefficients are equal to each other with some accuracy - 10 * Constans::SMALL_EPSILON and types are consistent
	 * 
	 * @param line1 first object to compare
	 * @param line2 second object to compare
	 * @return true if given lines are equal
	 * @return false if given lines are not equal
	 */
	friend bool operator== (const LineEquation& line1, const LineEquation& line2);

	/**
	 * @brief Override of inequality operator 
	 * 
	 * Lines are equal if their coefficients are equal to each other with some accuracy - 10 * Constans::SMALL_EPSILON and types are consistent
	 * 
	 * @param line1 first object to compare
	 * @param line2 second object to compare
	 * @return true if given lines are not equal
	 * @return false if given lines are equal
	 */
	friend bool operator!= (const LineEquation& line1, const LineEquation& line2);

	/**
	 * @brief Override of stream insertion operator 
	 * 
	 * @param stream object of ostream class
	 * @param line object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const LineEquation& line);
};

#endif /* LINE_EQUATION_H */