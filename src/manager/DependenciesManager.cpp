#include "./../../inc/manager/DependenciesManager.h"

DependenciesManager::DependenciesManager() 
: 	perpendicularLines(std::vector<LinesDependency>()),
	parallelLines(std::vector<LinesDependency>()),
	equalSegments(std::vector<SegmentsDependency>()),
	equalAngles(std::vector<AnglesDependency>()),
	segmentLengths(std::vector<SegmentLength>()),
	angleValues(std::vector<AngleValue>()),
	tangentLines(std::vector<LineCircleDependency>()),
	bisectorLines(std::vector<LineAngleDependency>()),
	midPerpendicularLines(std::vector<LineSegmentDependency>()),
	escribedCircles(std::vector<PolygonCircleDependency>()),
	inscribedCircles(std::vector<PolygonCircleDependency>()),
	circumscribedCircles(std::vector<PolygonCircleDependency>()),
	polygonsTypes(std::vector<PolygonTypeDependency>()),
	medians(std::vector<SegmentsDependency>()),
	altitudes(std::vector<LineSegmentDependency>()),
	midSegments(std::vector<SegmentArmsDependency>()),
	tangentCircles(std::vector<CirclesDependency>())
	{ }

DependenciesManager::DependenciesManager(const DependenciesManager& dependenciesManager)
:   perpendicularLines(dependenciesManager.perpendicularLines),
	parallelLines(dependenciesManager.parallelLines),
	equalSegments(dependenciesManager.equalSegments),
	equalAngles(dependenciesManager.equalAngles),
	segmentLengths(dependenciesManager.segmentLengths),
	angleValues(dependenciesManager.angleValues),
	tangentLines(dependenciesManager.tangentLines), 
	bisectorLines(dependenciesManager.bisectorLines), 
	midPerpendicularLines(dependenciesManager.midPerpendicularLines) ,
	escribedCircles(dependenciesManager.escribedCircles),
	inscribedCircles(dependenciesManager.inscribedCircles), 
	circumscribedCircles(dependenciesManager.circumscribedCircles), 
	polygonsTypes(dependenciesManager.polygonsTypes),
	medians(dependenciesManager.medians),
	altitudes(dependenciesManager.altitudes), 
	midSegments(dependenciesManager.midSegments),
	tangentCircles(dependenciesManager.tangentCircles)
{}

DependenciesManager& DependenciesManager::operator=(const DependenciesManager& dependenciesManager) {
	perpendicularLines = dependenciesManager.perpendicularLines;
	parallelLines = dependenciesManager.parallelLines;
	equalSegments = dependenciesManager.equalSegments;
	equalAngles = dependenciesManager.equalAngles;
	segmentLengths = dependenciesManager.segmentLengths;
	angleValues = dependenciesManager.angleValues;
	tangentLines = dependenciesManager.tangentLines;
	bisectorLines = dependenciesManager.bisectorLines;
	midPerpendicularLines = dependenciesManager.midPerpendicularLines;
	escribedCircles = dependenciesManager.escribedCircles;
	inscribedCircles = dependenciesManager.inscribedCircles;
	circumscribedCircles = dependenciesManager.circumscribedCircles;
	polygonsTypes = dependenciesManager.polygonsTypes;
	medians = dependenciesManager.medians;
	altitudes = dependenciesManager.altitudes;
	midSegments = dependenciesManager.midSegments;
	tangentCircles = dependenciesManager.tangentCircles;

	return *this;
}

json DependenciesManager::getPerpendicularLinesAsJsonObjects() const {
	json result;

	std::vector<LinesDependency>::const_iterator vIt;
	for (vIt = perpendicularLines.begin(); vIt != perpendicularLines.end(); vIt++) {
		result.push_back({
			{"id1", vIt->getFirst()},
			{"id2", vIt->getSecond()}
		});
	}

	return result;
}

json DependenciesManager::getParallelLinesAsJsonObjects() const {
	json result;

	std::vector<LinesDependency>::const_iterator vIt;
	for (vIt = parallelLines.begin(); vIt != parallelLines.end(); vIt++) {
		result.push_back({
			{"id1", vIt->getFirst()},
			{"id2", vIt->getSecond()}
		});
	}

	return result;
}

