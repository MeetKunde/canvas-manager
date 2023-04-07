#include "./../../../inc/manager/dependencies/PolygonTypeDependency.h"

PolygonTypeDependency::PolygonTypeDependency(std::vector<unsigned int> polygon, PolygonType type)
: polygonVertices(polygon), polygonType(type) { }

PolygonTypeDependency::PolygonTypeDependency(const PolygonTypeDependency& polygonTypeDependency)
: polygonVertices(polygonTypeDependency.polygonVertices), polygonType(polygonTypeDependency.polygonType) { }

PolygonTypeDependency& PolygonTypeDependency::operator=(const PolygonTypeDependency& polygonTypeDependency) {
    polygonVertices = polygonTypeDependency.polygonVertices;
    polygonType = polygonTypeDependency.polygonType;

    return *this;
}

bool operator== (const PolygonTypeDependency& ptd1, const PolygonTypeDependency& ptd2) {
    if(ptd1.polygonType != ptd2.polygonType) {
        return false;
    }
    else if(ptd1.polygonVertices.size() != ptd2.polygonVertices.size()) {
        return false;
    }
    else {
        for(int i = 0; i < ptd1.polygonVertices.size(); i++) {
            if(ptd1.polygonVertices[i] != ptd2.polygonVertices[i]) {
                return false;
            }
        }
    }

    return true;
}

bool operator!= (const PolygonTypeDependency& ptd1, const PolygonTypeDependency& ptd2) {
    return !(ptd1 == ptd2);
}

std::ostream& operator<< (std::ostream& stream, const PolygonTypeDependency& polygonTypeDependency) {
    stream << "polygon {";

    std::vector<unsigned int>::const_iterator it;
    for(it = polygonTypeDependency.polygonVertices.begin(); it != polygonTypeDependency.polygonVertices.end(); it++) {
        stream << (*it) << ", ";
    }

    stream << "} is type ";

    switch(polygonTypeDependency.getType()) {
    case PolygonTypeDependency::PolygonType::RECTANGLE:
        stream << "RECTANGLE";
        break;
    case PolygonTypeDependency::PolygonType::SQUARE:
        stream << "SQUARE";
        break;
    default:
        break;
    }

    return stream;
}