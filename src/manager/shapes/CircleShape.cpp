#include "./../../../inc/manager/shapes/CircleShape.h"

CircleShape::CircleShape(PointEquation& centerPoint, unsigned int centerPointId, PointEquation& pointOnCircle, unsigned int pointOnCircleId)
: CircleEquation(centerPoint, Distance::ofPoints(centerPoint, pointOnCircle)) {
	includedPointIds = std::set<unsigned int>();
	
	centerId = centerPointId;
	includedPointIds.insert(pointOnCircleId);
}

CircleShape::CircleShape(const CircleShape& circle)
: CircleEquation(circle), centerId(circle.centerId), includedPointIds(circle.includedPointIds) {}

CircleShape& CircleShape::operator=(const CircleShape& circle) {
	CircleEquation::operator=(circle);

	centerId = circle.centerId;
	includedPointIds = circle.includedPointIds;

	return *this;

}