json DependenciesManager::getEqualSegmentsAsJsonObjects() const {
	json result;

	std::vector<SegmentsDependency>::const_iterator vIt;
	for (vIt = equalSegments.begin(); vIt != equalSegments.end(); vIt++) {
		result.push_back({
			{"s1End1Id", vIt->getSegment1Ends().getFirst()},
			{"s1End2Id", vIt->getSegment1Ends().getSecond()},
			{"s2End1Id", vIt->getSegment2Ends().getFirst()},
			{"s2End2Id", vIt->getSegment2Ends().getSecond()}
		});
	}

	return result;
}

json DependenciesManager::getEqualAnglesAsJsonObjects() const {
	json result;

	std::vector<AnglesDependency>::const_iterator vIt;
	for (vIt = equalAngles.begin(); vIt != equalAngles.end(); vIt++) {
		result.push_back({
			{"a1End1Id", vIt->getAngle1().getPointsOnArms().getFirst()},
			{"a1VertexId", vIt->getAngle1().getVertex()},
			{"a1End2Id", vIt->getAngle1().getPointsOnArms().getSecond()},
			{"a1Type", int(vIt->getAngle1().getType())},
			{"a2End1Id", vIt->getAngle2().getPointsOnArms().getFirst()},
			{"a2VertexId", vIt->getAngle2().getVertex()},
			{"a2End2Id", vIt->getAngle2().getPointsOnArms().getSecond()},
			{"a2Type", int(vIt->getAngle2().getType())}
		});
	}

	return result;
}

json DependenciesManager::getSegmentLenghtsAsJsonObjects() const {
	json result;

	std::vector<SegmentLength>::const_iterator vIt;
	for (vIt = segmentLengths.begin(); vIt != segmentLengths.end(); vIt++) {
		result.push_back({
			{"end1Id", vIt->getSegment().getFirst()},
			{"end2Id", vIt->getSegment().getSecond()},
			{"value", vIt->getValue()}
		});
	}

	return result;
}

json DependenciesManager::getAngleValuesAsJsonObjects() const {
	json result;

	std::vector<AngleValue>::const_iterator vIt;
	for (vIt = angleValues.begin(); vIt != angleValues.end(); vIt++) {
		int typeInt = vIt->getAngle().getType() == Angle::AngleType::CONVEX ? 1 : 2;

		result.push_back({
			{"end1Id", vIt->getAngle().getPointsOnArms().getFirst()},
			{"vertexId", vIt->getAngle().getVertex()},
			{"end2Id", vIt->getAngle().getPointsOnArms().getSecond()},
			{"type", typeInt},
			{"value", vIt->getValue()}
		});
	}

	return result;
}

json DependenciesManager::getTangentLinesAsJsonObjects() const {
	json result;

	std::vector<LineCircleDependency>::const_iterator vIt;
	for(vIt = tangentLines.begin(); vIt != tangentLines.end(); vIt++) {
		result.push_back({
			{"lineId", vIt->getLineId()},
			{"circleId", vIt->getCircleId()}
		});
	}

	return result;
}

json DependenciesManager::getBisectorLinesAsJsonObjects() const {
	json result;

	std::vector<LineAngleDependency>::const_iterator vIt;
	for(vIt = bisectorLines.begin(); vIt != bisectorLines.end(); vIt++) {
		int typeInt = vIt->getAngle().getType() == Angle::AngleType::CONVEX ? 1 : 2;
		
		result.push_back({
			{"lineId", vIt->getLineId()},
			{"point1Id", vIt->getAngle().getPointsOnArms().getFirst()},
			{"vertexId", vIt->getAngle().getVertex()},
			{"point2Id", vIt->getAngle().getPointsOnArms().getSecond()},
			{"angleType", typeInt}
		});
	}

	return result;
}

