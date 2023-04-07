#ifndef POINT_SHAPE_H
#define POINT_SHAPE_H

#include "./../../math/equations/PointEquation.h"

/**
 * @brief Class representing point shape. It inherits from PointEquation
 */
class PointShape: public PointEquation {
public:
	/**
	 * @brief Constructor of a new PointShape object
	 * 
	 * @param x X coordinate of point
	 * @param y Y coordinate of point
	 */
	PointShape(double x, double y);

	/**
	 * @brief Constructor of a new PointShape object
	 * 
	 * @param pointEquation PointEquation on which base the shape will be created
	 */
	PointShape(PointEquation pointEquation);

	/**
	 * @brief Constructor of a new PointShape object
	 * 
	 * @param point other PointShape object
	 */
	PointShape(const PointShape& point);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param point object to be assigned 
	 * @return new PointShape object
	 */
    PointShape& operator=(const PointShape& point);
};

#endif /* POINT_SHAPE_H */