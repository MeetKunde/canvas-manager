#ifndef CIRCLE_SHAPE_H
#define CIRCLE_SHAPE_H

#include "./../../math/equations/CircleEquation.h"
#include <set>

/**
 * @brief Class representing circle shape. It inherits from CircleEquation
 */
class CircleShape : public CircleEquation {
private:
	/**
	 * @brief ID of circle center point
	 */
	unsigned int centerId;

	/**
	 * @brief Set of IDs of points which lies o circle
	 */
	std::set<unsigned int> includedPointIds;

public:
	/**
	 * @brief Constructor of a new CircleShape object
	 * 
	 * @param centerPoint object of center point
	 * @param centerPointId ID of object of center point
	 * @param pointOnCircle object of one point which lies on circle
	 * @param pointOnCircleId ID of object of one point which lies on circle
	 */
	CircleShape(PointEquation& centerPoint, unsigned int centerPointId, PointEquation& pointOnCircle, unsigned int pointOnCircleId);

	/**
	 * @brief Constructor of a new CircleShape object
	 * 
	 * @param circle other CircleShape object
	 */
	CircleShape(const CircleShape& circle);
	
	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param circle object to be assignment
	 * @return new CircleShape object 
	 */
    CircleShape& operator=(const CircleShape& circle);

	/**
	 * @brief Circle center point ID getter
	 * 
	 * @return value of ID of center point object 
	 */
	inline unsigned int getCenterId() const { return centerId; }

	/**
	 * @brief Reference to set of included points IDs getter
	 * 
	 * @return reference to set of included points IDs object
	 */
	inline const std::set<unsigned int>* getIncludedPoints() const { return &includedPointIds; }

	/**
	 * @brief Adding new included point object ID
	 * 
	 * @param includedPointId ID of point object to add
	 */
	inline void addIncludedPoint(unsigned int includedPointId) { std::cout << "ADED: " << includedPointId << " with start size " << includedPointIds.size(); includedPointIds.insert(includedPointId); std::cout << " after " << includedPointIds.size() << std::endl; }
	
};

#endif /* CIRCLE_SHAPE_H */