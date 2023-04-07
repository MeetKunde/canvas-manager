#ifndef LINE_SEGMENT_DEPENDENCY_H
#define LINE_SEGMENT_DEPENDENCY_H

#include "OrderedPair.h"

class LineSegmentDependency {
private:
    unsigned int lineId;
    OrderedPair segment;

public:
    LineSegmentDependency(unsigned int line, unsigned int end1Id, unsigned int end2Id);
    LineSegmentDependency(const LineSegmentDependency& lineSegmentDependency);

    LineSegmentDependency& operator= (const LineSegmentDependency& lineSegmentDependency);

    unsigned int getLineId() const { return lineId; }
    const OrderedPair& getSegment() const { return segment; }

    friend bool operator== (const LineSegmentDependency& lsd1, const LineSegmentDependency& lsd2);
    friend bool operator!= (const LineSegmentDependency& lsd1, const LineSegmentDependency& lsd2);

    friend std::ostream& operator<< (std::ostream& stream, const LineSegmentDependency& lineSegmentDependency);
};

#endif /* LINE_SEGMENT_DEPENDENCY_H */