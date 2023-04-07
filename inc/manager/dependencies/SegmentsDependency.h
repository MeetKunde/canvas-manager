#ifndef SEGMENTS_DEPENDENCY_H
#define SEGMENTS_DEPENDENCY_H

#include "OrderedPair.h"

/**
 * @brief Class representing dependency between 2 segments
 */
class SegmentsDependency {
private:
	/**
	 * @brief Pair representing IDs of first segment ends
	 */
	OrderedPair segment1;

	/**
	 * @brief Pair representing IDs of second segment ends
	 */
	OrderedPair segment2;

public:
	/**
	 * @brief Constructor of a new SegmentsDependency object
	 * 
	 * @param segment1End1 ID of first end point of first segment 
	 * @param segment1End2 ID of second end point of first segment
	 * @param segment2End1 ID of first end point of second segment 
	 * @param segment2End2 ID of second end point of second segment
	 * @param reason dependency reason
	 */
	SegmentsDependency(int segment1End1, int segment1End2, int segment2End1, int segment2End2);

	/**
	 * @brief Constructor of a new SegmentsDependency object
	 * 
	 * @param segmentDependency other SegmentsDependency object
	 */
	SegmentsDependency(const SegmentsDependency& segmentDependency);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param segmentDependency object to be assigned 
	 * @return new SegmentsDependency object
	 */
    SegmentsDependency& operator=(const SegmentsDependency& segmentDependency);

	/**
	 * @brief First segment ends pair object getter
	 * 
	 * @return reference to frst segment ends pair object
	 */
	const OrderedPair& getSegment1Ends() const { return segment1; }

	/**
	 * @brief Second segment ends pair object getter
	 * 
	 * @return reference to second segment ends pair object
	 */
	const OrderedPair& getSegment2Ends() const { return segment2; }

	/**
	 * @brief Override of equality operator 
	 * 
	 * @param sd1 first object to compare
	 * @param sd2 second object to compare
	 * @return true if object are equal
	 * @return false if object are not equal
	 */
	friend bool operator== (const SegmentsDependency& sd1, const SegmentsDependency& sd2);

	/**
	 * @brief Override of inequality operator 
	 * 
	 * @param sd1 first object to compare
	 * @param sd2 second object to compare
	 * @return true if objects are not equal
	 * @return false if objects are equal
	 */
	friend bool operator!= (const SegmentsDependency& sd1, const SegmentsDependency& sd2);

	/**
	 * @brief Override of stream insertion operator
	 *
	 * @param stream object of ostream class
	 * @param segmentsDependency object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const SegmentsDependency& segmentsDependency);
};

#endif /* SEGMENTS_DEPENDENCY_H */