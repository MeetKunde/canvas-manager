#ifndef POLYGON_TYPE_DEPENDENCY_H
#define POLYGON_TYPE_DEPENDENCY_H

#include <vector>
#include <ostream>

class PolygonTypeDependency {
public:
    enum class PolygonType {
        UNKNOWN,
        ISOSCELES_ACUTE_TRIANGLE,
        EQUILATERAL_TRIANGLE,
        SCALENE_RIGHT_TRIANGLE,
        ISOSCELES_RIGHT_TRIANGLE,
        OBTUSE_ISOSCELES_TRIANGLE,
        SQUARE,
        RECTANGLE,
        REGULAR_POLYGON,
        PARALLELOGRAM,
        KITE,
        RHOMBUS,
        SCALENE_TRAPEZOID,
        ISOSCELES_TRAPEZOID,
        RIGHT_TRAPEZOID
    };

private:
    std::vector<unsigned int> polygonVertices;
    PolygonType polygonType;

public:
    PolygonTypeDependency(std::vector<unsigned int> polygon, PolygonType type);
    PolygonTypeDependency(const PolygonTypeDependency& polygonTypeDependency);

    PolygonTypeDependency& operator=(const PolygonTypeDependency& polygonTypeDependency);

    const std::vector<unsigned int>& getPolygonVerticesIds() const { return polygonVertices;}
    PolygonType getType() const { return polygonType; }

    friend bool operator== (const PolygonTypeDependency& ptd1, const PolygonTypeDependency& ptd2);
    friend bool operator!= (const PolygonTypeDependency& ptd1, const PolygonTypeDependency& ptd2);

    friend std::ostream& operator<< (std::ostream& stream, const PolygonTypeDependency& polygonTypeDependency);
};

#endif /* POLYGON_TYPE_DEPENDENCY_H */