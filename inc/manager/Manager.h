#ifndef MANAGER_H
#define MANAGER_H

#include "ShapesManager.h"
#include "DependenciesManager.h"
#include "./../figures-creating/IntersectionPoints.h"
#include "./../figures-creating/Lines.h"
#include "./../figures-creating/Circles.h"

#include "./../json.h"

#include <vector>
#include <map>
#include <algorithm>
#include <math.h>

using json = nlohmann::json;

//#define CONVERTING_TO_WEBASSEMBLY

class Manager {
public:
	/**
	 * @brief Class implementing a custom exception used in Manager class methods 
	 * when an attempt is made to call a function with invalid or meaningless parameters
	 */
	class InvalidOrMeaninglessArgumentsException : public virtual std::invalid_argument {
	public:
		/**
		 * @brief Constructor of a new InvalidOrMeaninglessArgumentsException object
		 */
		InvalidOrMeaninglessArgumentsException() : std::invalid_argument("Given parameters are invalid or meaningless") { }
	};

	enum class ShapeToCreate {
		NONE,
		POINT,
		SEGMENT,
		LINE,
		SEMILINE,
		CIRCLE,
		COMPLEX_SHAPE
	};

private:
	double canvasWidth;
	double canvasHeight;
	double offset;

	std::vector<unsigned int> buffer;
	ShapeToCreate currentlyCreatedShape;

	unsigned int lineEquationsCounter;
	std::map<std::string, unsigned int> lineEquationsIds;
	std::map<unsigned int, LineEquation> lineEquations;
	std::map<unsigned int, std::vector<unsigned int>> pointsOnLines;
	std::map<unsigned int, std::vector<unsigned int>> segmentsOnLines;

	ShapesManager shapes;
	DependenciesManager dependencies;

	std::set<unsigned int> idsNonConsidered;

	void (*drawPointFunction)(int, double, double);
	void (*drawSegmentFunction)(int, double, double, double, double);
	void (*drawCircleFunction)(int, double, double, double);
	void (*deleteShapeFunction)(int);
	void (*setPromptingShapeStartPointFunction)(int, double, double);
	void (*processingCompletedAlertFunction)();
	void (*alertFunction)(int, const char*);

public:

#ifdef CONVERTING_TO_WEBASSEMBLY
	Manager(double width, double height, double offset, 
		int drawPointFunctionPointer, 
		int drawSegmentFunctionPointer, 
		int drawCircleFunctionPointer, 
		int deleteShapeFunctionPointer, 
		int setPromptingShapeStartPointFunctionPointer, 
		int processingCompletedAlertFunctionPointer, 
		int alertFunctionPointer);
#else
	Manager(double width, double height, double offset,
		void (*drawPointFunction)(int, double, double),
		void (*drawSegmentFunction)(int, double, double, double, double),
		void (*drawCircleFunction)(int, double, double, double),
		void (*deleteShapeFunction)(int),
		void (*setPromptingShapeStartPointFunction)(int, double, double),
		void (*processingCompletedAlertFunction)(),
		void (*alertFunction)(int, const char*));
#endif // CONVERTING_TO_WEBASSEMBLY

	void clearCanvas();

	void setCurrentlyCreatedShape(Manager::ShapeToCreate shape);

	unsigned int clickedOnCanvas(double x, double y);
	unsigned int clickedOnPoint(unsigned int id);
	unsigned int clickedOnSegment(unsigned int id, double x, double y);
	unsigned int clickedOnCircle(unsigned int id, double x, double y);

	void displayPointsAndSegmentsOnLines();

	void setPerpendicularityDependency(unsigned int line1Id, unsigned int line2Id);
	void setPerpendicularityDependencyBaseOnPoints(unsigned int line1Point1Id, unsigned int line1Point2Id, unsigned int line2Point1Id, unsigned int line2Point2Id);
	void createPerpendicularLineToLine(unsigned int lineId, unsigned int pointId);
	void setParallelismDependency(unsigned int line1Id, unsigned int line2Id);
	void setParallelismDependencyBaseOnPoints(unsigned int line1Point1Id, unsigned int line1Point2Id, unsigned int line2Point1Id, unsigned int line2Point2Id);
	void createParallelLineToLine(int lineId, int pointId);
	void setEqualSegmentsDependencyWithEnds(unsigned int segment1End1Id, unsigned int segment1End2Id, unsigned int segment2End1Id, unsigned int segment2End2Id);
	void setEqualSegmentsDependnecyWithIds(unsigned int segment1Id, unsigned int segment2Id);
	void setEqualSegmentsDependencyWithMix(unsigned int segment1Id, unsigned int segment2End1Id, unsigned int segment2End2Id);
	void setEqualAnglesDependency(unsigned int angle1Point1Id, unsigned int angle1VertexId, unsigned int angle1Point2Id, unsigned int angle2Point1Id, unsigned int angle2VertexId, unsigned int angle2Point2Id);
	void setLengthValue(unsigned int end1Id, unsigned int end2Id, std::string value);
	void setSegmentLengthValue(unsigned int segmentId, std::string value);
	void setAngleValue(unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, Angle::AngleType type, std::string value);

