#include "./../../inc/manager/ShapesManager.h"

ShapesManager::ShapesManager()
:	idCounter(1),
	points(std::map<unsigned int, PointShape>()),
	circles(std::map<unsigned int, CircleShape>()),
	segments(std::map<unsigned int, SegmentShape>()),
	segmentsWithDeletions(std::map<unsigned int, SegmentShape>()),
	deletedSegmentsMap(std::map<unsigned int, std::pair<unsigned int, unsigned int>>()),
	deletedSegmentIds(std::set<unsigned int>())
	{ }

ShapesManager::ShapesManager(const ShapesManager& shapesManager) 
:   idCounter(shapesManager.idCounter),
	points(shapesManager.points),
	circles(shapesManager.circles),
	segments(shapesManager.segments),
	segmentsWithDeletions(shapesManager.segmentsWithDeletions),
	deletedSegmentsMap(shapesManager.deletedSegmentsMap),
	deletedSegmentIds(shapesManager.deletedSegmentIds)
	{ }

ShapesManager& ShapesManager::operator=(const ShapesManager& shapesManager) {
	idCounter = shapesManager.idCounter;
	points = shapesManager.points;
	circles = shapesManager.circles;
	segments = shapesManager.segments;
	segmentsWithDeletions = shapesManager.segmentsWithDeletions;
	deletedSegmentsMap = shapesManager.deletedSegmentsMap;
	deletedSegmentIds = shapesManager.deletedSegmentIds;

	return *this;
}

std::pair<unsigned int, bool> ShapesManager::addPoint(double x, double y) {
	PointShape newPoint = PointShape(x, y);

	std::map<unsigned int, PointShape>::const_iterator mIt;
	for (mIt = points.begin(); mIt != points.end(); mIt++) {
		if ((mIt->second) == newPoint) {
			return {mIt->first, false};
		}
	}

	points.insert({ idCounter,  newPoint });
	idCounter++;

	return {idCounter - 1, true};
}

json ShapesManager::getPointsAsJsonObjects() const {
	json result;

	std::map<unsigned int, PointShape>::const_iterator mIt;
	for (mIt = points.begin(); mIt != points.end(); mIt++) {
		result.push_back({ 
			{"id", mIt->first}, 
			{"x", mIt->second.getX()},
			{"y", mIt->second.getY()} 
		});
	}

	return result;
}

std::pair<unsigned int, bool> ShapesManager::addCircle(PointShape& centerPoint, unsigned int centerPointId, PointShape& pointOnCircle, unsigned int pointOnCircleId) {
	CircleShape newCircle = CircleShape(centerPoint, centerPointId, pointOnCircle, pointOnCircleId);

	std::map<unsigned int, CircleShape>::iterator cIt;
	for (cIt = circles.begin(); cIt != circles.end(); cIt++) {
		if ((cIt->second) == newCircle) {
			return {cIt->first, false};
		}
	}
	
	circles.insert({ idCounter, newCircle });
	idCounter++;

	return {idCounter - 1, true};
}

json ShapesManager::getCirclesAsJsonObjects() const {
	json result;

	std::map<unsigned int, CircleShape>::const_iterator cIt;
	for (cIt = circles.begin(); cIt != circles.end(); cIt++) {
		std::vector<unsigned int> includedPoints;

		std::cout << "INCLUDED POINTS 1 = " << cIt->second.getIncludedPoints()->size() << std::endl;

		std::set<unsigned int>::iterator sIt;
		for (sIt = cIt->second.getIncludedPoints()->begin(); sIt != cIt->second.getIncludedPoints()->end(); sIt++) {
			includedPoints.push_back(*sIt);
		}

		std::cout << "INCLUDED POINTS 2 = " << includedPoints.size() << std::endl;

		result.push_back({ 
			{"id", cIt->first}, 
			{"centerId", cIt->second.getCenterId()}, 
			{"centerX", cIt->second.getCenterPoint().getX()},
			{"centerY", cIt->second.getCenterPoint().getY()},
			{"radius", cIt->second.getRadius()},
			{"pointsOn", json(includedPoints)}
		});
	}

	return result;
}

std::pair<unsigned int, bool> ShapesManager::addSegment(PointShape& point1, unsigned int point1Id, PointShape& point2, unsigned int point2Id) {
	SegmentShape newSegment = SegmentShape(point1, point1Id, point2, point2Id);

	std::map<unsigned int, SegmentShape>::iterator sIt;
	for (sIt = segments.begin(); sIt != segments.end(); sIt++) {
		if ((sIt->second) == newSegment) {
			return {sIt->first, false};
		}
	}

	segments.insert({ idCounter, newSegment});
	segmentsWithDeletions.insert({ idCounter, newSegment});
	idCounter++;

	return {idCounter - 1, true};
}

json ShapesManager::getSegmentsAsJsonObjects() const {
	json result;

	std::map<unsigned int, SegmentShape>::const_iterator sIt;
	for (sIt = segmentsWithDeletions.begin(); sIt != segmentsWithDeletions.end(); sIt++) {
		result.push_back({
			{"id", sIt->first},
			{"end1Id", sIt->second.getEnd1Id()},
			{"end2Id", sIt->second.getEnd2Id()},
		});
	}

	return result;
}

void ShapesManager::deleteSegment(unsigned int id, unsigned int newId1, unsigned int newId2) {
	segmentsWithDeletions.erase(id);
	deletedSegmentsMap.insert({id, {newId1, newId2} });
	deletedSegmentIds.insert(id);
}

