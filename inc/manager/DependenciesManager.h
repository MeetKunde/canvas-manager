#ifndef DEPENDENCIES_MANAGER_H
#define DEPENDENCIES_MANAGER_H

#include "./dependencies/LinesDependency.h"
#include "./dependencies/SegmentsDependency.h"
#include "./dependencies/AnglesDependency.h"
#include "./dependencies/LineCircleDependency.h"
#include "./dependencies/LineAngleDependency.h"
#include "./dependencies/LineSegmentDependency.h"
#include "./dependencies/PolygonCircleDependency.h"
#include "./dependencies/PolygonTypeDependency.h"
#include "./dependencies/SegmentArmsDependency.h"
#include "./dependencies/CirclesDependency.h"
#include "./dependencies/SegmentLength.h"
#include "./dependencies/AngleValue.h"

#include "./../json.h"

#include <vector>
#include <string>

using json = nlohmann::json;

/**
 * @brief Class managing dependencies
 */
class DependenciesManager {
private:
	std::vector<LinesDependency> perpendicularLines;
	std::vector<LinesDependency> parallelLines;
	std::vector<SegmentsDependency> equalSegments;
	std::vector<AnglesDependency> equalAngles;
	std::vector<SegmentLength> segmentLengths;
	std::vector<AngleValue> angleValues;
	std::vector<LineCircleDependency> tangentLines;
	std::vector<LineAngleDependency> bisectorLines;
	std::vector<LineSegmentDependency> midPerpendicularLines;
	std::vector<PolygonCircleDependency> escribedCircles, inscribedCircles, circumscribedCircles;
	std::vector<PolygonTypeDependency> polygonsTypes;
	std::vector<SegmentsDependency> medians;
	std::vector<LineSegmentDependency> altitudes;
	std::vector<SegmentArmsDependency> midSegments;
	std::vector<CirclesDependency> tangentCircles;

public:
	/**
	 * @brief Constructor of a new Dependencies Manager object
	 */
	DependenciesManager();

	/**
	 * @brief Constructor of a new DependenciesManager object
	 * 
	 * @param dependenciesManager other DependenciesManager object
	 */
	DependenciesManager(const DependenciesManager& dependenciesManager);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param dependenciesManager object to be assigned 
	 * @return new DependenciesManager object
	 */
    DependenciesManager& operator=(const DependenciesManager& dependenciesManager);

	/**
	 * @brief Adding new perpendicular lines dependency
	 * 
	 * @param line1Id ID of first line object
	 * @param line2Id ID of second line object
	 * @param reason dependency reason
	 */
	inline void addPerpendicularLines(unsigned int line1Id, unsigned int line2Id) { perpendicularLines.push_back(LinesDependency(line1Id, line2Id)); }
	
	/**
	 * @brief Getting all perpendicular lines dependencies as written to JSON object as JSON objects
	 * 
	 * @return JSON object with JSON objects representing perpendicular lines dependencies
	 */
	json getPerpendicularLinesAsJsonObjects() const;

	/**
	 * @brief Adding new parallel lines dependency
	 * 
	 * @param line1Id ID of first line object
	 * @param line2Id ID of second line object
	 * @param reason dependency reason
	 */
	inline void addParallelLines(unsigned int line1Id, unsigned int line2Id) { parallelLines.push_back(LinesDependency(line1Id, line2Id)); }
	
	/**
	 * @brief Getting all parallel lines dependencies as written to JSON object as JSON objects
	 * 
	 * @return JSON object with JSON objects representing parallel lines dependencies
	 */
	json getParallelLinesAsJsonObjects() const;

	/**
	 * @brief Adding new equal segments dependency
	 * 
	 * @param segment1End1Id ID of first end point of first segment
	 * @param segment1End2Id ID of second end point of first segment
	 * @param segment2End1Id ID of first end point of second segment
	 * @param segment2End2Id ID of second end point of second segment
	 * @param reason dependency reason
	 */
	inline void addEqualSegments(unsigned int segment1End1Id, unsigned int segment1End2Id, unsigned int segment2End1Id, unsigned int segment2End2Id) { equalSegments.push_back(SegmentsDependency(segment1End1Id, segment1End2Id, segment2End1Id, segment2End2Id)); }
	
	/**
	 * @brief Getting all equal segments dependencies as written to JSON object as JSON objects
	 * 
	 * @return JSON object with JSON objects representing equal segments dependencies
	 */
	json getEqualSegmentsAsJsonObjects() const;

	/**
	 * @brief Adding new equal angles dependency
	 * 
	 * @param angle1Point1Id ID of first point on first angle
	 * @param angle1VertexId ID of first angle vertex point
	 * @param angle1Point2Id ID of second point on first angle
	 * @param angle1Type first angle type
	 * @param angle2Point1Id ID of first point on second angle
	 * @param angle2VertexId ID of second angle vertex point
	 * @param angle2Point2Id ID of second point on second angle
	 * @param angle2Type second angle type
	 * @param reason dependency reason
	 */
	inline void addEqualAngles(unsigned int angle1Point1Id, unsigned int angle1VertexId, unsigned int angle1Point2Id, Angle::AngleType angle1Type, unsigned int angle2Point1Id, unsigned int angle2VertexId, unsigned int angle2Point2Id, Angle::AngleType angle2Type) { equalAngles.push_back(AnglesDependency(angle1Point1Id, angle1VertexId, angle1Point2Id, angle1Type, angle2Point1Id, angle2VertexId, angle2Point2Id, angle2Type)); }
	
