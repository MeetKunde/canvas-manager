#ifndef ANGLE_VALUE_H
#define ANGLE_VALUE_H

#include "Angle.h"

#include <string>

/**
 * @brief Class representing angle value dependency
 */
class AngleValue {
private:
	/**
	 * @brief Angle
	 */
	Angle angle;

	/**
	 * @brief Set value
	 * 
	 * Saved as string - it can store number, letter or math expression
	 */
	std::string value;

public:
	/**
	 * @brief Constructor of a new AngleValue object
	 * 
	 * @param anglePoint1 ID of first point on angle
	 * @param vertexId ID of vertex point on angle
	 * @param anglePoint2Id ID of second point on angle
	 * @param type type of angle
	 * @param value value to set
	 * @param reason reason of dependency
	 */
	AngleValue(int anglePoint1, int vertexId, int anglePoint2Id, Angle::AngleType type, std::string value);

	/**
	 * @brief Constructor of a new AngleValue object
	 * 
	 * @param angleValue other AngleValue object
	 */
	AngleValue(const AngleValue& angleValue);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param angleValue object to be assigned 
	 * @return new AngleValue object
	 */
    AngleValue& operator=(const AngleValue& angleValue);

	/**
	 * @brief Angle object getter
	 * 
	 * @return reference to angle object
	 */
	const Angle& getAngle() const { return angle; }

	/**
	 * @brief Set value object getter
	 * 
	 * @return reference to angle value object
	 */
	const std::string& getValue() const { return value; }

	/**
	 * @brief Override of equality operator 
	 * 
	 * @param av1 first object to compare
	 * @param av2 second object to compare
	 * @return true if object are equal
	 * @return false if object are not equal
	 */
	friend bool operator== (const AngleValue& av1, const AngleValue& av2);

	/**
	 * @brief Override of inequality operator 
	 * 
	 * @param av1 first object to compare
	 * @param av2 second object to compare
	 * @return true if objects are not equal
	 * @return false if objects are equal
	 */
	friend bool operator!= (const AngleValue& av1, const AngleValue& av2);

	/**
	 * @brief Override of stream insertion operator
	 *
	 * @param stream object of ostream class
	 * @param angleValue object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const AngleValue& angleValue);
};

#endif /* ANGLE_VALUE_H */