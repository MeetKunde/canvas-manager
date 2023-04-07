#include "./../../../inc/manager/dependencies/LineSegmentDependency.h"

LineSegmentDependency::LineSegmentDependency(unsigned int line, unsigned int end1Id, unsigned int end2Id) 
: lineId(line), segment(OrderedPair(end1Id, end2Id)) { }

LineSegmentDependency::LineSegmentDependency(const LineSegmentDependency& lineSegmentDependency)
: lineId(lineSegmentDependency.lineId), segment(lineSegmentDependency.segment) { }

LineSegmentDependency& LineSegmentDependency::operator= (const LineSegmentDependency& lineSegmentDependency) {
    lineId = lineSegmentDependency.lineId;
    segment = lineSegmentDependency.segment;

    return *this;
}

bool operator== (const LineSegmentDependency& lsd1, const LineSegmentDependency& lsd2) {
    return lsd1.lineId == lsd2.lineId && lsd1.segment == lsd2.segment;
}

bool operator!= (const LineSegmentDependency& lsd1, const LineSegmentDependency& lsd2) {
    return !(lsd1 == lsd2);
}

std::ostream& operator<< (std::ostream& stream, const LineSegmentDependency& lineSegmentDependency) {
    stream << "line " << lineSegmentDependency.getLineId() << " and segment " << lineSegmentDependency.getSegment();

    return stream;
}
