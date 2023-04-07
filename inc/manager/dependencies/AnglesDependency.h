#ifndef ANGLES_DEPENDENCY_H
#define ANGLES_DEPENDENCY_H

#include "Angle.h"

/**
 * @brief Class representing dependency betweeen 2 angles
 */
class AnglesDependency {
private:
	/**
	 * @brief First angle
	 */
	Angle angle1;

	/**
	 * @brief Second angle
	 */
	Angle angle2;

public:
	/**
	 * @brief Constructor of a new AnglesDependency object
	 * 
	 * @param angle1Point1Id ID of first point on first angle
	 * @param angle1VertexId ID of vertex point on first angle
	 * @param angle1Point2Id ID of second point on first angle
	 * @param angle1Type type of first angle
	 * @param angle2Point1Id ID of first point on second angle
	 * @param angle2VertexId ID of vertex point on second angle
	 * @param angle2Point2Id ID of second point on second angle
	 * @param angle2Type type of second angle
	 * @param reason reason of dependency
	 */
	AnglesDependency(int angle1Point1Id, int angle1VertexId, int angle1Point2Id, Angle::AngleType angle1Type, int angle2Point1Id, int angle2VertexId, int angle2Point2Id, Angle::AngleType angle2Type);

	/**
	 * @brief Constructor of a new AnglesDependency object
	 *
	 * @param angleDependency other AnglesDependency object
	 */
	AnglesDependency(const AnglesDependency& angleDependency);

	/**
	 * @brief Override of the assignment operator
	 *
	 * @param angleDependency object to be assigned
	 * @return new AnglesDependency object
	 */
	AnglesDependency& operator=(const AnglesDependency& angleDependency);

	/**
	 * @brief First angle object getter
	 * 
	 * @return reference to first angle object
	 */
	const Angle& getAngle1() const { return angle1; }

	/**
	 * @brief Second angle object getter
	 * 
	 * @return reference to second angle object
	 */
	const Angle& getAngle2() const { return angle2; }

	/**
	 * @brief Override of equality operator 
	 * 
	 * @param ad1 first object to compare
	 * @param ad2 second object to compare
	 * @return true if object are equal
	 * @return false if object are not equal
	 */
	friend bool operator== (const AnglesDependency& ad1, const AnglesDependency& ad2);

	/**
	 * @brief Override of inequality operator 
	 * 
	 * @param ad1 first object to compare
	 * @param ad2 second object to compare
	 * @return true if objects are not equal
	 * @return false if objects are equal
	 */
	friend bool operator!= (const AnglesDependency& ad1, const AnglesDependency& ad2);

	/**
	 * @brief Override of stream insertion operator
	 *
	 * @param stream object of ostream class
	 * @param anglesDependency object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const AnglesDependency& anglesDependency);
};

#endif /* ANGLES_DEPENDENCY_H */