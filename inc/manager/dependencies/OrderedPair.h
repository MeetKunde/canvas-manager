#ifndef ORDERED_PAIR_H
#define ORDERED_PAIR_H

#include <iostream>

/**
 * @brief Class representing ordered pair of integers
 */
class OrderedPair {
private:
	/**
	 * @brief Value of first element
	 */
	int firstElement;

	/**
	 * @brief Value of second element
	 */
	int secondElement;

public:
	/**
	 * @brief Constructor of a new OrderedPair object
	 * 
	 * @param element1 first pair element
	 * @param element2 second pair element
	 */
	OrderedPair(int element1, int element2);

	/**
	 * @brief Constructor of a new OrderedPair object
	 * 
	 * @param orderedPair other OrderedPair object
	 */
	OrderedPair(const OrderedPair& orderedPair);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param orderedPair object to be assigned 
	 * @return new OrderedPair object
	 */
    OrderedPair& operator=(const OrderedPair& orderedPair);

	/**
	 * @brief First element getter
	 * 
	 * @return value of first element 
	 */
	inline int getFirst() const { return firstElement; }

	/**
	 * @brief Second element getter
	 * 
	 * @return value of second element 
	 */
	inline int getSecond() const { return secondElement; }

	/**
	 * @brief Override of equality operator 
	 * 
	 * @param orderedPair1 first object to compare
	 * @param orderedPair2 second object to compare
	 * @return true if pairs are equal
	 * @return false if pairs are not equal
	 */
	friend bool operator== (const OrderedPair& orderedPair1, const OrderedPair& orderedPair2);

	/**
	 * @brief Override of inequality operator 
	 * 
	 * @param orderedPair1 first object to compare
	 * @param orderedPair2 second object to compare
	 * @return true if pairs are not equal
	 * @return false if pairs are equal
	 */
	friend bool operator!= (const OrderedPair& orderedPair1, const OrderedPair& orderedPair2);

	/**
	 * @brief Override of less operator 
	 * 
	 * @param orderedPair1 first object to compare
	 * @param orderedPair2 second object to compare
	 * @return true if pair 1 is smaller than pair 2
	 * @return false if pair 1 is not smaller than pair 2
	 */
	friend bool operator< (const OrderedPair& orderedPair1, const OrderedPair& orderedPair2);

	/**
	 * @brief Override of greater operator 
	 * 
	 * @param orderedPair1 first object to compare
	 * @param orderedPair2 second object to compare
	 * @return true if pair 1 is greater than pair 2
	 * @return false if pair 1 is not greater than pair 2
	 */
	friend bool operator> (const OrderedPair& orderedPair1, const OrderedPair& orderedPair2);

	/**
	 * @brief Override of less or equal operator 
	 * 
	 * @param orderedPair1 first object to compare
	 * @param orderedPair2 second object to compare
	 * @return true if pair 1 is smaller than or equal pair 2
	 * @return false if pair 1 is not (smaller than or equal) pair 2
	 */
	friend bool operator<= (const OrderedPair& orderedPair1, const OrderedPair& orderedPair2);

	/**
	 * @brief Override of greater or equal operator 
	 * 
	 * @param orderedPair1 first object to compare
	 * @param orderedPair2 second object to compare
	 * @return true if pair 1 is greater than or equal pair 2
	 * @return false if pair 1 is not (greater than or equal) pair 2
	 */
	friend bool operator>= (const OrderedPair& orderedPair1, const OrderedPair& orderedPair2);

	/**
	 * @brief Override of stream insertion operator 
	 * 
	 * @param stream object of ostream class
	 * @param orderedPair object to insert to stream
	 * @return object of ostream class
	 */
	friend std::ostream& operator<< (std::ostream& stream, const OrderedPair& orderedPair);
};

#endif /* ORDERED_PAIR_H */