	void divideSegmentWithId(unsigned int segmentId, unsigned int n);
	void divideSegmentWithEnds(unsigned int end1Id, unsigned int end2Id, unsigned int n);
	void divideAngle(unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, bool ofConvexAngle, unsigned int n);
	void createSegmentMidPerpendicularWithId(unsigned int segmentId);
	void createSegmentMidPerpendicularWithEnds(unsigned int end1Id, unsigned int end2Id);
	void createTangentLine(unsigned int pointId, unsigned int circleId);
	void createTangentCircleToLine(unsigned int centerId, unsigned int segmentId);
	void createTangentCircleToCircle(unsigned int circleId, unsigned int newCircleCenterId, bool externally);
	void createAltitudeWithBaseId(unsigned int baseId, unsigned int vertexId);
	void createAltitudeWithBaseEnds(unsigned int end1Id, unsigned int end2Id, unsigned int vertexId);
	void createMedianWithBaseId(unsigned int baseId, unsigned int vertexId);
	void createMedianwithBaseEnds(unsigned int baseEnd1Id, unsigned int baseEnd2Id, unsigned int vertexId);
	void createMidSegmentWithArmIds(unsigned int arm1Id, unsigned int arm2Id);
	void createMidSegmentWithArmEnds(unsigned int arm1End1, unsigned int arm1End2, unsigned int arm2End1, unsigned int arm2End2);
	void createMidSegmentWithMix(unsigned int arm1Id, unsigned int arm2End1Id, unsigned int arm2End2Id);
	void createBisectorLine(unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, bool ofConvexAngle);
	void createInscribedCircle(std::vector<unsigned int> verticesIds);
	void createCircumscribedCircle(std::vector<unsigned int> verticesIds);
	void createEscribedCircleWithSideId(unsigned int sideId, unsigned int pointId);
	void createEscribedCircleWithSideEnds(unsigned int end1Id, unsigned int end2Id, unsigned int pointId);
	void setPolygonType(std::vector<unsigned int> polygon, PolygonTypeDependency::PolygonType type);

	void setPerpendicularLines(unsigned int line1, unsigned int line2);
	void setParallelLines(unsigned int line1, unsigned int line2);
	void setEscribedCircle(unsigned int circleId, std::vector<unsigned int> polygon);
    void setInscribedCircle(unsigned int circleId, std::vector<unsigned int> polygon);
    void setCircumscribedCircle(unsigned int circleId, std::vector<unsigned int> polygon);
    void setTangentLineToCircle(unsigned int lineId, unsigned int circleId);
    void setTangentCircles(unsigned int circle1Id, unsigned int circle2Id);
    void setAltitude(unsigned int end1Id, unsigned int end2Id, unsigned int lineId);
    void setMedian(unsigned int s1End1Id, unsigned int s1End2Id, unsigned int s2End1Id, unsigned int s2End2Id);
    void setMidSegment(unsigned int a1End1Id, unsigned int a1End2Id, unsigned int a2End1Id, unsigned int a2End2Id, unsigned int sEnd1, unsigned int sEnd2);

	std::string getJsonData();

private:
	void processFullBuffer();

	unsigned int createPoint(double x, double y, bool findIntersectionPoints);
	unsigned int createSimpleSegment(PointShape& end1, unsigned int end1Id, PointShape& end2, unsigned int end2Id);
	unsigned int createSegment(unsigned int end1Id, unsigned int end2Id, bool findIntersectionPoints);
	unsigned int createLine(unsigned int point1Id, unsigned int point2Id, bool findIntersectionPoints);
	unsigned int createSemiLine(unsigned int startPointId, unsigned int includedPointId, bool findIntersectionPoints);
	unsigned int createCircle(unsigned int centerPointId, unsigned int pointOnCircleId, bool findIntersectionPoints);

	std::vector<unsigned int> clickOnSegment(unsigned int id, double x, double y) noexcept(false);
	unsigned int clickOnCircle(unsigned int id, double x, double y);

	void findIntersectionPointsWithLine(unsigned int lineId, std::vector<unsigned int> segmentIds);
	void findIntersectionPointsWithCircle(unsigned int circleId);

	unsigned int createPerpendicularLine(LineEquation& lineEquation, unsigned int pointId);
	unsigned int createParallelLine(LineEquation& lineEquation, unsigned int pointId);

	std::vector<unsigned int> divideSegmentId(unsigned int segmentId, unsigned int n);
	std::vector<unsigned int> divideSegmentEnds(unsigned int end1Id, unsigned int end2Id, unsigned int n);

	std::vector<std::pair<unsigned int, PointEquation>> sortVerticesClockwise(std::vector<std::pair<unsigned int, PointEquation>>& vertices);

	void errorNotForeseen();
};

#endif /* MANAGER_H */