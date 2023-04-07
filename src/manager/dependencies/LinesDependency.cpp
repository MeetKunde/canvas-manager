#include "./../../../inc/manager/dependencies/LinesDependency.h"

LinesDependency::LinesDependency(int line1Id, int line2Id)
: OrderedPair(line1Id, line2Id) { }

LinesDependency::LinesDependency(const LinesDependency& linesDependency)
: OrderedPair(linesDependency) { }

LinesDependency& LinesDependency::operator=(const LinesDependency& linesDependency) {
    OrderedPair::operator=(linesDependency);

    return *this;
}

bool operator==(const LinesDependency& ld1, const LinesDependency& ld2) {
    return ld1.getFirst() == ld2.getFirst() && ld1.getSecond() == ld2.getSecond();
}

bool operator!=(const LinesDependency& ld1, const LinesDependency& ld2) {
    return !(ld1 == ld2);
}

std::ostream& operator<< (std::ostream& stream, const LinesDependency& linesDependency) {
    stream << "line " << linesDependency.getFirst() << " and " << linesDependency.getSecond();
    
    return stream;
}