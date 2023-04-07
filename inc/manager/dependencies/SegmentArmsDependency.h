#ifndef SEGMENT_ARMS_DEPENDENCY_H
#define SEGMENT_ARMS_DEPENDENCY_H

#include "OrderedPair.h"

class SegmentArmsDependency {
private:
    OrderedPair arm1;
    OrderedPair arm2;
    OrderedPair segment;

public:
    SegmentArmsDependency(unsigned int arm1End1, unsigned int arm1End2, unsigned int arm2End1, unsigned int arm2End2, unsigned int segmentEnd1, unsigned int segmentEnd2);
    SegmentArmsDependency(const SegmentArmsDependency& segmentArmsDependency);

    SegmentArmsDependency& operator=(const SegmentArmsDependency& segmentArmsDependency);

    const OrderedPair& getArm1Ends() const { return arm1; }
    const OrderedPair& getArm2Ends() const { return arm2; }
    const OrderedPair& getSegmentEnds() const { return segment; }

    friend bool operator== (const SegmentArmsDependency& lhs, const SegmentArmsDependency& rhs);
    friend bool operator!= (const SegmentArmsDependency& lhs, const SegmentArmsDependency& rhs);

    friend std::ostream& operator<< (std::ostream& stream, const SegmentArmsDependency& segmentArmsDependency);
};

#endif /* SEGMENT_ARMS_DEPENDENCY_H */