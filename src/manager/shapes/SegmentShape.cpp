#include "./../../../inc/manager/shapes/SegmentShape.h"

SegmentShape::SegmentShape(PointShape& point1, unsigned int point1Id, PointShape& point2, unsigned int point2Id) noexcept(false)
: LineEquation(point1, point2), endIds{point1Id, point2Id}, ends{PointShape(point1), PointShape(point2)} {
	if (getType() == LineType::VERTICAL) {
		if (point1.getY() < point2.getY()) {
			//endIds[0] = point1Id;
			//endIds[1] = point2Id;

			//ends[0] = point1;
			//ends[1] = point2;
		}
		else {
			endIds[0] = point2Id;
			endIds[1] = point1Id;

			ends[0] = PointShape(point2);
			ends[1] = PointShape(point1);
		}
	}
	else {
		if (point1.getX() < point2.getX()) {
			//endIds[0] = point1Id;
			//endIds[1] = point2Id;

			//ends[0] = point1;
			//ends[1] = point2;
		}
		else {
			endIds[0] = point2Id;
			endIds[1] = point1Id;

			ends[0] = point2;
			ends[1] = point1;
		}
	}
}

SegmentShape::SegmentShape(const SegmentShape& segment)
: LineEquation(segment), endIds{segment.getEnd1Id(), segment.getEnd2Id()}, ends{segment.getEnd1(), segment.getEnd2()} {}

SegmentShape& SegmentShape::operator=(const SegmentShape& segment) {
	LineEquation::operator=(segment);

	endIds[0] = segment.endIds[0];
	endIds[1] = segment.endIds[1];

	ends[0] = segment.ends[0];
	ends[1] = segment.ends[1];

	return *this;
}

bool SegmentShape::liesOn(const PointShape& point) {
	if (point == ends[0] || point == ends[1]) {
		return false;
	}

	if (getType() == LineType::VERTICAL) {
		if (fabs(point.getX() - getb()) > Constans::BIG_EPSILON) {
			return false;
		}

		if (point.getY() < ends[0].getY() || point.getY() > ends[1].getY()) {
			return false;
		}

		return true;
	}
	else if (getType() == LineType::HORIZONTAL) {
		if (fabs(point.getY() - getb()) > Constans::BIG_EPSILON) {
			return false;
		}

		if (point.getX() < ends[0].getX() || point.getX() > ends[1].getX()) {
			return false;
		}

		return true;
	}
	else {
		if (geta() > 0.0) {
			if (point.getY() < ends[0].getY() || point.getY() > ends[1].getY()) {
				return false;
			}

		}
		else {
			if (point.getY() < ends[1].getY() || point.getY() > ends[0].getY()) {
				return false;
			}
		}
		
		if (point.getX() < ends[0].getX() || point.getX() > ends[1].getX()) {
			return false;
		}

		return LineEquation::liesOn(point);
	}
}

bool operator==(const SegmentShape& segment1, const SegmentShape& segment2) {
	return segment1.endIds[0] == segment2.endIds[0] && segment1.endIds[1] == segment2.endIds[1];
}

bool operator!=(const SegmentShape& segment1, const SegmentShape& segment2) {
	return !(segment1 == segment2);
}

std::ostream& operator<<(std::ostream& stream, const SegmentShape& segment) {
	stream << segment.getA() << "x + " << segment.getB() << "y + " << segment.getC() << " = 0.0;  ends = {" << segment.getEnd1() << ", " << segment.getEnd2() << "}";

	return stream;
}