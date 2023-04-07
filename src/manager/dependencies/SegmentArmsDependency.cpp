#include "./../../../inc/manager/dependencies/SegmentArmsDependency.h"


SegmentArmsDependency::SegmentArmsDependency(unsigned int arm1End1, unsigned int arm1End2, unsigned int arm2End1, unsigned int arm2End2, unsigned int segmentEnd1, unsigned int segmentEnd2)
: arm1(arm1End1, arm1End2), arm2(arm2End1, arm2End2), segment(segmentEnd1, segmentEnd2) { }

SegmentArmsDependency::SegmentArmsDependency(const SegmentArmsDependency& segmentArmsDependency) 
: arm1(segmentArmsDependency.arm1), arm2(segmentArmsDependency.arm2), segment(segmentArmsDependency.segment) { }

SegmentArmsDependency& SegmentArmsDependency::operator=(const SegmentArmsDependency& segmentArmsDependency) {
    arm1 = segmentArmsDependency.arm1;
    arm2 = segmentArmsDependency.arm2;
    segment = segmentArmsDependency.segment;

    return *this;
}

bool operator== (const SegmentArmsDependency& lhs, const SegmentArmsDependency& rhs) {
    return lhs.arm1 == rhs.arm1 && lhs.arm2 == rhs.arm2 && lhs.segment == rhs.segment;
}
bool operator!= (const SegmentArmsDependency& lhs, const SegmentArmsDependency& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<< (std::ostream& stream, const SegmentArmsDependency& segmentArmsDependency) {
    stream << segmentArmsDependency.arm1 << " and " << segmentArmsDependency.arm2 << " with " << segmentArmsDependency.segment;
    
    return stream;
}
    