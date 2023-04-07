#ifndef LINES_DEPENDENCY_H
#define LINES_DEPENDENCY_H

#include "OrderedPair.h"

/**
 * @brief Class representing dependency between 2 lines
 */
class LinesDependency : public OrderedPair {
public:
	/**
	 * @brief Constructor of a new Lines Dependency object
	 * 
	 * @param line1Id 
	 * @param line2Id 
	 * @param reason 
	 */
	LinesDependency(int line1Id, int line2Id);

	/**
	 * @brief Constructor of a new LinesDependency object
	 * 
	 * @param linesDependency other LinesDependency object
	 */
	LinesDependency(const LinesDependency& linesDependency);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param linesDependency object to be assigned 
	 * @return new LinesDependency object
	 */
    LinesDependency& operator=(const LinesDependency& linesDependency);

	/**
	 * @brief Override of equality operator 
	 * 
	 * @param ld1 first object to compare
	 * @param ld2 second object to compare
	 * @return true if object are equal
	 * @return false if object are not equal
	 */
	friend bool operator== (const LinesDependency& ld1, const LinesDependency& ld2);

	/**
	 * @brief Override of inequality operator 
	 * 
	 * @param ld1 first object to compare
	 * @param ld2 second object to compare
	 * @return true if objects are not equal
	 * @return false if objects are equal
	 */
	friend bool operator!= (const LinesDependency& ld1, const LinesDependency& ld2);

	/**
	 * @brief Override of stream insertion operator
	 *
	 * @param stream object of ostream class
	 * @param linesDependency object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const LinesDependency& linesDependency);
};

#endif /* LINES_DEPENDENCY_H */