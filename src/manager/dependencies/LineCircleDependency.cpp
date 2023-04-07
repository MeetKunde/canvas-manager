#include "./../../../inc/manager/dependencies/LineCircleDependency.h"

LineCircleDependency::LineCircleDependency(unsigned int line, unsigned int circle) :
lineId(line), circleId(circle) { }

LineCircleDependency::LineCircleDependency(const LineCircleDependency& lineCircleDependency) :
lineId(lineCircleDependency.lineId), circleId(lineCircleDependency.circleId) { }

LineCircleDependency& LineCircleDependency::operator=(const LineCircleDependency& lineCircleDependecy) {
    lineId = lineCircleDependecy.lineId;
    circleId = lineCircleDependecy.circleId;

    return *this;
}

bool operator== (const LineCircleDependency& lcd1, const LineCircleDependency& lcd2) {
    return lcd1.lineId == lcd2.lineId && lcd1.circleId == lcd2.circleId;
}

bool operator!= (const LineCircleDependency& lcd1, const LineCircleDependency& lcd2) {
    return !(lcd1 == lcd2);
}

std::ostream& operator<< (std::ostream& stream, const LineCircleDependency& lineCircleDependency) {
    stream << "line " << lineCircleDependency.getLineId() << " and circle " << lineCircleDependency.getCircleId();

    return stream;
}