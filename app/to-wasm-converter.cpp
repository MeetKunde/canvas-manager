#include <emscripten/bind.h>

#include "./../inc/math/equations/PointEquation.h"
#include "./../inc/math/equations/LineEquation.h"
#include "./../inc/math/equations/CircleEquation.h"
#include "./../inc/math/Constans.h"
#include "./../inc/math/SystemOf2LinearEquations.h"
#include "./../inc/math/QuadraticEquation.h"
#include "./../inc/math/Distance.h"
#include "./../inc/figures-creating/Lines.h"
#include "./../inc/figures-creating/Circles.h"
#include "./../inc/figures-creating/IntersectionPoints.h"
#include "./../inc/manager/shapes/PointShape.h"
#include "./../inc/manager/shapes/SegmentShape.h"
#include "./../inc/manager/shapes/CircleShape.h"
#include "./../inc/manager/dependencies/Angle.h"
#include "./../inc/manager/dependencies/OrderedPair.h"
#include "./../inc/manager/dependencies/LinesDependency.h"
#include "./../inc/manager/dependencies/SegmentsDependency.h"
#include "./../inc/manager/dependencies/AnglesDependency.h"
#include "./../inc/manager/dependencies/SegmentLength.h"
#include "./../inc/manager/dependencies/AngleValue.h"
#include "./../inc/manager/dependencies/CirclesDependency.h"
#include "./../inc/manager/dependencies/LineAngleDependency.h"
#include "./../inc/manager/dependencies/LineCircleDependency.h"
#include "./../inc/manager/dependencies/LineSegmentDependency.h"
#include "./../inc/manager/dependencies/PolygonCircleDependency.h"
#include "./../inc/manager/dependencies/PolygonTypeDependency.h"
#include "./../inc/manager/dependencies/SegmentArmsDependency.h"
#include "./../inc/manager/ShapesManager.h"
#include "./../inc/manager/DependenciesManager.h"
#include "./../inc/manager/Manager.h"
#include "./../inc/json.h"

