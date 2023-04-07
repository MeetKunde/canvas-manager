#include "./../../../inc/manager/dependencies/LineAngleDependency.h"

LineAngleDependency::LineAngleDependency(unsigned int line, unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, Angle::AngleType angleType)
: lineId(line), angle(Angle(point1Id, vertexId, point2Id, angleType)) { }
    
LineAngleDependency::LineAngleDependency(const LineAngleDependency& lineAngleDependency) 
: lineId(lineAngleDependency.lineId), angle(lineAngleDependency.angle) { }

LineAngleDependency& LineAngleDependency::operator=(const LineAngleDependency& lineAngleDependency) {
    lineId = lineAngleDependency.lineId;
    angle = lineAngleDependency.angle;

    return *this;
}

bool operator== (const LineAngleDependency& lad1, const LineAngleDependency& lad2) {
    return lad1.lineId == lad2.lineId && lad1.angle == lad2.angle;
}

bool operator!= (const LineAngleDependency& lad1, const LineAngleDependency& lad2) {
    return !(lad1 == lad2);
}

std::ostream& operator<< (std::ostream& stream, const LineAngleDependency& lineAngleDependency) {
    stream << "line " << lineAngleDependency.getLineId() << " and angle " << lineAngleDependency.getAngle();

    return stream;
}