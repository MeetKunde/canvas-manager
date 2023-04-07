#include "./../../../inc/manager/dependencies/Angle.h"

Angle::Angle(int point1Id, int vertexId, int point2Id, AngleType type) 
: pointsOnArms(OrderedPair(point1Id, point2Id)), vertexId(vertexId), angleType(type) { }

Angle::Angle(const Angle& angle) 
: pointsOnArms(OrderedPair(angle.pointsOnArms)), vertexId(angle.vertexId), angleType(angle.angleType) { }

Angle& Angle::operator=(const Angle& angle) {
	pointsOnArms = OrderedPair(angle.pointsOnArms);
	vertexId = angle.vertexId;
	angleType = angle.angleType;

	return *this;
}

bool operator==(const Angle& angle1, const Angle& angle2) {
	return angle1.pointsOnArms == angle2.pointsOnArms && angle1.vertexId == angle2.vertexId && 
	(angle1.angleType == angle2.angleType || angle1.angleType == Angle::AngleType::UNKNOWN || angle2.angleType == Angle::AngleType::UNKNOWN);
}

bool operator!=(const Angle& angle1, const Angle& angle2) {
	return !(angle1 == angle2);
}

bool operator<(const Angle& angle1, const Angle& angle2) {
	if(angle1.vertexId == angle2.vertexId && angle1.pointsOnArms == angle2.pointsOnArms) {
		return angle1.angleType < angle2.angleType;
	}
	else if (angle1.vertexId == angle2.vertexId) {
		return angle1.pointsOnArms < angle2.pointsOnArms;
	}
	else {
		return angle1.vertexId < angle2.vertexId;
	}
}

bool operator>(const Angle& angle1, const Angle& angle2) {
	return angle2 < angle1;
}

bool operator<=(const Angle& angle1, const Angle& angle2) {
	return angle1 == angle2 || angle1 < angle2;
}

bool operator>=(const Angle& angle1, const Angle& angle2) {
	return angle1 == angle2 || angle1 > angle2;
}

std::ostream& operator<<(std::ostream& stream, const Angle& angle) {
	stream << "<)" << angle.pointsOnArms.getFirst() << "-" << angle.vertexId << "-" << angle.pointsOnArms.getSecond();
	switch (angle.angleType)
	{
	case Angle::AngleType::CONVEX:
		stream << " is convex";
		break;
	case Angle::AngleType::CONCAVE:
		stream << " is concave";
		break;
	default:
		stream << " is unknown";
		break;
	}

	return stream;
}