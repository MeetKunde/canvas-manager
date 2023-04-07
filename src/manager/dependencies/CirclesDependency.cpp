#include "./../../../inc/manager/dependencies/CirclesDependency.h"

CirclesDependency::CirclesDependency(int circle1Id, int circle2Id)
: OrderedPair(circle1Id, circle2Id) { }

CirclesDependency::CirclesDependency(const CirclesDependency& circlesDependency)
: OrderedPair(circlesDependency) { }

CirclesDependency& CirclesDependency::operator=(const CirclesDependency& circlesDependency) {
    OrderedPair::operator=(circlesDependency);

    return *this;
}

bool operator==(const CirclesDependency& ld1, const CirclesDependency& ld2) {
    return ld1.getFirst() == ld2.getFirst() && ld1.getSecond() == ld2.getSecond();
}

bool operator!=(const CirclesDependency& ld1, const CirclesDependency& ld2) {
    return !(ld1 == ld2);
}

std::ostream& operator<< (std::ostream& stream, const CirclesDependency& circlesDependency) {
    stream << "circle " << circlesDependency.getFirst() << " and " << circlesDependency.getSecond();
    
    return stream;
}