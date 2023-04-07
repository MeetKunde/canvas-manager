#include "./../../../inc/manager/dependencies/AnglesDependency.h"

AnglesDependency::AnglesDependency(int angle1Point1Id, int angle1VertexId, int angle1Point2Id, Angle::AngleType angle1Type, int angle2Point1Id, int angle2VertexId, int angle2Point2Id, Angle::AngleType angle2Type)
: angle1(Angle(angle1Point1Id, angle1VertexId, angle1Point2Id, angle1Type)),
  angle2(Angle(angle2Point1Id, angle2VertexId, angle2Point2Id, angle2Type)) {
    
    if (angle1 < angle2) {
        //angle1 = Angle(angle1Point1Id, angle1VertexId, angle1Point2Id, angle1Type);
        //angle2 = Angle(angle2Point1Id, angle2VertexId, angle2Point2Id, angle2Type);
    }
    else {
        angle1 = Angle(angle2Point1Id, angle2VertexId, angle2Point2Id, angle2Type);
        angle2 = Angle(angle1Point1Id, angle1VertexId, angle1Point2Id, angle1Type);
    }
}

AnglesDependency::AnglesDependency(const AnglesDependency& angleDependency)
: angle1(Angle(angleDependency.angle1)),
  angle2(Angle(angleDependency.angle2)) { }

AnglesDependency& AnglesDependency::operator=(const AnglesDependency& angleDependency) {
    angle1 = Angle(angleDependency.angle1);
    angle2 = Angle(angleDependency.angle2);

    return *this;
}

bool operator==(const AnglesDependency& ad1, const AnglesDependency& ad2) {
    return ad1.angle1 == ad2.angle1 && ad1.angle2 == ad2.angle2;
}

bool operator!=(const AnglesDependency& ad1, const AnglesDependency& ad2) {
    return !(ad1 == ad2);
}

std::ostream& operator<< (std::ostream& stream, const AnglesDependency& anglesDependency) {
    stream << "angle " << anglesDependency.getAngle1() << " and " << anglesDependency.getAngle2();

    return stream;
}