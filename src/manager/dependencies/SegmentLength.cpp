#include "./../../../inc/manager/dependencies/SegmentLength.h"

SegmentLength::SegmentLength(int end1Id, int end2Id, std::string value)
: segment(OrderedPair(end1Id, end2Id)), value(value) { }

SegmentLength::SegmentLength(const SegmentLength& segmentLenght)
: segment(OrderedPair(segmentLenght.segment)), value(segmentLenght.value) {}

SegmentLength& SegmentLength::operator=(const SegmentLength& segmentLenght) {
	segment = OrderedPair(segmentLenght.segment);
	value = segmentLenght.value;

	return *this;
}

bool operator== (const SegmentLength& sl1, const SegmentLength& sl2) {
	return sl1.segment == sl2.segment && sl1.value == sl2.value;
}

bool operator!= (const SegmentLength& sl1, const SegmentLength& sl2) {
	return !(sl1 == sl2);
}

std::ostream& operator<< (std::ostream& stream, const SegmentLength& segmentLength) {
	stream << "length of segment " << segmentLength.getSegment() << " = " << segmentLength.getValue();

	return stream;
}