#include <vector>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(canvasManager) {
    register_vector<unsigned int>("vectorOfUnsignedInts");

    enum_<Manager::ShapeToCreate>("ShapeToCreate")
        .value("NONE", Manager::ShapeToCreate::NONE)
        .value("POINT", Manager::ShapeToCreate::POINT)
        .value("SEGMENT", Manager::ShapeToCreate::SEGMENT)
        .value("LINE", Manager::ShapeToCreate::LINE)
        .value("SEMILINE", Manager::ShapeToCreate::SEMILINE)
        .value("CIRCLE", Manager::ShapeToCreate::CIRCLE)
        .value("COMPLEX_SHAPE", Manager::ShapeToCreate::COMPLEX_SHAPE);

    enum_<Angle::AngleType>("AngleType")
        .value("UNKNOWN", Angle::AngleType::UNKNOWN)
        .value("CONVEX", Angle::AngleType::CONVEX)
        .value("CONCAVE", Angle::AngleType::CONCAVE);

    enum_<PolygonTypeDependency::PolygonType>("PolygonType")
        .value("UNKNOWN", PolygonTypeDependency::PolygonType::UNKNOWN)
        .value("ISOSCELES_ACUTE_TRIANGLE", PolygonTypeDependency::PolygonType::ISOSCELES_ACUTE_TRIANGLE)
        .value("EQUILATERAL_TRIANGLE", PolygonTypeDependency::PolygonType::EQUILATERAL_TRIANGLE)
        .value("SCALENE_RIGHT_TRIANGLE", PolygonTypeDependency::PolygonType::SCALENE_RIGHT_TRIANGLE)
        .value("ISOSCELES_RIGHT_TRIANGLE", PolygonTypeDependency::PolygonType::ISOSCELES_RIGHT_TRIANGLE)
        .value("OBTUSE_ISOSCELES_TRIANGLE", PolygonTypeDependency::PolygonType::OBTUSE_ISOSCELES_TRIANGLE)
        .value("SQUARE", PolygonTypeDependency::PolygonType::SQUARE)
        .value("RECTANGLE", PolygonTypeDependency::PolygonType::RECTANGLE)
        .value("REGULAR_POLYGON", PolygonTypeDependency::PolygonType::REGULAR_POLYGON)
        .value("PARALLELOGRAM", PolygonTypeDependency::PolygonType::PARALLELOGRAM)
        .value("KITE", PolygonTypeDependency::PolygonType::KITE)
        .value("RHOMBUS", PolygonTypeDependency::PolygonType::RHOMBUS)
        .value("SCALENE_TRAPEZOID", PolygonTypeDependency::PolygonType::SCALENE_TRAPEZOID)
        .value("ISOSCELES_TRAPEZOID", PolygonTypeDependency::PolygonType::ISOSCELES_TRAPEZOID)
        .value("RIGHT_TRAPEZOID", PolygonTypeDependency::PolygonType::RIGHT_TRAPEZOID);
        
    class_<Manager>("CanvasManager")
        .constructor<double, double, double, int, int, int, int, int, int, int>()

        .function("clearCanvas", &Manager::clearCanvas)

        .function("setCurrentlyCreatedShape", &Manager::setCurrentlyCreatedShape)

        .function("clickedOnCanvas", &Manager::clickedOnCanvas)
        .function("clickedOnPoint", &Manager::clickedOnPoint)
        .function("clickedOnSegment", &Manager::clickedOnSegment)
        .function("clickedOnCircle", &Manager::clickedOnCircle)

        .function("setPerpendicularityDependency", &Manager::setPerpendicularityDependency)
        .function("setPerpendicularityDependencyBaseOnPoints", &Manager::setPerpendicularityDependencyBaseOnPoints)
        .function("createPerpendicularLineToLine", &Manager::createPerpendicularLineToLine)
        .function("setParallelismDependency", &Manager::setParallelismDependency)
        .function("setParallelismDependencyBaseOnPoints", &Manager::setParallelismDependencyBaseOnPoints)
        .function("createParallelLineToLine", &Manager::createParallelLineToLine)
        .function("setEqualSegmentsDependencyWithEnds", &Manager::setEqualSegmentsDependencyWithEnds)
        .function("setEqualSegmentsDependnecyWithIds", &Manager::setEqualSegmentsDependnecyWithIds)
        .function("setEqualSegmentsDependencyWithMix", &Manager::setEqualSegmentsDependencyWithMix)
        .function("setEqualAnglesDependency", &Manager::setEqualAnglesDependency)
        .function("setLengthValue", &Manager::setLengthValue)
        .function("setSegmentLengthValue", &Manager::setSegmentLengthValue)
        .function("setAngleValue", &Manager::setAngleValue)

        .function("divideSegmentWithId", &Manager::divideSegmentWithId)
        .function("divideSegmentWithEnds", &Manager::divideSegmentWithEnds)
        .function("divideAngle", &Manager::divideAngle)
        .function("createSegmentMidPerpendicularWithId", &Manager::createSegmentMidPerpendicularWithId)
        .function("createSegmentMidPerpendicularWithEnds", &Manager::createSegmentMidPerpendicularWithEnds)
        .function("createTangentLine", &Manager::createTangentLine)
        .function("createTangentCircleToLine", &Manager::createTangentCircleToLine)
        .function("createTangentCircleToCircle", &Manager::createTangentCircleToCircle)
        .function("createAltitudeWithBaseId", &Manager::createAltitudeWithBaseId)
        .function("createAltitudeWithBaseEnds", &Manager::createAltitudeWithBaseEnds)
        .function("createMedianWithBaseId", &Manager::createMedianWithBaseId)
        .function("createMedianwithBaseEnds", &Manager::createMedianwithBaseEnds)
        .function("createMidSegmentWithArmIds", &Manager::createMidSegmentWithArmIds)
        .function("createMidSegmentWithArmEnds", &Manager::createMidSegmentWithArmEnds)
        .function("createMidSegmentWithMix", &Manager::createMidSegmentWithMix)
        .function("createBisectorLine", &Manager::createBisectorLine)
        .function("createInscribedCircle", &Manager::createInscribedCircle)
        .function("createCircumscribedCircle", &Manager::createCircumscribedCircle)
        .function("createEscribedCircleWithSideId", &Manager::createEscribedCircleWithSideId)
        .function("createEscribedCircleWithSideEnds", &Manager::createEscribedCircleWithSideEnds)
        .function("setPolygonType", &Manager::setPolygonType)
        .function("setPerpendicularLines", &Manager::setPerpendicularLines)
        .function("setParallelLines", &Manager::setParallelLines)
        .function("setEscribedCircle", &Manager::setEscribedCircle)
        .function("setInscribedCircle", &Manager::setInscribedCircle)
        .function("setCircumscribedCircle", &Manager::setCircumscribedCircle)
        .function("setTangentLineToCircle", &Manager::setTangentLineToCircle)
        .function("setTangentCircles", &Manager::setTangentCircles)
        .function("setAltitude", &Manager::setAltitude)
        .function("setMedian", &Manager::setMedian)
        .function("setMidSegment", &Manager::setMidSegment)
        .function("getJsonData", &Manager::getJsonData, allow_raw_pointers());
}
