#ifndef LINE_ANGLE_DEPENDENCY_H
#define LINE_ANGLE_DEPENDENCY_H

#include "Angle.h"

class LineAngleDependency {
private:
    unsigned int lineId;
    Angle angle;

public:
    LineAngleDependency(unsigned int line, unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, Angle::AngleType angleType);
    LineAngleDependency(const LineAngleDependency& lineAngleDependency);

    LineAngleDependency& operator=(const LineAngleDependency& lineAngleDependency);

    unsigned int getLineId() const { return lineId; }
    const Angle& getAngle() const { return angle; }

    friend bool operator== (const LineAngleDependency& lad1, const LineAngleDependency& lad2);
    friend bool operator!= (const LineAngleDependency& lad1, const LineAngleDependency& lad2);

    friend std::ostream& operator<< (std::ostream& stream, const LineAngleDependency& lineAngleDependency);
};

#endif /* LINE_ANGLE_DEPENDENCY_H */