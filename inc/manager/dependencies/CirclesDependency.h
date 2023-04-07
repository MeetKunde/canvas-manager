#ifndef CIRCLES_DEPENDENCY_H
#define CIRCLES_DEPENDENCY_H

#include "OrderedPair.h"

class CirclesDependency : public OrderedPair {
public:
	CirclesDependency(int circle1Id, int circle2Id);

	CirclesDependency(const CirclesDependency& CirclesDependency);

    CirclesDependency& operator=(const CirclesDependency& circlesDependency);

	friend bool operator== (const CirclesDependency& ld1, const CirclesDependency& ld2);

	friend bool operator!= (const CirclesDependency& ld1, const CirclesDependency& ld2);

	friend std::ostream& operator<< (std::ostream& stream, const CirclesDependency& CirclesDependency);
};

#endif /* CIRCLES_DEPENDENCY_H */