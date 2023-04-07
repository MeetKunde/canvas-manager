#include "./../../../inc/manager/dependencies/SegmentsDependency.h"

SegmentsDependency::SegmentsDependency(int segment1End1, int segment1End2, int segment2End1, int segment2End2)
: segment1(OrderedPair(segment1End1, segment1End2)), 
  segment2(OrderedPair(segment2End1, segment2End2)) { 

    if (segment1 < segment2) {
        //segment1 = OrderedPair(segment1End1, segment1End2);
        //segment2 = OrderedPair(segment2End1, segment2End2);
    }
    else {
        segment1 = OrderedPair(segment2End1, segment2End2);
        segment2 = OrderedPair(segment1End1, segment1End2);
    }
}

SegmentsDependency::SegmentsDependency(const SegmentsDependency& segmentDependency)
: segment1(OrderedPair(segmentDependency.segment1)), segment2(OrderedPair(segmentDependency.segment2)) { }

SegmentsDependency& SegmentsDependency::operator=(const SegmentsDependency& segmentDependency) {
    segment1 = OrderedPair(segmentDependency.segment1);
    segment2 = OrderedPair(segmentDependency.segment2);

    return *this;
}

bool operator==(const SegmentsDependency& sd1, const SegmentsDependency& sd2) {
    return sd1.segment1 == sd2.segment1 && sd1.segment2 == sd2.segment2;
}

bool operator!=(const SegmentsDependency& sd1, const SegmentsDependency& sd2) {
    return !(sd1 == sd2);
}

std::ostream& operator<< (std::ostream& stream, const SegmentsDependency& segmentsDependency) {
    stream << "segment " << segmentsDependency.getSegment1Ends() << " and " << segmentsDependency.getSegment2Ends();

    return stream;
}