#include "./../../../inc/manager/dependencies/AngleValue.h"

AngleValue::AngleValue(int anglePoint1Id, int vertexId, int anglePoint2Id, Angle::AngleType type, std::string value)
: angle(Angle(anglePoint1Id, vertexId, anglePoint2Id, type)), value(value) { }

AngleValue::AngleValue(const AngleValue& angleValue)
: angle(Angle(angleValue.angle)), value(angleValue.value) {}

AngleValue& AngleValue::operator=(const AngleValue& angleValue) {
    angle = Angle(angleValue.angle);
    value = angleValue.value;

    return *this;
}

bool operator== (const AngleValue& av1, const AngleValue& av2) {
    return av1.angle == av2.angle && av1.value == av2.value;
}

bool operator!= (const AngleValue& av1, const AngleValue& av2) {
    return !(av1 == av2);
}

std::ostream& operator<< (std::ostream& stream, const AngleValue& angleValue) {
    stream << "value of angle " << angleValue.getAngle() << " = " << angleValue.getValue();

    return stream;
}