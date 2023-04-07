#include "./../../../inc/manager/dependencies/PolygonCircleDependency.h"

PolygonCircleDependency::PolygonCircleDependency(std::vector<unsigned int> polygon, unsigned int circle)
: polygonVertices(polygon), circleId(circle) { }

PolygonCircleDependency::PolygonCircleDependency(const PolygonCircleDependency& polygonCircleDependency) 
: polygonVertices(polygonCircleDependency.polygonVertices), circleId(polygonCircleDependency.circleId) { }

PolygonCircleDependency& PolygonCircleDependency::operator=(const PolygonCircleDependency& polygonCircleDependency) {
    polygonVertices = polygonCircleDependency.polygonVertices;
    circleId = polygonCircleDependency.circleId;

    return *this;
}

bool operator== (const PolygonCircleDependency& pcd1, const PolygonCircleDependency& pcd2) {
    if(pcd1.circleId != pcd2.circleId) {
        return false;
    }
    else if(pcd1.polygonVertices.size() != pcd2.polygonVertices.size()) {
        return false;
    }
    else {
        for(int i = 0; i < pcd1.polygonVertices.size(); i++) {
            if(pcd1.polygonVertices[i] != pcd2.polygonVertices[i]) {
                return false;
            }
        }
    }

    return true;
}

bool operator!= (const PolygonCircleDependency& pcd1, const PolygonCircleDependency& pcd2) {
    return !(pcd1 == pcd2);
}

std::ostream& operator<< (std::ostream& stream, const PolygonCircleDependency& polygonCircleDependency) {
    stream << "polygon {";

    std::vector<unsigned int>::const_iterator it;
    for(it = polygonCircleDependency.polygonVertices.begin(); it != polygonCircleDependency.polygonVertices.end(); it++) {
        stream << (*it) << ", ";
    }

    stream << "} and circle " << polygonCircleDependency.getCircleId();

    return stream;
}