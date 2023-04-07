#include "./../../../inc/manager/dependencies/OrderedPair.h"

OrderedPair::OrderedPair(int element1, int element2) {
	if (element1 < element2) {
		firstElement = element1;
		secondElement = element2;
	}
	else {
		firstElement = element2;
		secondElement = element1;
	}
}

OrderedPair::OrderedPair(const OrderedPair& orderedPair) 
: firstElement(orderedPair.firstElement), secondElement(orderedPair.secondElement) { }

OrderedPair& OrderedPair::operator=(const OrderedPair& orderedPair) {
	firstElement = orderedPair.firstElement;
	secondElement = orderedPair.secondElement;

	return *this;
}

bool operator==(const OrderedPair& line1, const OrderedPair& line2) {
	return line1.firstElement == line2.firstElement && line1.secondElement == line2.secondElement;
}

bool operator!=(const OrderedPair& line1, const OrderedPair& line2) {
	return !(line1 == line2);
}

bool operator<(const OrderedPair& line1, const OrderedPair& line2) {
	if (line1.firstElement == line2.firstElement) {
		return line1.secondElement < line2.secondElement;
	}
	else {
		return line1.firstElement < line2.firstElement;
	}
}

bool operator>(const OrderedPair& line1, const OrderedPair& line2) {
	return line2 < line1;
}

bool operator<=(const OrderedPair& line1, const OrderedPair& line2) {
	return line1 == line2 || line1 < line2;
}

bool operator>=(const OrderedPair& line1, const OrderedPair& line2) {
	return line1 == line2 || line1 > line2;
}

std::ostream& operator<<(std::ostream& stream, const OrderedPair& line) {
	stream << "(" << line.firstElement << ", " << line.secondElement << ")";

	return stream;
}
