#ifndef SEGMENT_LENGTH_H
#define SEGMENT_LENGTH_H

#include "OrderedPair.h"

#include <string>

/**
 * @brief Class representing segment length value dependency
 * 
 */
class SegmentLength {
private:
	/**
	 * @brief Pair representing IDs of segment ends
	 */
	OrderedPair segment;

	/**
	 * @brief Set length
	 * 
	 * Saved as string - it can store number, letter or math expression
	 */
	std::string value;

public:
	/**
	 * @brief Constructor of a new SegmentLength object
	 * 
	 * @param end1Id ID of first end point ID
	 * @param end2Id ID of second end point ID
	 * @param value value to set
	 * @param reason reason of dependency 
	 */
	SegmentLength(int end1Id, int end2Id, std::string value);

	/**
	 * @brief Constructor of a new SegmentLength object
	 * 
	 * @param segmentLength other SegmentLength object
	 */
	SegmentLength(const SegmentLength& segmentLength);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param segmentLenght object to be assigned 
	 * @return new SegmentLength object
	 */
    SegmentLength& operator=(const SegmentLength& segmentLenght);

	/**
	 * @brief Segment object getter
	 * 
	 * @return reference to segment object
	 */
	const OrderedPair& getSegment() const { return segment; }

	/**
	 * @brief Value object getter
	 * 
	 * @return reference to value object 
	 */
	const std::string& getValue() const { return value; }

	/**
	 * @brief Override of equality operator 
	 * 
	 * @param sl1 first object to compare
	 * @param sl2 second object to compare
	 * @return true if object are equal
	 * @return false if object are not equal
	 */
	friend bool operator== (const SegmentLength& sl1, const SegmentLength& sl2);

	/**
	 * @brief Override of inequality operator 
	 * 
	 * @param sl1 first object to compare
	 * @param sl2 second object to compare
	 * @return true if objects are not equal
	 * @return false if objects are equal
	 */
	friend bool operator!= (const SegmentLength& sl1, const SegmentLength& sl2);

	/**
	 * @brief Override of stream insertion operator
	 *
	 * @param stream object of ostream class
	 * @param segmentLength object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const SegmentLength& segmentLength);
};

#endif /* SEGMENT_LENGTH_H */