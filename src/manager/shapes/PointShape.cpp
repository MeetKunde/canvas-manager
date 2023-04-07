#include "./../../../inc/manager/shapes/PointShape.h"

PointShape::PointShape(double x, double y) 
: PointEquation(x, y) { }

PointShape::PointShape(PointEquation pointEquation)
: PointEquation(pointEquation) { }

PointShape::PointShape(const PointShape& point)
: PointEquation(point) { }

PointShape& PointShape::operator=(const PointShape& point) {
  PointEquation::operator= (point);
  
  return *this;
}


