#ifndef POLYGON_CIRCLE_DEPENDENCY_H
#define POLYGON_CIRCLE_DEPENDENCY_H

#include <vector>
#include <ostream>

class PolygonCircleDependency {
private:
    std::vector<unsigned int> polygonVertices;
    unsigned int circleId;

public:
    PolygonCircleDependency(std::vector<unsigned int> polygon, unsigned int circle);
    PolygonCircleDependency(const PolygonCircleDependency& polygonCircleDependency);

    PolygonCircleDependency& operator=(const PolygonCircleDependency& polygonCircleDependency);

    const std::vector<unsigned int>& getPolygonVerticesIds() const { return polygonVertices; }
    unsigned int getCircleId() const { return circleId; }

    friend bool operator== (const PolygonCircleDependency& pcd1, const PolygonCircleDependency& pcd2);
    friend bool operator!= (const PolygonCircleDependency& pcd1, const PolygonCircleDependency& pcd2);

    friend std::ostream& operator<< (std::ostream& stream, const PolygonCircleDependency& polygonCircleDependency);
};

#endif /* POLYGON_CIRCLE_DEPENDENCY_H */