	/**
	 * @brief Getting all equal angles dependencies as written to JSON object as JSON objects
	 * 
	 * @return JSON object with JSON objects representing equal angles dependencies
	 */
	json getEqualAnglesAsJsonObjects() const;

	/**
	 * @brief Adding new segment lenght dependency
	 * 
	 * @param end1Id ID of first end point
	 * @param end2Id ID of second end point
	 * @param value segment length to set
	 * @param reason dependency reason 
	 */
	inline void setSegmentLength(unsigned int end1Id, unsigned int end2Id, std::string value) { segmentLengths.push_back(SegmentLength(end1Id, end2Id, value)); }
	
	/**
	 * @brief Getting all segment length dependencies as written to JSON object as JSON objects
	 * 
	 * @return JSON object with JSON objects representing segment length dependencies
	 */
	json getSegmentLenghtsAsJsonObjects() const;

	/**
	 * @brief Adding new angle value dependency
	 * 
	 * @param point1Id ID of first point on angle
	 * @param vertexId ID of angle vertex point
	 * @param point2Id ID of second point on angle
	 * @param type type of angle
	 * @param value angle value to set
	 * @param reason dependency reason
	 */
	inline void setAngleValue(unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, Angle::AngleType type, std::string value) { angleValues.push_back(AngleValue(point1Id, vertexId, point2Id, type, value)); }
	
	/**
	 * @brief Getting all angle value dependencies as written to JSON object as JSON objects
	 * 
	 * @return JSON object with JSON objects representing angle value dependencies
	 */
	json getAngleValuesAsJsonObjects() const;

	inline void addTangentLine(unsigned int lineId, unsigned int circleId) { tangentLines.push_back(LineCircleDependency(lineId, circleId)); }
	json getTangentLinesAsJsonObjects() const;

	inline void addBisectorLine(unsigned int lineId, unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, Angle::AngleType angleType) { bisectorLines.push_back(LineAngleDependency(lineId, point1Id, vertexId, point2Id, angleType)); }
	json getBisectorLinesAsJsonObjects() const;

	inline void addMidPerpendicularLine(unsigned int lineId, unsigned int end1Id, unsigned int end2Id) { midPerpendicularLines.push_back(LineSegmentDependency(lineId, end1Id, end2Id)); }
	json getMidPerpendicularLinesAsJsonObjects() const;

	inline void addEscribedCircle(std::vector<unsigned int> polygon, unsigned int circleId) { escribedCircles.push_back(PolygonCircleDependency(polygon, circleId)); }
	json getEscribedCirclesAsJsonObjects() const;

	inline void addInscribedCircle(std::vector<unsigned int> polygon, unsigned int circleId) { inscribedCircles.push_back(PolygonCircleDependency(polygon, circleId)); }
	json getInscribedCirclesAsJsonObjects() const;

	inline void addCircumscribedCircle(std::vector<unsigned int> polygon, unsigned int circleId) { circumscribedCircles.push_back(PolygonCircleDependency(polygon, circleId)); }
	json getCircumscribedCirclesAsJsonObjects() const;

	inline void addPolygonType(std::vector<unsigned int> polygon, PolygonTypeDependency::PolygonType type) { polygonsTypes.push_back(PolygonTypeDependency(polygon, type)); }
	json getPolygonTypesAsJsonObjects() const;

	inline void addMedian(unsigned int segment1End1Id, unsigned int segment1End2Id, unsigned int segment2End1Id, unsigned int segment2End2Id) { medians.push_back(SegmentsDependency(segment1End1Id, segment1End2Id, segment2End1Id, segment2End2Id)); }
	json getMediansAsJsonObjects() const;

	inline void addAltitude(unsigned int altitudeEnd1Id, unsigned int altitudeEnd2Id, unsigned int baseLineId) { altitudes.push_back(LineSegmentDependency(baseLineId, altitudeEnd1Id, altitudeEnd2Id)); }
	json getAltitudesAsJsonObjects() const;

	inline void addMidSegment(unsigned int arm1End1, unsigned int arm1End2, unsigned int arm2End1, unsigned int arm2End2, unsigned int segmentEnd1, unsigned int segmentEnd2) { midSegments.push_back(SegmentArmsDependency(arm1End1, arm1End2, arm2End1, arm2End2, segmentEnd1, segmentEnd2)); }
	json getMidSegmentsAsJsonObjects() const;

	inline void addTangentCircles(unsigned int circle1Id, unsigned int circle2Id) { tangentCircles.push_back(CirclesDependency(circle1Id, circle2Id)); }
	json getTangentCirclesAsJsonObjects() const;
};

#endif /* DEPENDENCIES_MANAGER_H */