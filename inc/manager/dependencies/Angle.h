#ifndef ANGLE_H
#define ANGLE_H

#include "OrderedPair.h"

#include <iostream>

/**
 * @brief Class representing angle as "triple" of point IDs
 */
class Angle {
public:
	/**
	 * @brief Representing type of angle
	 */
	enum class AngleType {
		UNKNOWN,
		CONVEX,
		CONCAVE
	};

private:
	/**
	 * @brief Angle vertex ID
	 */
	int vertexId;

	/**
	 * @brief IDs of points which lies on ends of angle arms
	 */
	OrderedPair pointsOnArms;

	/**
	 * @brief Type of angle
	 */
	AngleType angleType;

public:
	/**
	 * @brief Constructor of a new Angle object
	 * 
	 * @param point1Id ID of point on first angle arm
	 * @param vertexId ID of angle vertex
	 * @param point2Id ID of point on second angle arm
	 * @param type type of angle
	 */
	Angle(int point1Id, int vertexId, int point2Id, AngleType type);

	/**
	 * @brief Constructor of a new Angle object
	 * 
	 * @param angle other Angle object
	 */
	Angle(const Angle& angle);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param angle object to be assigned 
	 * @return new Angle object
	 */
    Angle& operator=(const Angle& angle);

	/**
	 * @brief IDs of points on angle arms getter
	 * 
	 * @return IDs of points on angle arms
	 */
	inline const OrderedPair& getPointsOnArms() const { return pointsOnArms; }

	/**
	 * @brief ID of angle vertex getter
	 * 
	 * @return ID of angle vertex 
	 */
	inline int getVertex() const { return vertexId; }

	/**
	 * @brief Angle type getter
	 * 
	 * @return angle type 
	 */
	inline AngleType getType() const { return angleType; }

	/**
	 * @brief Override of equality operator 
	 * 
	 * @param angle1 first object to compare
	 * @param angle2 second object to compare
	 * @return true if given angles are equal
	 * @return false if given angles are not equal
	 */
	friend bool operator== (const Angle& angle1, const Angle& angle2);

	/**
	 * @brief Override of inequality operator 
	 * 
	 * @param angle1 first object to compare
	 * @param angle2 second object to compare
	 * @return true if given angles are not equal
	 * @return false if given angles are equal
	 */
	friend bool operator!= (const Angle& angle1, const Angle& angle2);

	/**
	 * @brief Override of less operator 
	 * 
	 * @param angle1 first object to compare
	 * @param angle2 second object to compare
	 * @return true if angle 1 is smaller than angle 2
	 * @return false if angle 1 is not smaller than angle 2
	 */
	friend bool operator< (const Angle& angle1, const Angle& angle2);

	/**
	 * @brief Override of greater operator 
	 * 
	 * @param angle1 first object to compare
	 * @param angle2 second object to compare
	 * @return true if angle 1 is greater than angle 2
	 * @return false if angle 1 is not greater than angle 2
	 */
	friend bool operator> (const Angle& angle1, const Angle& angle2);

	/**
	 * @brief Override of less or equal operator 
	 * 
	 * @param angle1 first object to compare
	 * @param angle2 second object to compare
	 * @return true if angle 1 is smaller than or equal angle 2
	 * @return false if angle 1 is not (smaller than or equal) angle 2
	 */
	friend bool operator<= (const Angle& angle1, const Angle& angle2);

	/**
	 * @brief Override of greater or equal operator 
	 * 
	 * @param angle1 first object to compare
	 * @param angle2 second object to compare
	 * @return true if angle 1 is greater than or equal angle 2
	 * @return false if angle 1 is not (greater than or equal) angle 2
	 */
	friend bool operator>= (const Angle& angle1, const Angle& angle2);

	/**
	 * @brief Override of stream insertion operator 
	 * 
	 * @param stream object of ostream class
	 * @param angle object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const Angle& angle);
};

#endif /* ANGLE_H */