json DependenciesManager::getMidPerpendicularLinesAsJsonObjects() const {
	json result;

	std::vector<LineSegmentDependency>::const_iterator vIt;
	for(vIt = midPerpendicularLines.begin(); vIt != midPerpendicularLines.end(); vIt++) {
		result.push_back({
			{"lineId", vIt->getLineId()},
			{"end1Id", vIt->getSegment().getFirst()},
			{"end2Id", vIt->getSegment().getSecond()}
		});
	}

	return result;
}

json DependenciesManager::getEscribedCirclesAsJsonObjects() const {
	json result;

	std::vector<PolygonCircleDependency>::const_iterator vIt;
	for(vIt = escribedCircles.begin(); vIt != escribedCircles.end(); vIt++) {
		result.push_back({
			{"circleId", vIt->getCircleId()},
			{"polygon", json(vIt->getPolygonVerticesIds())}
		});
	}

	return result;
}

json DependenciesManager::getInscribedCirclesAsJsonObjects() const {
	json result;

	std::vector<PolygonCircleDependency>::const_iterator vIt;
	for(vIt = inscribedCircles.begin(); vIt != inscribedCircles.end(); vIt++) {
		result.push_back({
			{"circleId", vIt->getCircleId()},
			{"polygon", json(vIt->getPolygonVerticesIds())}
		});
	}

	return result;
}

json DependenciesManager::getCircumscribedCirclesAsJsonObjects() const {
	json result;

	std::vector<PolygonCircleDependency>::const_iterator vIt;
	for(vIt = circumscribedCircles.begin(); vIt != circumscribedCircles.end(); vIt++) {
		result.push_back({
			{"circleId", vIt->getCircleId()},
			{"polygon", json(vIt->getPolygonVerticesIds())}
		});
	}

	return result;
}

json DependenciesManager::getPolygonTypesAsJsonObjects() const {
	json result;

	std::vector<PolygonTypeDependency>::const_iterator vIt;
	for(vIt = polygonsTypes.begin(); vIt != polygonsTypes.end(); vIt++) {
		result.push_back({
			{"polygon", json(vIt->getPolygonVerticesIds())},
			{"type", int(vIt->getType())}
		});
	}

	return result;
}

json DependenciesManager::getMediansAsJsonObjects() const {
	json result;

	std::vector<SegmentsDependency>::const_iterator vIt;
	for(vIt = medians.begin(); vIt != medians.end(); vIt++) {
		result.push_back({
			{"s1End1Id", vIt->getSegment1Ends().getFirst()},
			{"s1End2Id", vIt->getSegment1Ends().getSecond()},
			{"s2End1Id", vIt->getSegment2Ends().getFirst()},
			{"s2End2Id", vIt->getSegment2Ends().getSecond()}
		});
	}

	return result;
}

json DependenciesManager::getAltitudesAsJsonObjects() const {
	json result;

	std::vector<LineSegmentDependency>::const_iterator vIt;
	for(vIt = altitudes.begin(); vIt != altitudes.end(); vIt++) {
		result.push_back({
			{"lineId", vIt->getLineId()},
			{"end1Id", vIt->getSegment().getFirst()},
			{"end2Id", vIt->getSegment().getSecond()}
		});
	}

	return result;
}

json DependenciesManager::getMidSegmentsAsJsonObjects() const {
	json result;

	std::vector<SegmentArmsDependency>::const_iterator vIt;
	for(vIt = midSegments.begin(); vIt != midSegments.end(); vIt++) {		
		result.push_back({
			{"a1End1Id", vIt->getArm1Ends().getFirst()},
			{"a1End2Id", vIt->getArm1Ends().getSecond()},
			{"a2End1Id", vIt->getArm2Ends().getFirst()},
			{"a2End2Id", vIt->getArm2Ends().getSecond()},
			{"sEnd1", vIt->getSegmentEnds().getFirst()},
			{"sEnd2", vIt->getSegmentEnds().getSecond()}
		});
	}

	return result;
}

json DependenciesManager::getTangentCirclesAsJsonObjects() const {
	json result;

	std::vector<CirclesDependency>::const_iterator vIt;
	for (vIt = tangentCircles.begin(); vIt != tangentCircles.end(); vIt++) {
		result.push_back({
			{"id1", vIt->getFirst()},
			{"id2", vIt->getSecond()}
		});
	}

	return result;
}
