#ifndef SEGMENT_SHAPE_H
#define SEGMENT_SHAPE_H

#include "./../../math/equations/LineEquation.h"
#include "PointShape.h"

#include <cmath>

/**
 * @brief Class representing segment shape. It inherits from LineEquation
 */
class SegmentShape: public LineEquation {
private:
	/**
	 * @brief 2-element array with IDs of segment ends
	 * 
	 * It is sorted by PointShapes coordinates
	 */
	unsigned int endIds[2];

	/**
	 * @brief 2-element array with PointShapes that are ends of a segment 
	 * 
	 * It is sorted by PointShapes coordinates
	 */
	PointShape ends[2];

public:
	/**
	 * @brief Constructor of a new SegmentShape object
	 * 
	 * @param point1 object of first end
	 * @param point1Id ID of object of first end
	 * @param point2 object of second end
	 * @param point2Id ID of object of second end
	 * @throws LineEquation::EqualPointsException if point1 is equal to point2
	 */
	SegmentShape(PointShape& point1, unsigned int point1Id, PointShape& point2, unsigned int point2Id) noexcept(false);

	/**
	 * @brief Constructor a new SegmentShape object
	 * 
	 * @param segment other SegmentShape object
	 */
	SegmentShape(const SegmentShape& segment);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param segment object to be assignment
	 * @return new SegmentShape object
	 */
    SegmentShape& operator=(const SegmentShape& segment);

	/**
	 * @brief First end ID getter
	 * 
	 * @return value of first end ID object 
	 */
	inline unsigned int getEnd1Id() const { return endIds[0]; }

	/**
	 * @brief Second end ID getter
	 * 
	 * @return value of second end ID object  
	 */
	inline unsigned int getEnd2Id() const { return endIds[1]; }

	/**
	 * @brief First end object getter
	 * 
	 * @return reference to first end point object
	 */
	inline const PointShape& getEnd1() const { return ends[0]; }

	/**
	 * @brief Second end object getter
	 * 
	 * @return reference to second end point object
	 */
	inline const PointShape& getEnd2() const { return ends[1]; }

	/**
	 * @brief Checking whether a point lies on a segment 
	 * 
	 * If point is one of segment ends function returns false
	 * 
	 * @param point point to check 
	 * @return true if given point lies on segment
	 * @return false if given point does not lies on segment
	 */
	bool liesOn(const PointShape& point);

	/**
	 * @brief Override of equality operator 
	 * 
	 * @param segment1 first object to compare
	 * @param segment2 second object to compare
	 * @return true if given segments are equal
	 * @return false if given segments are not equal
	 */
	friend bool operator== (const SegmentShape& segment1, const SegmentShape& segment2);
	
	/**
	 * @brief Override of inequality operator 
	 * 
	 * @param segment1 first object to compare
	 * @param segment2 second object to compare
	 * @return true if given segments are not equal
	 * @return false if given segments are equal
	 */
	friend bool operator!= (const SegmentShape& segment1, const SegmentShape& segment2);

	/**
	 * @brief Override of stream insertion operator
	 *
	 * @param stream object of ostream class
	 * @param segment object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const SegmentShape& segment);
};

#endif /* SEGMENT_SHAPE_H */