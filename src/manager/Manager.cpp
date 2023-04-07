#include "./../../inc/manager/Manager.h"

/* * * *
P U B L I C  F U N C T I O N S
						* * * */

#ifdef CONVERTING_TO_WEBASSEMBLY
Manager::Manager(double width, double height, double offset, 
		int drawPointFunctionPointer, 
		int drawSegmentFunctionPointer, 
		int drawCircleFunctionPointer, 
		int deleteShapeFunctionPointer, 
		int setPromptingShapeStartPointFunctionPointer, 
		int processingCompletedAlertFunctionPointer, 
		int alertFunctionPointer)

	: canvasWidth(width),
	canvasHeight(height),
	offset(offset),
	buffer(std::vector<unsigned int>()),
	currentlyCreatedShape(ShapeToCreate::NONE),
	lineEquationsCounter(1),
	lineEquationsIds(std::map<std::string, unsigned int>()),
	lineEquations(std::map<unsigned int, LineEquation>()),
	pointsOnLines(std::map<unsigned int, std::vector<unsigned int>>()),
	segmentsOnLines(std::map<unsigned int, std::vector<unsigned int>>()),
	shapes(ShapesManager()),
	dependencies(DependenciesManager()),
	idsNonConsidered(std::set<unsigned int>()),
	drawPointFunction(reinterpret_cast<void (*)(int, double, double)>(drawPointFunctionPointer)),
	drawSegmentFunction(reinterpret_cast<void (*)(int, double, double, double, double)>(drawSegmentFunctionPointer)),
	drawCircleFunction(reinterpret_cast<void (*)(int, double, double, double)>(drawCircleFunctionPointer)),
	deleteShapeFunction(reinterpret_cast<void (*)(int)>(deleteShapeFunctionPointer)),
	setPromptingShapeStartPointFunction(reinterpret_cast<void (*)(int, double, double)>(setPromptingShapeStartPointFunctionPointer)),
	processingCompletedAlertFunction(reinterpret_cast<void (*)()>(processingCompletedAlertFunctionPointer)),
	alertFunction(reinterpret_cast<void (*)(int, const char*)>(alertFunctionPointer))

	{ alertFunction(3, "INITIALISATION OF COMPUTING MODULE SUCCESSFULLY COMPLETED!"); }
#else
Manager::Manager(double width, double height, double offset,
		void (*drawPointFunction)(int, double, double),
		void (*drawSegmentFunction)(int, double, double, double, double),
		void (*drawCircleFunction)(int, double, double, double),
		void (*deleteShapeFunction)(int),
		void (*setPromptingShapeStartPointFunction)(int, double, double),
		void (*processingCompletedAlertFunction)(),
		void (*alertFunction)(int, const char*))

	: canvasWidth(width),
	canvasHeight(height),
	offset(offset),
	buffer(std::vector<unsigned int>()),
	currentlyCreatedShape(ShapeToCreate::NONE),
	lineEquationsCounter(1),
	lineEquationsIds(std::map<std::string, unsigned int>()),
	lineEquations(std::map<unsigned int, LineEquation>()),
	pointsOnLines(std::map<unsigned int, std::vector<unsigned int>>()),
	segmentsOnLines(std::map<unsigned int, std::vector<unsigned int>>()),
	shapes(ShapesManager()),
	dependencies(DependenciesManager()),
	idsNonConsidered(std::set<unsigned int>()),
	drawPointFunction(drawPointFunction),
	drawSegmentFunction(drawSegmentFunction),
	drawCircleFunction(drawCircleFunction),
	deleteShapeFunction(deleteShapeFunction),
	setPromptingShapeStartPointFunction(setPromptingShapeStartPointFunction),
	processingCompletedAlertFunction(processingCompletedAlertFunction),
	alertFunction(alertFunction)

	{ alertFunction(3, "INITIALISATION OF COMPUTING MODULE SUCCESSFULLY COMPLETED!"); }
#endif // CONVERTING_TO_WEBASSEMBLY

void Manager::clearCanvas() {
	try {
		buffer = std::vector<unsigned int>();
		currentlyCreatedShape = ShapeToCreate::NONE;
		lineEquationsCounter = 1;
		lineEquationsIds = std::map<std::string, unsigned int>();
		lineEquations = std::map<unsigned int, LineEquation>();
		pointsOnLines = std::map<unsigned int, std::vector<unsigned int>>();
		segmentsOnLines = std::map<unsigned int, std::vector<unsigned int>>();
		shapes = ShapesManager();
		dependencies = DependenciesManager();
		idsNonConsidered = std::set<unsigned int>();

		processingCompletedAlertFunction();
	} 
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setCurrentlyCreatedShape(ShapeToCreate shape) {
	try {
		currentlyCreatedShape = shape;
		buffer.clear();
	}
	catch(...) {
		errorNotForeseen();
	}
}

unsigned int Manager::clickedOnCanvas(double x, double y) {
	try {
		unsigned int resultId = 0;

		if (currentlyCreatedShape == ShapeToCreate::POINT || 
			currentlyCreatedShape == ShapeToCreate::COMPLEX_SHAPE) {

			resultId = createPoint(x, y, false);
		}
		else if (currentlyCreatedShape == ShapeToCreate::SEGMENT ||
			currentlyCreatedShape == ShapeToCreate::LINE ||
			currentlyCreatedShape == ShapeToCreate::SEMILINE ||
			currentlyCreatedShape == ShapeToCreate::CIRCLE) {

			if (buffer.size() == 0) {
				resultId = createPoint(x, y, false);
				buffer.push_back(resultId);
				setPromptingShapeStartPointFunction(true, x, y);
			}
			else if (buffer.size() == 1) {
				resultId= createPoint(x, y, false);
				buffer.push_back(resultId);
				processFullBuffer();
			}
		}	

		processingCompletedAlertFunction();

		return resultId;
	}
	catch(...) {
		errorNotForeseen();
	}
}

unsigned int Manager::clickedOnPoint(unsigned int id) {
	try {
		unsigned int resultId = 0;

		if (currentlyCreatedShape == ShapeToCreate::SEGMENT ||
			currentlyCreatedShape == ShapeToCreate::LINE ||
			currentlyCreatedShape == ShapeToCreate::SEMILINE ||
			currentlyCreatedShape == ShapeToCreate::CIRCLE) {

			if (buffer.size() == 0) {
				buffer.push_back(id);
				PointShape chosenPoint = shapes.getPoint(id);
				setPromptingShapeStartPointFunction(true, chosenPoint.getX(), chosenPoint.getY());

				resultId = id;
			}
			else if (buffer.at(0) != id) {
				buffer.push_back(id);
				processFullBuffer();

				resultId = id;
			}
		}

		processingCompletedAlertFunction();

		return resultId;
	}
	catch(...) {
		errorNotForeseen();
	}
}

unsigned int Manager::clickedOnSegment(unsigned int id, double x, double y) {
	try {
		unsigned int resultId = 0;

		if (currentlyCreatedShape != ShapeToCreate::NONE) {
			std::vector<unsigned int> result = clickOnSegment(id, x, y);

			return clickedOnPoint(result.at(0));
		}
		else {
			processingCompletedAlertFunction();

			return resultId;
		}
	}
	catch(...) {
		errorNotForeseen();
	}
}

unsigned int Manager::clickedOnCircle(unsigned int id, double x, double y) {
	try {
		unsigned int resultId = 0;

		if (currentlyCreatedShape != ShapeToCreate::NONE) {
			unsigned int newPointId = clickOnCircle(id, x, y);

			return clickedOnPoint(newPointId);
		}
		else {
			processingCompletedAlertFunction();

			return resultId;
		}
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::displayPointsAndSegmentsOnLines() {
	std::map<std::string, unsigned int>::iterator mIt;
	std::vector<unsigned int>::iterator vIt1S, vIt1E;
	std::vector<unsigned int>::iterator vIt2S, vIt2E;

	std::cout << std::endl << "<-- Points And Segments On Lines -->" << std::endl;

	for (mIt = lineEquationsIds.begin(); mIt != lineEquationsIds.end(); mIt++) {
		std::cout << mIt->first << ": " << std::endl;

		vIt1S = pointsOnLines.find(mIt->second)->second.begin();
		vIt1E = pointsOnLines.find(mIt->second)->second.end();

		vIt2S = segmentsOnLines.find(mIt->second)->second.begin();
		vIt2E = segmentsOnLines.find(mIt->second)->second.end();

		for (; vIt1S != vIt1E; vIt1S++) {
			std::cout << shapes.getPoint((*vIt1S)) << "  ";
		}
		std::cout << std::endl;

		for (; vIt2S != vIt2E; vIt2S++) {
			SegmentShape s = shapes.getSegment((*vIt2S));
			std::cout << "|" << s.getEnd1() << " " << s.getEnd2() << "|  ";
		}
		std::cout << std::endl << std::endl;
	}
}

void Manager::setPerpendicularityDependency(unsigned int segment1Id, unsigned int segment2Id) {
	try {
		LineEquation line1 = shapes.getSegment(segment1Id);
		LineEquation line2 = shapes.getSegment(segment2Id);

		if(line1 == line2) {
			alertFunction(2, "SETTING THE PERPENDICULARITY DEPENDENCY DOES NOT MAKE SENSE!");
		}
		else if (fabs(Distance::tangentOfAngleBetweenLines(line1, line2)) > 6) { // angle > 80 degress
			alertFunction(1, "THE PERPENDICULARITY DEPENDENCY HAS BEEN SET!");
			dependencies.addPerpendicularLines(lineEquationsIds.at(line1.getStringHash()), lineEquationsIds.at(line2.getStringHash()));
		}
		else {
			alertFunction(2, "THE CHOSEN LINES CANNOT BE CONSIDERED AS PERPENDICULAR!");
		}
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setPerpendicularityDependencyBaseOnPoints(unsigned int line1Point1Id, unsigned int line1Point2Id, unsigned int line2Point1Id, unsigned int line2Point2Id) {
	try {
		PointEquation line1Point1 = shapes.getPoint(line1Point1Id);
		PointEquation line1Point2 = shapes.getPoint(line1Point2Id);
		PointEquation line2Point1 = shapes.getPoint(line2Point1Id);
		PointEquation line2Point2 = shapes.getPoint(line2Point2Id);

		LineEquation line1 = LineEquation(line1Point1, line1Point2);
		LineEquation line2 = LineEquation(line2Point1, line2Point2);

		if(line1 == line2) {
			alertFunction(2, "SETTING THE PERPENDICULARITY DEPENDENCY DOES NOT MAKE SENSE!");
		}
		else if (fabs(Distance::tangentOfAngleBetweenLines(line1, line2)) > 6) { // angle > 80 degress
			alertFunction(1, "THE PERPENDICULARITY DEPENDENCY HAS BEEN SET!");
			dependencies.addPerpendicularLines(lineEquationsIds.at(line1.getStringHash()), lineEquationsIds.at(line2.getStringHash()));
		}
		else {
			alertFunction(2, "THE CHOSEN LINES CANNOT BE CONSIDERED AS PERPENDICULAR!");
		}
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createPerpendicularLineToLine(unsigned int segmentId, unsigned int pointId) {
	try {
		SegmentShape line = shapes.getSegment(segmentId);
		unsigned int newLineEquationId = createPerpendicularLine(line, pointId);

		dependencies.addPerpendicularLines(lineEquationsIds.at(line.getStringHash()), newLineEquationId);
		
		alertFunction(1, "THE PERPENDICULAR LINE HAS BEEN CORRECTLY CREATED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setParallelismDependency(unsigned int segment1Id, unsigned int segment2Id) {
	try {
		LineEquation line1 = shapes.getSegment(segment1Id);
		LineEquation line2 = shapes.getSegment(segment2Id);

		if (line1 == line2) {
			alertFunction(2, "SETTING THE PARALLELISM DEPENDENCY DOES NOT MAKE SENSE!");
		}
		else {
			PointEquation commonPoint;
			int possibleCommonPointsNumber = IntersectionPoints::ofLines(line1, line2, &commonPoint);
			
			if (possibleCommonPointsNumber == 1 && commonPoint.getX() >= 0.0 && commonPoint.getX() <= canvasWidth && commonPoint.getY() >= 0.0 && commonPoint.getY() <= canvasHeight) {
				alertFunction(2, "THE CHOSEN LINES CANNOT BE CONSIDERED AS PARALLEL!");
			}
			else if (fabs(Distance::tangentOfAngleBetweenLines(line1, line2)) < 0.1) { // angle < 5 degress
				alertFunction(1, "THE PARALLELISM DEPENDENCY HAS BEEN SET!");
				dependencies.addParallelLines(lineEquationsIds.at(line1.getStringHash()), lineEquationsIds.at(line2.getStringHash()));
			}
			else {
				alertFunction(2, "THE CHOSEN LINES CANNOT BE CONSIDERED AS PARALLEL!");
			}
		}
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setParallelismDependencyBaseOnPoints(unsigned int line1Point1Id, unsigned int line1Point2Id, unsigned int line2Point1Id, unsigned int line2Point2Id) {
	try {
		PointEquation line1Point1 = shapes.getPoint(line1Point1Id);
		PointEquation line1Point2 = shapes.getPoint(line1Point2Id);
		PointEquation line2Point1 = shapes.getPoint(line2Point1Id);
		PointEquation line2Point2 = shapes.getPoint(line2Point2Id);

		LineEquation line1 = LineEquation(line1Point1, line1Point2);
		LineEquation line2 = LineEquation(line2Point1, line2Point2);

		if (line1 == line2) {
			alertFunction(2, "SETTING THE PARALLELISM DEPENDENCY DOES NOT MAKE SENSE!");
		}
		else {
			PointEquation commonPoint;
			int possibleCommonPointsNumber = IntersectionPoints::ofLines(line1, line2, &commonPoint);
			
			if (possibleCommonPointsNumber == 1 && commonPoint.getX() >= 0.0 && commonPoint.getX() <= canvasWidth && commonPoint.getY() >= 0.0 && commonPoint.getY() <= canvasHeight) {
				alertFunction(2, "THE CHOSEN LINES CANNOT BE CONSIDERED AS PARALLEL!");
			}
			else if (fabs(Distance::tangentOfAngleBetweenLines(line1, line2)) < 0.1) { // angle < 5 degress
				alertFunction(1, "THE PARALLELISM DEPENDENCY HAS BEEN SET!");
				dependencies.addParallelLines(lineEquationsIds.at(line1.getStringHash()), lineEquationsIds.at(line2.getStringHash()));
			}
			else {
				alertFunction(2, "THE CHOSEN LINES CANNOT BE CONSIDERED AS PARALLEL!");
			}
		}
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createParallelLineToLine(int lineId, int pointId) {
	try {
		SegmentShape line = shapes.getSegment(lineId);
		unsigned int newLineEquationId = createParallelLine(line, pointId);

		dependencies.addParallelLines(lineEquationsIds.at(line.getStringHash()), newLineEquationId);
		
		alertFunction(1, "THE PARALLEL LINE HAS BEEN CORRECTLY CREATED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setEqualSegmentsDependencyWithEnds(unsigned int segment1End1Id, unsigned int segment1End2Id, unsigned int segment2End1Id, unsigned int segment2End2Id) {
	alertFunction(1, "THE EQUAL SEGMENTS DEPENDENCY HAS BEEN SET!");
	dependencies.addEqualSegments(segment1End1Id, segment1End2Id, segment2End1Id, segment2End2Id);
}

void Manager::setEqualSegmentsDependnecyWithIds(unsigned int segment1Id, unsigned int segment2Id) {
	SegmentShape segment1 = shapes.getSegment(segment1Id);
	SegmentShape segment2 = shapes.getSegment(segment2Id);

	setEqualSegmentsDependencyWithEnds(segment1.getEnd1Id(), segment1.getEnd2Id(), segment2.getEnd1Id(), segment2.getEnd2Id());
}
	
void Manager::setEqualSegmentsDependencyWithMix(unsigned int segment1Id, unsigned int segment2End1Id, unsigned int segment2End2Id) {
	SegmentShape segment = shapes.getSegment(segment1Id);

	setEqualSegmentsDependencyWithEnds(segment.getEnd1Id(), segment.getEnd2Id(), segment2End1Id, segment2End2Id);
}

void Manager::setEqualAnglesDependency(unsigned int angle1Point1Id, unsigned int angle1VertexId, unsigned int angle1Point2Id, unsigned int angle2Point1Id, unsigned int angle2VertexId, unsigned int angle2Point2Id) {
	alertFunction(1, "THE EQUAL ANGLES DEPENDENCY HAS BEEN SET!");
	dependencies.addEqualAngles(angle1Point1Id, angle1VertexId, angle1Point2Id, Angle::AngleType::UNKNOWN, angle2Point1Id, angle2VertexId, angle2Point2Id, Angle::AngleType::UNKNOWN);
}

void Manager::setLengthValue(unsigned int end1Id, unsigned int end2Id, std::string value) {
	alertFunction(1, "THE LENGTH OF THE SEGMENT HAS BEEN SET!");
	dependencies.setSegmentLength(end1Id, end2Id, value);
}

void Manager::setSegmentLengthValue(unsigned int segmentId, std::string value) {
	SegmentShape segment = shapes.getSegment(segmentId);
	alertFunction(1, "THE LENGTH OF THE SEGMENT HAS BEEN SET!");
	dependencies.setSegmentLength(segment.getEnd1Id(), segment.getEnd2Id(), value);
}

void Manager::setAngleValue(unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, Angle::AngleType type, std::string value) {
	alertFunction(1, "THE VALUE OF THE ANGLE HAS BEEN SET!");
	dependencies.setAngleValue(point1Id, vertexId, point2Id, type, value);
}

void Manager::divideSegmentWithId(unsigned int segmentId, unsigned int n) {
	try {
		std::vector<unsigned int> points = divideSegmentId(segmentId, n);

		for (int i = 0; i < n-1; i++) {
			dependencies.addEqualSegments(points.at(i), points.at(i + 1), points.at(i + 1), points.at(i + 2));
		}

		alertFunction(1, "THE SEGMENT HAS BEEN CORRECTLY DIVIDED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::divideSegmentWithEnds(unsigned int end1Id, unsigned int end2Id, unsigned int n) {
	try {
		std::vector<unsigned int> points = divideSegmentEnds(end1Id, end2Id, n);

		for (int i = 0; i < n-1; i++) {
			dependencies.addEqualSegments(points.at(i), points.at(i + 1), points.at(i + 1), points.at(i + 2));
		}

		alertFunction(1, "THE SEGMENT HAS BEEN CORRECTLY DIVIDED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

// NIE DZIALA
// GLUPI POMYSL BYL JAK TO ZROBIC
// NA RAZIE INNEGO NIE WYMYSLILEM / NIE WYMYSLONO W NECIE
void Manager::divideAngle(unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, bool ofConvexAngle, unsigned int n) {
	try {
		if(n < 2) {
			return;
		}

		PointShape p1 = shapes.getPoint(point1Id);
		PointShape p2 = shapes.getPoint(vertexId);
		PointShape p3 = shapes.getPoint(point2Id);

		LineEquation arm1 = LineEquation(p1, p2);
		LineEquation arm2 = LineEquation(p2, p3);

		double d1 = Distance::ofPoints(p1, p2);
		double d2 = Distance::ofPoints(p2, p3);
		double d = d1 < d2 ? d1 : d2;

		p1 = arm1.getPointBetweenPointsWithDistance(p2, p1, d);
		p3 = arm2.getPointBetweenPointsWithDistance(p2, p3, d);

		double dx = (p3.getX() - p1.getX()) / n;
		double dy = (p3.getY() - p1.getY()) / n;

		unsigned int newPointId;
		for (int i = 1; i < n; i++) {
			if (ofConvexAngle) {
				newPointId = createPoint(p1.getX() + i * dx, p1.getY() + i * dy, true);
			}
			else {
				newPointId = createPoint(2 * p2.getX() - (p1.getX() + i * dx), 2 + p2.getX() - (p1.getY() + i * dy), true);
			}

			createSemiLine(vertexId, newPointId, true);
		}

		alertFunction(1, "THE ANGLE HAS BEEN CORRECTLY DIVIDED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}


void Manager::createSegmentMidPerpendicularWithId(unsigned int segmentId) {
	try {
		SegmentShape segment = shapes.getSegment(segmentId);
		std::vector<unsigned int> midPointId = divideSegmentId(segmentId, 2);
		unsigned int newLineId = createPerpendicularLine(segment, midPointId.at(1));

		dependencies.addMidPerpendicularLine(newLineId, segment.getEnd1Id(), segment.getEnd2Id());

		alertFunction(1, "THE MID PERPENDICULAR LINE HAS BEEN CORRECTLY CREATED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createSegmentMidPerpendicularWithEnds(unsigned int end1Id, unsigned int end2Id) {
	try {
		PointShape end1 = shapes.getPoint(end1Id);
		PointShape end2 = shapes.getPoint(end2Id);
		LineEquation lineEquation = LineEquation(end1, end2);

		std::vector<unsigned int> midPointId = divideSegmentEnds(end1Id, end2Id, 2);
		unsigned int newLineId = createPerpendicularLine(lineEquation, midPointId.at(1));

		dependencies.addMidPerpendicularLine(newLineId, end1Id, end2Id);

		alertFunction(1, "THE MID PERPENDICULAR LINE HAS BEEN CORRECTLY CREATED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createTangentLine(unsigned int pointId, unsigned int circleId) {
	try {
		CircleShape circle = shapes.getCircle(circleId);
		if (circle.getIncludedPoints()->find(pointId) != circle.getIncludedPoints()->end()) {
			idsNonConsidered.insert(circleId);

			unsigned int idOfNewLineEquation = createSegment(pointId, circle.getCenterId(), true);
			LineEquation newLineEquation = lineEquations.at(idOfNewLineEquation);

			unsigned int id = createPerpendicularLine(newLineEquation, pointId);

			dependencies.addTangentLine(id, circleId);

			idsNonConsidered.clear();

			alertFunction(1, "THE TANGENT LINE HAS BEEN CORRECTLY CREATED!");
		}

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createTangentCircleToLine(unsigned int centerId, unsigned int segmentId) {
	try {
		PointEquation circleCenter = shapes.getPoint(centerId);
		SegmentShape segment = shapes.getSegment(segmentId);
		LineEquation line = shapes.getSegment(segmentId);
		LineEquation radiusLine = Lines::getPerpendicularLine(line, circleCenter);
		PointEquation contactPoint;
		IntersectionPoints::ofLines(line, radiusLine, &contactPoint);

		unsigned int pointOnLine = 0;
		unsigned int newCircleId;

		if(segment.liesOn(contactPoint)) {
			std::vector<unsigned int> result = clickOnSegment(segmentId, contactPoint.getX(), contactPoint.getY());
			idsNonConsidered.insert(result[1]);
			idsNonConsidered.insert(result[2]);

			newCircleId = createCircle(centerId, result[0], true);

			idsNonConsidered.clear();

			pointOnLine = result[0];
		}
		else {
			unsigned int pointId = createPoint(contactPoint.getX(), contactPoint.getY(), true);

			newCircleId = createCircle(centerId, pointId, true);

			pointOnLine = pointId;
		}

		unsigned int idOfNewLineEquation = createSegment(pointOnLine, centerId, true);
		unsigned int mainLine = lineEquationsIds.at(line.getStringHash());

		dependencies.addTangentLine(mainLine, newCircleId);

		alertFunction(1, "THE TANGENT CIRCLE HAS BEEN CORRECTLY CREATED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createTangentCircleToCircle(unsigned int circleId, unsigned int newCircleCenterId, bool externally) {
	try {
		CircleShape baseCircle = shapes.getCircle(circleId);
		PointShape baseCircleCenter = shapes.getPoint(baseCircle.getCenterId());
		PointShape newCircleCenter = shapes.getPoint(newCircleCenterId);
		SegmentShape segmentBetweenCenters = SegmentShape(baseCircleCenter, baseCircle.getCenterId(), newCircleCenter, newCircleCenterId);

		PointEquation intersectionPoints[2], intersectionPoint;	
		IntersectionPoints::ofLineAndCircle(segmentBetweenCenters, baseCircle, intersectionPoints);

		if(Distance::ofPoints(baseCircleCenter, newCircleCenter) > baseCircle.getRadius()) {
			if(segmentBetweenCenters.liesOn(intersectionPoints[0])) {
				if(externally) {
					intersectionPoint = intersectionPoints[0];
				}
				else {
					intersectionPoint = intersectionPoints[1];
				}
			}
			else {
				if(externally) {
					intersectionPoint = intersectionPoints[1];
				}
				else {
					intersectionPoint = intersectionPoints[0];
				}
			}
		}
		else {
			if(Distance::ofPoints(intersectionPoints[0], newCircleCenter) > Distance::ofPoints(intersectionPoints[0], baseCircleCenter)) {
				if(externally) {
					intersectionPoint = intersectionPoints[0];
				}
				else {
					intersectionPoint = intersectionPoints[1];
				}
			}
			else {
				if(externally) {
					intersectionPoint = intersectionPoints[1];
				}
				else {
					intersectionPoint = intersectionPoints[0];
				}
			}
		}

		unsigned int newPointId = clickOnCircle(circleId, intersectionPoint.getX(), intersectionPoint.getY());

		idsNonConsidered.insert(circleId);
		unsigned int newCircleId = createCircle(newCircleCenterId, newPointId, true);
		idsNonConsidered.clear();

		dependencies.addTangentCircles(circleId, newCircleId);

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createAltitudeWithBaseId(unsigned int baseId, unsigned int vertexId) {
	try {
		SegmentShape segment = shapes.getSegment(baseId);
		createAltitudeWithBaseEnds(segment.getEnd1Id(), segment.getEnd2Id(), vertexId);

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createAltitudeWithBaseEnds(unsigned int end1Id, unsigned int end2Id, unsigned int vertexId) {
	try {
		PointShape end1 = shapes.getPoint(end1Id);
		PointShape end2 = shapes.getPoint(end2Id);
		PointShape vertex = shapes.getPoint(vertexId);

		LineEquation baseEquation = LineEquation(end1, end2);
		LineEquation altitudeEquation = Lines::getPerpendicularLine(baseEquation, vertex);
		
		PointEquation spotPoint;
		IntersectionPoints::ofLines(baseEquation, altitudeEquation, &spotPoint);

		int spotPointId = -1;

		std::vector<unsigned int> segments = segmentsOnLines.at(lineEquationsIds.at(baseEquation.getStringHash()));
		std::vector<unsigned int>::iterator it;
		for (it = segments.begin(); it != segments.end(); it++) {
			SegmentShape s = shapes.getSegment(*it);
			if (s.liesOn(spotPoint)) {
				std::vector<unsigned int> clickResult = clickOnSegment(*it, spotPoint.getX(), spotPoint.getY());
				spotPointId = clickResult.at(0);
			}
		}

		if (spotPointId == -1) {
			spotPointId = createPoint(spotPoint.getX(), spotPoint.getY(), true);
		}

		createSegment(vertexId, spotPointId, true);

		//dependencies.addPerpendicularLines(lineEquationsIds.at(baseEquation.getStringHash()), lineEquationsIds.at(altitudeEquation.getStringHash()), DependencyReason(reason + DependencyReason::ALTITUDE ));
	
		dependencies.addAltitude(vertexId, spotPointId, lineEquationsIds.at(baseEquation.getStringHash()));

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createMedianWithBaseId(unsigned int baseId, unsigned int vertexId) {
	try {
		SegmentShape base = shapes.getSegment(baseId);
		std::vector<unsigned int> newPoints = divideSegmentId(baseId, 2);
		createSegment(vertexId, newPoints.at(1), true);

		dependencies.addMedian(vertexId, newPoints.at(1), base.getEnd1Id(), base.getEnd2Id());

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createMedianwithBaseEnds(unsigned int baseEnd1Id, unsigned int baseEnd2Id, unsigned int vertexId) {
	try {
		std::vector<unsigned int> newPoints = divideSegmentEnds(baseEnd1Id, baseEnd2Id, 2);
		createSegment(vertexId, newPoints.at(1), true);

		dependencies.addMedian(vertexId, newPoints.at(1), baseEnd1Id, baseEnd2Id);

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createMidSegmentWithArmIds(unsigned int arm1Id, unsigned int arm2Id) {
	try {
		SegmentShape arm1 = shapes.getSegment(arm1Id);
		SegmentShape arm2 = shapes.getSegment(arm2Id);
		std::vector<unsigned int> newPoints1 = divideSegmentId(arm1Id, 2);
		std::vector<unsigned int> newPoints2 = divideSegmentId(arm2Id, 2);

		createSegment(newPoints1.at(1), newPoints2.at(1), true);

		dependencies.addMidSegment(arm1.getEnd1Id(), arm1.getEnd2Id(), arm2.getEnd1Id(), arm2.getEnd2Id(), newPoints1.at(1), newPoints2.at(1));

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createMidSegmentWithArmEnds(unsigned int arm1End1Id, unsigned int arm1End2Id, unsigned int arm2End1Id, unsigned int arm2End2Id) {
	try {
		std::vector<unsigned int> newPoints1 = divideSegmentEnds(arm1End1Id, arm1End2Id, 2);
		std::vector<unsigned int> newPoints2 = divideSegmentEnds(arm2End1Id, arm2End2Id, 2);

		createSegment(newPoints1.at(1), newPoints2.at(1), true);

		dependencies.addMidSegment(arm1End1Id, arm1End2Id, arm2End1Id, arm2End2Id, newPoints1.at(1), newPoints2.at(1));

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createMidSegmentWithMix(unsigned int arm1Id, unsigned int arm2End1Id, unsigned int arm2End2Id) {
	try {
		SegmentShape arm1 = shapes.getSegment(arm1Id);
		std::vector<unsigned int> newPoints1 = divideSegmentId(arm1Id, 2);
		std::vector<unsigned int> newPoints2 = divideSegmentEnds(arm2End1Id, arm2End2Id, 2);

		createSegment(newPoints1.at(1), newPoints2.at(1), true);

		dependencies.addMidSegment(arm1.getEnd1Id(), arm1.getEnd2Id(), arm2End1Id, arm2End2Id, newPoints1.at(1), newPoints2.at(1));

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createBisectorLine(unsigned int point1Id, unsigned int vertexId, unsigned int point2Id, bool ofConvexAngle) {
	try {
		PointShape point1 = shapes.getPoint(point1Id);
		PointShape vertex = shapes.getPoint(vertexId);
		PointShape point2 = shapes.getPoint(point2Id);
		std::vector<LineEquation> bisectors = Lines::getBisectorLines(point1, vertex, point2);

		SegmentShape sideOppositeVertex = SegmentShape(point1, point1Id, point2, point2Id);
		PointEquation intersection1, intersection2, includingPoint;
		int intersectionNumber1 = IntersectionPoints::ofLines(sideOppositeVertex, bisectors.front(), &intersection1);
		int intersectionNumber2 = IntersectionPoints::ofLines(sideOppositeVertex, bisectors.back(), &intersection2);

		if (intersectionNumber1 == 1) {
			if (sideOppositeVertex.liesOn(intersection1)) {
				includingPoint = intersection1;
			}
			else {
				includingPoint = intersection2;
			}
		}
		else {
			includingPoint = intersection2;
		}

		// jak to ma stworzyc w odcinku punktu to lipa - np. trojkat rownoramienny - juz dziala
		unsigned int newPointId;
		Angle::AngleType type;
		if (ofConvexAngle) {
			newPointId = createPoint(includingPoint.getX(), includingPoint.getY(), true);
			type = Angle::AngleType::CONVEX;
		}
		else {
			newPointId = createPoint(2 * vertex.getX() - includingPoint.getX(), 2 * vertex.getY() - includingPoint.getY(), true);
			type = Angle::AngleType::CONCAVE;
		}
		unsigned int newLineId = createSemiLine(vertexId, newPointId, true);

		dependencies.addBisectorLine(newLineId, point1Id, vertexId, point2Id, type);

		alertFunction(1, "THE BISECTOR LINE HAS BEEN CORRECTLY CREATED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createInscribedCircle(std::vector<unsigned int> verticesIds) {
	try {
		std::vector<unsigned int>::iterator iIt;
		std::vector<std::pair<unsigned int, PointEquation>> vertices = {};
		std::vector<std::pair<unsigned int, PointEquation>>::iterator ipIt;
		for(iIt = verticesIds.begin(); iIt != verticesIds.end(); iIt++) {
			vertices.push_back({*iIt, shapes.getPoint(*iIt)});
		}

		std::vector<std::pair<unsigned int, PointEquation>>sortedVertices = sortVerticesClockwise(vertices);

		std::vector<PointEquation> sortedVerticesPointEquations;
		std::vector<unsigned int> sortedVerticesIds;
		for(ipIt = sortedVertices.begin(); ipIt != sortedVertices.end(); ipIt++) {
			sortedVerticesPointEquations.push_back(ipIt->second);
			sortedVerticesIds.push_back(ipIt->first);
		}

		CircleEquation circle = Circles::getInscribedCircle(sortedVerticesPointEquations);

		int centerPointId = createPoint(circle.getCenterPoint().getX(), circle.getCenterPoint().getY(), true);

		int n = sortedVertices.size();
		sortedVertices.push_back(sortedVertices[0]);

		PointEquation centerPoint = shapes.getPoint(centerPointId);

		LineEquation sideLine, radiusLine;
		PointEquation intersectionPoint;
		unsigned int pointOnSide;
		std::map<unsigned int, SegmentShape>::const_iterator it, sIt, eIt;
		shapes.getIteratorBoundsOfAllSegmentsMap(sIt, eIt);
		bool t = true;
		for(int i = 0; i<n; i++) {
			sideLine = LineEquation(sortedVerticesPointEquations[i], sortedVerticesPointEquations[i+1]);
			radiusLine = Lines::getPerpendicularLine(sideLine, centerPoint);
			IntersectionPoints::ofLines(sideLine, radiusLine, &intersectionPoint);

			for(it = sIt; it != eIt; it++) {
				SegmentShape segment = it->second;
				if(segment.getEnd1() == sortedVerticesPointEquations[i] && segment.getEnd2() == sortedVerticesPointEquations[i+1] || segment.getEnd1() == sortedVerticesPointEquations[i+1] && segment.getEnd2() == sortedVerticesPointEquations[i]) {
					std::vector<unsigned int> result = clickOnSegment(it->first, intersectionPoint.getX(), intersectionPoint.getY());
					pointOnSide = result[0];
					idsNonConsidered.insert(result[1]);
					idsNonConsidered.insert(result[2]);
					t = false;
					break;
				}
			}

			if(t) {
				pointOnSide = createPoint(intersectionPoint.getX(), intersectionPoint.getY(), true);
			}
		}

		unsigned int newCircleId = createCircle(centerPointId, pointOnSide, true);
		idsNonConsidered.clear();

		dependencies.addInscribedCircle(sortedVerticesIds, newCircleId);
		
		alertFunction(1, "THE INSCRIBED CIRCLE HAS BEEN CORRECTLY CREATED!");

		processingCompletedAlertFunction();
	}
	catch(Circles::InvalidPointsException) {
		alertFunction(2, "INCORRECT ARGUMENTS WERE GIVEN!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createCircumscribedCircle(std::vector<unsigned int> verticesIds) {
	try {
		std::vector<std::pair<unsigned int, PointEquation>> vertices = {};
		std::vector<unsigned int>::iterator it;
		for(it = verticesIds.begin(); it != verticesIds.end(); it++) {
			vertices.push_back({*it, shapes.getPoint(*it)});
		}

		std::vector<std::pair<unsigned int, PointEquation>>sortedVertices = sortVerticesClockwise(vertices);

		std::vector<PointEquation> sortedVerticesPointEquations;
		std::vector<unsigned int> sortedVerticesIds;
		std::vector<std::pair<unsigned int, PointEquation>>::iterator ipIt;
		for(ipIt = sortedVertices.begin(); ipIt != sortedVertices.end(); ipIt++) {
			sortedVerticesPointEquations.push_back(ipIt->second);
			sortedVerticesIds.push_back(ipIt->first);
		}


		CircleEquation circle = Circles::getCircumscribedCircle(sortedVerticesPointEquations);

		int centerPointId = createPoint(circle.getCenterPoint().getX(), circle.getCenterPoint().getY(), true);
		unsigned int newCircleId = createCircle(centerPointId, verticesIds.at(0), true);

		dependencies.addCircumscribedCircle(sortedVerticesIds, newCircleId);

		alertFunction(1, "THE CIRCUMSCRIBED CIRCLE HAS BEEN CORRECTLY CREATED!");

		processingCompletedAlertFunction();
	}
	catch(Circles::InvalidPointsException) {
		alertFunction(2, "INCORRECT ARGUMENTS WERE GIVEN!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createEscribedCircleWithSideId(unsigned int sideId, unsigned int pointId) {
	try {
		SegmentShape segment = shapes.getSegment(sideId);
		PointEquation point = shapes.getPoint(pointId);

		CircleEquation circle = Circles::getEscribedCircle(segment.getEnd1(), segment.getEnd2(), segment, point);

		int centerPointId = createPoint(circle.getCenterPoint().getX(), circle.getCenterPoint().getY(), true);

		PointEquation circleCenter = shapes.getPoint(centerPointId);
		LineEquation line = shapes.getSegment(sideId);
		LineEquation radiusLine = Lines::getPerpendicularLine(line, circleCenter);
		PointEquation contactPoint;
		IntersectionPoints::ofLines(line, radiusLine, &contactPoint);

		std::vector<unsigned int> result = clickOnSegment(sideId, contactPoint.getX(), contactPoint.getY());
		idsNonConsidered.insert(result[1]);
		idsNonConsidered.insert(result[2]);

		unsigned int newCircleId = createCircle(centerPointId, result[0], true);

		idsNonConsidered.clear();

		unsigned int idOfNewLineEquation = createSegment(result[0], centerPointId, true);
		unsigned int mainLine = lineEquationsIds.at(line.getStringHash());

		dependencies.addEscribedCircle({pointId, segment.getEnd1Id(), segment.getEnd2Id()}, newCircleId);

		alertFunction(1, "THE ESCRIBED CIRCLE HAS BEEN CORRECTLY CREATED!");

		processingCompletedAlertFunction();
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::createEscribedCircleWithSideEnds(unsigned int end1Id, unsigned int end2Id, unsigned int pointId) {
	try {
		std::map<unsigned int, SegmentShape>::const_iterator sIt, eIt, it;
		shapes.getIteratorBoundsOfAllSegmentsMap(sIt, eIt);

		for(it = sIt; it != eIt; it++) {
			SegmentShape segment = it->second;
			if(segment.getEnd1Id() == end1Id && segment.getEnd2Id() == end2Id) {
				createEscribedCircleWithSideId(it->first, pointId);
				return;
			}
			else if(segment.getEnd1Id() == end2Id && segment.getEnd2Id() == end1Id) {
				createEscribedCircleWithSideId(it->first, pointId);
				return;
			}
		}

		alertFunction(2, "INCORRECT ARGUMENTS WERE GIVEN!");
		processingCompletedAlertFunction();
	}	
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setPolygonType(std::vector<unsigned int> polygon, PolygonTypeDependency::PolygonType type) {
	try {
		dependencies.addPolygonType(polygon, type);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setPerpendicularLines(unsigned int line1, unsigned int line2) {
	try {
		dependencies.addPerpendicularLines(line1, line2);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setParallelLines(unsigned int line1, unsigned int line2) {
	try {
		dependencies.addParallelLines(line1, line2);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setEscribedCircle(unsigned int circleId, std::vector<unsigned int> polygon) {
	try {
		dependencies.addEscribedCircle(polygon, circleId);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setInscribedCircle(unsigned int circleId, std::vector<unsigned int> polygon) {
	try {
		dependencies.addInscribedCircle(polygon, circleId);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setCircumscribedCircle(unsigned int circleId, std::vector<unsigned int> polygon) {
	try {
		dependencies.addCircumscribedCircle(polygon, circleId);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setTangentLineToCircle(unsigned int lineId, unsigned int circleId) {
	try {
		dependencies.addTangentLine(lineId, circleId);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setTangentCircles(unsigned int circle1Id, unsigned int circle2Id) {
	try {
		dependencies.addTangentCircles(circle1Id, circle2Id);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setAltitude(unsigned int end1Id, unsigned int end2Id, unsigned int lineId) {
	try {
		dependencies.addAltitude(end1Id, end2Id, lineId);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setMedian(unsigned int s1End1Id, unsigned int s1End2Id, unsigned int s2End1Id, unsigned int s2End2Id) {
	try {
		dependencies.addMedian(s1End1Id, s1End2Id, s2End1Id, s2End2Id);
	}
	catch(...) {
		errorNotForeseen();
	}
}

void Manager::setMidSegment(unsigned int a1End1Id, unsigned int a1End2Id, unsigned int a2End1Id, unsigned int a2End2Id, unsigned int sEnd1, unsigned int sEnd2) {
	try {
		dependencies.addMidSegment(a1End1Id, a1End2Id, a2End1Id, a2End2Id, sEnd1, sEnd2);
	}
	catch(...) {
		errorNotForeseen();
	}
}

std::string Manager::getJsonData() {
	json lines;

	std::map<unsigned int, LineEquation>::iterator lIt;
	for (lIt = lineEquations.begin(); lIt != lineEquations.end(); lIt++) {
		lines.push_back({
			{"id", lIt->first},
			{"type", lIt->second.getType()},
			{"a", lIt->second.geta()},
			{"b", lIt->second.getb()},
			{"string", lIt->second.getStringHash()},
			{"pointsOn", json((pointsOnLines.at(lIt->first)))}
			});
	}

	json dataToExport = {
		{"maxShapeId", shapes.getIdCounter()},
		{"pointsNumber", shapes.getPointsNumber()},
		{"segmentsNumber", shapes.getSegmentsNumber()},
		{"circlesNumber", shapes.getCirclesNumber()},
		{"linesNumber", lineEquations.size()},
		{"points", shapes.getPointsAsJsonObjects()},
		{"segments", shapes.getSegmentsAsJsonObjects()},
		{"circles", shapes.getCirclesAsJsonObjects()},
		{"lines", lines},
		{"perpendicular", dependencies.getPerpendicularLinesAsJsonObjects()},
		{"parallel", dependencies.getParallelLinesAsJsonObjects()},
		{"equalSegments", dependencies.getEqualSegmentsAsJsonObjects()},
		{"equalAngles", dependencies.getEqualAnglesAsJsonObjects()},
		{"lengths", dependencies.getSegmentLenghtsAsJsonObjects()},
		{"angleValues", dependencies.getAngleValuesAsJsonObjects()},
		{"tangentLines", dependencies.getTangentLinesAsJsonObjects()},
		{"bisectorLines", dependencies.getBisectorLinesAsJsonObjects()},
		{"midPerpendicularLines", dependencies.getMidPerpendicularLinesAsJsonObjects()},
		{"escribedCircles", dependencies.getEscribedCirclesAsJsonObjects()},
		{"inscribedCircles", dependencies.getInscribedCirclesAsJsonObjects()},
		{"circumscribedCircles", dependencies.getCircumscribedCirclesAsJsonObjects()},
		{"polygonTypes", dependencies.getPolygonTypesAsJsonObjects()},
		{"medians", dependencies.getMediansAsJsonObjects()},
		{"altitudes", dependencies.getAltitudesAsJsonObjects()},
		{"midSegments", dependencies.getMidSegmentsAsJsonObjects()},
		{"tangentCircles", dependencies.getTangentCirclesAsJsonObjects()}
	};

	std::string res = dataToExport.dump();
	return res;
}

/* * * *                   
P R I V A T E  F U N C T I O N S
                        * * * */


void Manager::processFullBuffer() {
	if (currentlyCreatedShape == ShapeToCreate::SEGMENT) {
		createSegment(buffer[0], buffer[1], true);
	}
	else if (currentlyCreatedShape == ShapeToCreate::LINE) {
		createLine(buffer[0], buffer[1], true);
	}
	else if (currentlyCreatedShape == ShapeToCreate::SEMILINE) {
		createSemiLine(buffer[0], buffer[1], true);
	}
	else if (currentlyCreatedShape == ShapeToCreate::CIRCLE) {
		createCircle(buffer[0], buffer[1], true);
	}

	buffer.clear();
	setPromptingShapeStartPointFunction(false, 0.0, 0.0);
}

unsigned int Manager::createPoint(double x, double y, bool findIntersectionPoints) {
	std::pair<unsigned int, bool> result = shapes.addPoint(x, y);

	if (result.second) {
		drawPointFunction(result.first, x, y);

		if(findIntersectionPoints) {
			PointShape createdPoint = shapes.getPoint(result.first);

			std::map<unsigned int, SegmentShape>::const_iterator sIt, eIt, it;
			shapes.getIteratorBoundsOfSegmentsMap(sIt, eIt);

			for(it = sIt; it != eIt; it++) {
				SegmentShape segment = it->second;
				if(segment.liesOn(createdPoint)) {
					try {
						clickOnSegment(it->first, createdPoint.getX(), createdPoint.getY());
					}
					catch(...) {}

					break;
				}
			}
		}
	}

	return result.first;
}

unsigned int Manager::createSimpleSegment(PointShape& end1, unsigned int end1Id, PointShape& end2, unsigned int end2Id) {
	std::pair<unsigned int, bool> result = shapes.addSegment(end1, end1Id, end2, end2Id);

	if (result.second) {
		drawSegmentFunction(result.first, end1.getX(), end1.getY(), end2.getX(), end2.getY());
	}

	return result.first;
}

unsigned int Manager::createSegment(unsigned int end1Id, unsigned int end2Id, bool findIntersectionPoints) {
	PointShape end1 = shapes.getPoint(end1Id);
	PointShape end2 = shapes.getPoint(end2Id);

	LineEquation equation = LineEquation(end1, end2);

	auto getProperCoord = [&](const PointShape& point) {
		return equation.getType() == LineEquation::LineType::VERTICAL ? point.getY() : point.getX();
	};

	double end1ProperCoordinate = getProperCoord(end1);
	double end2ProperCoordinate = getProperCoord(end2);

	if (end1ProperCoordinate > end2ProperCoordinate) {
		std::swap(end1ProperCoordinate, end2ProperCoordinate);
		std::swap(end1Id, end2Id);
		std::swap(end1, end2);
	}

	if (lineEquationsIds.find(equation.getStringHash()) == lineEquationsIds.end()) {
		unsigned int newSegmentId = createSimpleSegment(end1, end1Id, end2, end2Id);

		lineEquationsIds.insert({ equation.getStringHash(), lineEquationsCounter });
		lineEquations.insert({ lineEquationsCounter, equation });
		segmentsOnLines.insert({ lineEquationsCounter, std::vector<unsigned int>{newSegmentId} });
		pointsOnLines.insert({ lineEquationsCounter, std::vector<unsigned int>{end1Id, end2Id} });

		lineEquationsCounter++;
	}
	else {
		unsigned int equationId = lineEquationsIds.at(equation.getStringHash());

		unsigned int minPointId = pointsOnLines.at(equationId).front();
		unsigned int maxPointId = pointsOnLines.at(equationId).back();

		double minPointCoord = getProperCoord(shapes.getPoint(minPointId));
		double maxPointCoord = getProperCoord(shapes.getPoint(maxPointId));

		if (end1ProperCoordinate < minPointCoord) {
			if (end2ProperCoordinate < minPointCoord) {
				unsigned int newSegmentId = createSimpleSegment(end1, end1Id, end2, end2Id);

				segmentsOnLines.at(equationId).insert(segmentsOnLines.at(equationId).begin(), newSegmentId);
				pointsOnLines.at(equationId).insert(pointsOnLines.at(equationId).begin(), end2Id);
				pointsOnLines.at(equationId).insert(pointsOnLines.at(equationId).begin(), end1Id);
			}
			else if (end2ProperCoordinate > maxPointCoord) {
				unsigned int rightPointId = pointsOnLines.at(equationId).front();
				unsigned int leftPointId = pointsOnLines.at(equationId).back();

				PointShape e1 = shapes.getPoint(rightPointId);
				PointShape e2 = shapes.getPoint(leftPointId);

				unsigned int newSegment1Id = createSimpleSegment(end1, end1Id, e1, rightPointId);
				unsigned int newSegment2Id = createSimpleSegment(end2, end2Id, e2, leftPointId);

				segmentsOnLines.at(equationId).insert(segmentsOnLines.at(equationId).begin(), newSegment1Id);
				segmentsOnLines.at(equationId).push_back(newSegment2Id);

				pointsOnLines.at(equationId).insert(pointsOnLines.at(equationId).begin(), end1Id);
				pointsOnLines.at(equationId).push_back(end2Id);
			}
			else {
				unsigned int rightPointId = pointsOnLines.at(equationId).front();
				PointShape e = shapes.getPoint(rightPointId);
				unsigned int newSegmentId = createSimpleSegment(end1, end1Id, e, rightPointId);
				segmentsOnLines.at(equationId).insert(segmentsOnLines.at(equationId).begin(), newSegmentId);
				pointsOnLines.at(equationId).insert(pointsOnLines.at(equationId).begin(), end1Id);
			}
		}
		else if (end1ProperCoordinate > maxPointCoord) {
			unsigned int newPointId = createSimpleSegment(end1, end1Id, end2, end2Id);
			segmentsOnLines.at(equationId).push_back(newPointId);
			pointsOnLines.at(equationId).push_back(end1Id);
			pointsOnLines.at(equationId).push_back(end2Id);
		}
		else {
			if (end2ProperCoordinate > maxPointCoord) {
				unsigned int leftPointId = pointsOnLines.at(equationId).back();
				PointShape e = shapes.getPoint(leftPointId);
				unsigned int newSegmentId = createSimpleSegment(end2, end2Id, e, leftPointId);
				
				segmentsOnLines.at(equationId).push_back(newSegmentId);
				pointsOnLines.at(equationId).push_back(end2Id);
			}
		}

		std::map<unsigned int, std::vector<unsigned int>>::iterator mIt = segmentsOnLines.find(equationId);
		std::vector<unsigned int>::iterator vIt;
		std::vector<unsigned int> newSegmentsVector = {};

		for (vIt = mIt->second.begin(); vIt != (mIt->second.end() - 1); vIt++) {
			newSegmentsVector.push_back(*vIt);

			SegmentShape s1 = shapes.getSegment(*vIt);
			SegmentShape s2 = shapes.getSegment(*(vIt + 1));
					
			if (s1.getEnd2Id() != s2.getEnd1Id()) {
				PointShape e1 = s1.getEnd2();
				PointShape e2 = s2.getEnd1();

				if (getProperCoord(e1) >= getProperCoord(end1) && getProperCoord(e1) <= getProperCoord(end2) &&
					getProperCoord(e2) >= getProperCoord(end1) && getProperCoord(e2) <= getProperCoord(end2)) {
					unsigned int newSegmentId = createSimpleSegment(e1, s1.getEnd2Id(), e2, s2.getEnd1Id());
					newSegmentsVector.push_back(newSegmentId);
				}
				else if (getProperCoord(end1) > getProperCoord(e1) && getProperCoord(end1) < getProperCoord(e2) &&
					getProperCoord(end2) > getProperCoord(e1) && getProperCoord(end2) < getProperCoord(e2)) {
					unsigned int newSegmentId = createSimpleSegment(end1, end1Id, end2, end2Id);
					newSegmentsVector.push_back(newSegmentId);
				}
				else if (getProperCoord(end1) <= getProperCoord(e1) &&
					getProperCoord(end2) > getProperCoord(e1) && getProperCoord(end2) < getProperCoord(e2)) {
					unsigned int newSegmentId = createSimpleSegment(e1, s1.getEnd1Id(), end2, end2Id);
					newSegmentsVector.push_back(newSegmentId);
				}
				else if (getProperCoord(end2) >= getProperCoord(e2) &&
					getProperCoord(end1) > getProperCoord(e1) && getProperCoord(end1) < getProperCoord(e2)) {
					unsigned int newSegmentId = createSimpleSegment(end1, end1Id, e2, end2Id);
					newSegmentsVector.push_back(newSegmentId);
				}
			}
		}

		newSegmentsVector.push_back(*vIt);
		mIt->second = newSegmentsVector;
	}	
	
	unsigned int equationId = lineEquationsIds.at(equation.getStringHash());

	std::vector<unsigned int> resultIds{}, resultIdsV2{};

	std::vector<unsigned int>::iterator it;
	for (it = segmentsOnLines.at(equationId).begin(); it != segmentsOnLines.at(equationId).end(); it++) {
		SegmentShape s = shapes.getSegment(*it);
		PointShape e1 = shapes.getPoint(s.getEnd1Id());
		PointShape e2 = shapes.getPoint(s.getEnd2Id());

		if (getProperCoord(e1) >= getProperCoord(end1) && getProperCoord(e2) <= getProperCoord(end2)) {
			resultIds.push_back(*it);
		}
	}

	std::sort(resultIds.begin(), resultIds.end());
	resultIds.erase(std::unique(resultIds.begin(), resultIds.end()), resultIds.end());

	if (findIntersectionPoints) {
		findIntersectionPointsWithLine(equationId, resultIds);
	}
	
	// detecting points which lies under segments
	std::map<unsigned int, PointShape>::const_iterator pIt, psIt, peIt;
	std::vector<unsigned int>::iterator rIt;
	shapes.getIteratorBoundsOfPointsMap(psIt, peIt);

	for (pIt = psIt; pIt != peIt; pIt++) {
		for (rIt = resultIds.begin(); rIt != resultIds.end(); rIt++) {
			SegmentShape resultSegment = shapes.getSegment(*rIt);
			if (resultSegment.liesOn(pIt->second)) {
				try {
					clickOnSegment(*rIt, pIt->second.getX(), pIt->second.getY());
				}
				catch(...) {}
			}
		}
	}

	return equationId;
}

unsigned int Manager::createLine(unsigned int point1Id, unsigned int point2Id, bool findIntersectionPoints) {
	const PointShape& point1 = shapes.getPoint(point1Id);
	const PointShape& point2 = shapes.getPoint(point2Id);

	LineEquation equation = LineEquation(point1, point2);

	std::vector<unsigned int> creatingPoints;

	if (equation.getType() == LineEquation::LineType::VERTICAL) {
		const PointShape& higherPoint = point1.getY() > point2.getY() ? point1 : point2;
		unsigned int higherPointId = point1.getY() > point2.getY() ? point1Id : point2Id;
		const PointShape& lowerPoint = point1.getY() > point2.getY() ? point2 : point1;
		unsigned int lowerPointId = point1.getY() > point2.getY() ? point2Id : point1Id;

		if(canvasHeight - offset > higherPoint.getY()) {
			unsigned int topPointId = createPoint(equation.getX(canvasHeight - offset), canvasHeight - offset, true);
			creatingPoints.push_back(topPointId);
		}
		creatingPoints.push_back(higherPointId);
		creatingPoints.push_back(lowerPointId);
		if(offset < lowerPoint.getY()) {
			unsigned int bottomPointId = createPoint(equation.getX(offset), offset, true);
			creatingPoints.push_back(bottomPointId);
		}
	}
	else if (equation.getType() == LineEquation::LineType::HORIZONTAL) {
		const PointShape& righterPoint = point1.getX() > point2.getX() ? point1 : point2;
		unsigned int righterPointId = point1.getX() > point2.getX() ? point1Id : point2Id;
		const PointShape& lefterPoint = point1.getX() > point2.getX() ? point2 : point1;
		unsigned int lefterPointId = point1.getX() > point2.getX() ? point2Id : point1Id;

		if(canvasWidth - offset > righterPoint.getX()) {
			unsigned int rightPointId = createPoint(canvasWidth - offset, equation.getY(canvasWidth - offset), true);
			creatingPoints.push_back(rightPointId);
		}
		creatingPoints.push_back(righterPointId);
		creatingPoints.push_back(lefterPointId);
		if(offset < lefterPoint.getX()) {
			unsigned int leftPointId = createPoint(offset, equation.getY(offset), true);
			creatingPoints.push_back(leftPointId);
		}
	}
	else {
		const PointShape& righterPoint = point1.getX() > point2.getX() ? point1 : point2;
		unsigned int righterPointId = point1.getX() > point2.getX() ? point1Id : point2Id;
		const PointShape& lefterPoint = point1.getX() > point2.getX() ? point2 : point1;
		unsigned int lefterPointId = point1.getX() > point2.getX() ? point2Id : point1Id;

		if(offset < lefterPoint.getX()) {
			double leftPointX = offset;
			double leftPointY = equation.getY(offset);

			if(leftPointY < offset) {
				leftPointX = equation.getX(offset);
				leftPointY = offset;
			}
			else if(leftPointY > canvasHeight - offset) {
				leftPointX = equation.getX(canvasHeight - offset);
				leftPointY = canvasHeight - offset;
			}

			unsigned int leftPointId = createPoint(leftPointX, leftPointY, true);
			creatingPoints.push_back(leftPointId);
			
		}
		creatingPoints.push_back(lefterPointId);
		creatingPoints.push_back(righterPointId);
		if(canvasWidth - offset > righterPoint.getX()) {
			double rightPointX = canvasWidth - offset;
			double rightPointY = equation.getY(canvasWidth - offset);

			if(rightPointY < offset) {
				rightPointX = equation.getX(offset);
				rightPointY = offset;
			}
			else if(rightPointY > canvasHeight - offset) {
				rightPointX = equation.getX(canvasHeight - offset);
				rightPointY = canvasHeight - offset;
			}

			unsigned int rightPointId = createPoint(rightPointX, rightPointY, true);
			creatingPoints.push_back(rightPointId);
		}
	}

	unsigned int result;
	for (int i = 0; i < (creatingPoints.size() - 1); i++) {
		result = createSegment(creatingPoints[i], creatingPoints[i + 1], findIntersectionPoints);
	}
	
	return result;
}

unsigned int Manager::createSemiLine(unsigned int startPointId, unsigned int includedPointId, bool findIntersectionPoints) {
	const PointShape& startPoint = shapes.getPoint(startPointId);
	const PointShape& includedPoint = shapes.getPoint(includedPointId);

	LineEquation equation = LineEquation(startPoint, includedPoint);

	std::vector<unsigned int> creatingPoints;

	if (equation.getType() == LineEquation::LineType::VERTICAL) {
		if (startPoint.getY() < includedPoint.getY()) {
			if(canvasHeight - offset > includedPoint.getY()) {
				unsigned int topPointId = createPoint(equation.getX(canvasHeight - offset), canvasHeight - offset, true);
				creatingPoints.push_back(topPointId);
			}
			creatingPoints.push_back(includedPointId);
			creatingPoints.push_back(startPointId);
		}
		else {
			if(offset < includedPoint.getY()) {
				unsigned int bottomPointId = createPoint(equation.getX(offset), offset, true);
				creatingPoints.push_back(bottomPointId);
			}
			creatingPoints.push_back(includedPointId);
			creatingPoints.push_back(startPointId);
		}
	}
	else if (equation.getType() == LineEquation::LineType::HORIZONTAL) {
		if (startPoint.getX() < includedPoint.getX()) {
			if(canvasWidth - offset > includedPoint.getX()) {
				unsigned int rightPointId = createPoint(canvasWidth - offset, equation.getY(canvasWidth - offset), true);
				creatingPoints.push_back(rightPointId);
			}
			creatingPoints.push_back(includedPointId);
			creatingPoints.push_back(startPointId);
		}
		else {
			if(offset < includedPoint.getX()) {
				unsigned int leftPointId = createPoint(offset, equation.getY(offset), true);
				creatingPoints.push_back(leftPointId);
			}
			creatingPoints.push_back(includedPointId);
			creatingPoints.push_back(startPointId);
		}
	}
	else {
		if (startPoint.getX() < includedPoint.getX()) {
			if(canvasWidth - offset > includedPoint.getX()) {
				double rightPointX = canvasWidth - offset;
				double rightPointY = equation.getY(canvasWidth - offset);

				if(rightPointY < offset) {
					rightPointX = equation.getX(offset);
					rightPointY = offset;
				}
				else if(rightPointY > canvasHeight - offset) {
					rightPointX = equation.getX(canvasHeight - offset);
					rightPointY = canvasHeight - offset;
				}

				unsigned int rightPointId = createPoint(rightPointX, rightPointY, true);
				creatingPoints.push_back(rightPointId);
			}
			creatingPoints.push_back(includedPointId);
			creatingPoints.push_back(startPointId);
		}
		else {
			if(offset < includedPoint.getX()) {
				double leftPointX = offset;
				double leftPointY = equation.getY(offset);

				if(leftPointY < offset) {
					leftPointX = equation.getX(offset);
					leftPointY = offset;
				}
				else if(leftPointY > canvasHeight - offset) {
					leftPointX = equation.getX(canvasHeight - offset);
					leftPointY = canvasHeight - offset;
				}

				unsigned int leftPointId = createPoint(leftPointX, leftPointY, true);
				creatingPoints.push_back(leftPointId);
			}
			creatingPoints.push_back(includedPointId);
			creatingPoints.push_back(startPointId);
		}
	}

	unsigned int result;
	for (int i = 0; i < (creatingPoints.size() - 1); i++) {
		result = createSegment(creatingPoints[i], creatingPoints[i + 1], findIntersectionPoints);
	}
	
	return result;
}

unsigned int Manager::createCircle(unsigned int centerPointId, unsigned int pointOnCircleId, bool findIntersectionPoints) {
	PointShape centerPoint = shapes.getPoint(centerPointId);
	PointShape pointOnCircle = shapes.getPoint(pointOnCircleId);

	std::pair<unsigned int, bool> result = shapes.addCircle(centerPoint, centerPointId, pointOnCircle, pointOnCircleId);

	if (result.second) {
		drawCircleFunction(result.first, centerPoint.getX(), centerPoint.getY(), Distance::ofPoints(centerPoint, pointOnCircle));
		
		if (findIntersectionPoints) {
			findIntersectionPointsWithCircle(result.first);
		}

		CircleShape createdCircle = shapes.getCircle(result.first);

		std::map<unsigned int, PointShape>::const_iterator it, startIt, endIt;
		shapes.getIteratorBoundsOfPointsMap(startIt, endIt);
		for (it = startIt; it != endIt; it++) {
			if (createdCircle.liesOn(it->second)) {
				clickOnCircle(result.first, it->second.getX(), it->second.getY());
			}
		}
	}

	return result.first;
}

std::vector<unsigned int> Manager::clickOnSegment(unsigned int id, double x, double y) noexcept(false) {
	if (shapes.isDeleted(id)) {
		std::pair<unsigned int, unsigned int> newSegmentsPair = shapes.getIdsFromDeletedSegment(id);
		std::vector<unsigned int> newSegments = {newSegmentsPair.first, newSegmentsPair.second};
		std::vector<unsigned int>::iterator it;

		PointEquation p = PointEquation(x, y);
		for (it = newSegments.begin(); it != newSegments.end(); it++) {
			SegmentShape segment = shapes.getSegment(*it);
			if (segment.liesOn(p)) {
				return clickOnSegment(*it, x, y);
			}
		}

		std::cout << "PO FORZE. ZARAZ NIC NIE ZWROCE. TEN ODCINEK JEST ZA MALY" << std::endl;
		throw(InvalidOrMeaninglessArgumentsException());
	}
	else {
		SegmentShape segment = shapes.getSegment(id);

		PointEquation newPointE = PointEquation(x, y);
		newPointE = segment.getCenteredPoint(newPointE);

		PointShape end1 = segment.getEnd1();
		PointShape end2 = segment.getEnd2();
		PointShape newPoint = PointShape(newPointE);

		unsigned int newPointId = createPoint(newPoint.getX(), newPoint.getY(), false);

		deleteShapeFunction(id);

		unsigned int lineId = lineEquationsIds.at(segment.getStringHash());

		std::map<unsigned int, std::vector<unsigned int>>::iterator mIt = pointsOnLines.find(lineId);
		std::vector<unsigned int>::iterator vIt;

		if (segment.getType() == LineEquation::LineType::VERTICAL) {
			for (vIt = mIt->second.begin(); vIt != mIt->second.end(); vIt++) {
				PointShape p1 = shapes.getPoint(*vIt);
				PointShape p2 = shapes.getPoint(*(vIt + 1));

				if (y > p1.getY() && y < p2.getY()) {
					mIt->second.insert(vIt + 1, newPointId);
					break;
				}
			}
		}
		else {
			for (vIt = mIt->second.begin(); vIt != mIt->second.end(); vIt++) {
				PointShape p1 = shapes.getPoint(*vIt);
				PointShape p2 = shapes.getPoint(*(vIt + 1));

				if (x > p1.getX() && x < p2.getX()) {
					mIt->second.insert(vIt + 1, newPointId);
					break;
				}
			}
		}

		unsigned int newSegment1Id = shapes.addSegment(end1, segment.getEnd1Id(), newPoint, newPointId).first;
		unsigned int newSegment2Id = shapes.addSegment(end2, segment.getEnd2Id(), newPoint, newPointId).first;

		drawSegmentFunction(newSegment1Id, end1.getX(), end1.getY(), newPoint.getX(), newPoint.getY());
		drawSegmentFunction(newSegment2Id, end2.getX(), end2.getY(), newPoint.getX(), newPoint.getY());
		
		shapes.deleteSegment(id, newSegment1Id, newSegment2Id);

		mIt = segmentsOnLines.find(lineId);
		for (vIt = mIt->second.begin(); vIt != mIt->second.end(); vIt++) {
			if (*vIt == id) {
				break;
			}
		}

		std::vector<unsigned int> newIds = { newSegment1Id , newSegment2Id };
		mIt->second.insert(vIt, newIds.begin(), newIds.end());

		for (vIt = mIt->second.begin(); vIt != mIt->second.end(); vIt++) {
			if (*vIt == id) {
				break;
			}
		}
		mIt->second.erase(vIt);

		std::vector<unsigned int> resultIds{ newPointId, newSegment1Id, newSegment2Id };

		//displayPointsAndSegmentsOnLines();

		return resultIds;
	}
}

unsigned int Manager::clickOnCircle(unsigned int id, double x, double y) {
	PointEquation newPoint = PointEquation(x, y);
	CircleShape circle = shapes.getCircle(id);
	PointShape newNewPoint = circle.getCenteredPoint(newPoint);
	
	unsigned int newPointId = createPoint(newNewPoint.getX(), newNewPoint.getY(), false);
	shapes.addIncludedPointToCircle(id, newPointId);

	return newPointId;
}

void Manager::findIntersectionPointsWithLine(unsigned int lineId, std::vector<unsigned int> segmentIds) {
	LineEquation lineEquation = lineEquations.at(lineId);

	std::vector<PointShape>::iterator cPit, startIt, endIt;
	std::map<unsigned int, LineEquation>::iterator mIt;
	std::vector<unsigned int>::iterator vIt;

	int intersectionPointsNumber;
	PointEquation intersectionPoints[2];
	
	bool t1, t2;
	int id1, id2;
	
	for (mIt = lineEquations.begin(); mIt != lineEquations.end(); mIt++) {
		if (mIt->first != lineId) {
			LineEquation currentLineEquation = mIt->second;
			intersectionPointsNumber = IntersectionPoints::ofLines(lineEquation, currentLineEquation, intersectionPoints);
			
			if (intersectionPointsNumber == 1) {
				t1 = false;
				t2 = false;

				for (vIt = segmentIds.begin(); vIt != segmentIds.end(); vIt++) {
					SegmentShape currentSegment = shapes.getSegment(*vIt);
					if (currentSegment.liesOn(intersectionPoints[0])) {
						id1 = *vIt;
						t1 = true;
						break;
					}
				}

				for (vIt = segmentsOnLines.at(mIt->first).begin(); vIt != segmentsOnLines.at(mIt->first).end(); vIt++) {
					SegmentShape currentSegment = shapes.getSegment(*vIt);
					if (currentSegment.liesOn(intersectionPoints[0])) {
						id2 = *vIt;
						t2 = true;
						break;
					}
				}

				if (t1 && t2) {
					try {
						clickOnSegment(id2, intersectionPoints[0].getX(), intersectionPoints[0].getY());
					}
					catch(...) {}
				}
			}
		}
	}

	std::map<unsigned int, CircleShape>::const_iterator cIt, startcIt, endcIt;
	shapes.getIteratorBoundsOfCirclesMap(startcIt, endcIt);

	for (cIt = startcIt; cIt != endcIt; cIt++) {
		CircleShape circle = cIt->second;
		intersectionPointsNumber = IntersectionPoints::ofLineAndCircle(lineEquation, circle, intersectionPoints);

		for (int i = 0; i < intersectionPointsNumber; i++) {
			for (vIt = segmentIds.begin(); vIt != segmentIds.end(); vIt++) {
				SegmentShape s = shapes.getSegment(*vIt);
				if (s.liesOn(intersectionPoints[i])) {
					clickOnCircle(cIt->first, intersectionPoints[i].getX(), intersectionPoints[i].getY());
				}
			}
		}
	}
}

void Manager::findIntersectionPointsWithCircle(unsigned int circleId) {
	CircleEquation circle = (CircleEquation)shapes.getCircle(circleId);

	std::vector<std::pair<unsigned int, std::pair<double, double>>> pointsToCreate;
	std::vector<std::pair<unsigned int, std::pair<double, double>>>::iterator ptcIt;

	std::map<unsigned int, CircleShape>::const_iterator cIt, cItStart, cItEnd;
	shapes.getIteratorBoundsOfCirclesMap(cItStart, cItEnd);

	PointEquation intersectionPoints[2];
	int intersectionPointsNumber;

	for (cIt = cItStart; cIt != cItEnd; cIt++) {
		if (cIt->first == circleId) {
			continue;
		}

		CircleEquation c = cIt->second;

		intersectionPointsNumber = IntersectionPoints::ofCircles(circle, c, intersectionPoints);
		for (int i = 0; i < intersectionPointsNumber; i++) {
			clickOnCircle(circleId, intersectionPoints[i].getX(), intersectionPoints[i].getY());
			clickOnCircle(cIt->first, intersectionPoints[i].getX(), intersectionPoints[i].getY());
		}
	}

	std::map<unsigned int, LineEquation>::iterator mIt;
	std::vector<unsigned int>::iterator vIt;


	for (mIt = lineEquations.begin(); mIt != lineEquations.end(); mIt++) {
		intersectionPointsNumber = IntersectionPoints::ofLineAndCircle(mIt->second, circle, intersectionPoints);

		pointsToCreate = {};

		for (int i = 0; i < intersectionPointsNumber; i++) {
			for (vIt = segmentsOnLines.at(mIt->first).begin(); vIt != segmentsOnLines.at(mIt->first).end(); vIt++) {
				SegmentShape s = shapes.getSegment(*vIt);
				if (s.liesOn(intersectionPoints[i])) {
					pointsToCreate.push_back({ *vIt, {intersectionPoints[i].getX(), intersectionPoints[i].getY()} });
					clickOnCircle(circleId, intersectionPoints[i].getX(), intersectionPoints[i].getY());
				}
			}
		}
		
		for (ptcIt = pointsToCreate.begin(); ptcIt != pointsToCreate.end(); ptcIt++) {
			try {
				clickOnSegment(ptcIt->first, ptcIt->second.first, ptcIt->second.second);
			}
			catch(...) {}
		}
	}
}

unsigned int Manager::createPerpendicularLine(LineEquation& lineEquation, unsigned int pointId) {
	PointEquation point = shapes.getPoint(pointId);
	unsigned int newLineEquationId;

	if(lineEquation.getType() == LineEquation::LineType::VERTICAL) {
		if(point.getX() <= offset) {
			unsigned int bottomPointId = createPoint(canvasWidth - offset, point.getY(), true);
			newLineEquationId = createSegment(bottomPointId, pointId, true);
		}
		else if(point.getX() >= canvasWidth - offset) {
			unsigned int topPointId = createPoint(offset, point.getY(), true);
			newLineEquationId = createSegment(topPointId, pointId, true);
		}
		else {
			unsigned int bottomPointId = createPoint(canvasWidth - offset, point.getY(), true);
			newLineEquationId = createSegment(bottomPointId, pointId, true);
			unsigned int topPointId = createPoint(offset, point.getY(), true);
			newLineEquationId = createSegment(topPointId, pointId, true);
		}
	}
	else if(lineEquation.getType() == LineEquation::LineType::HORIZONTAL) {
		if(point.getY() <= offset) {
			unsigned int bottomPointId = createPoint(point.getX(), canvasHeight - offset, true);
			newLineEquationId = createSegment(bottomPointId, pointId, true);
		}
		else if(point.getY() >= canvasHeight - offset) {
			unsigned int topPointId = createPoint(point.getX(), offset, true);
			newLineEquationId = createSegment(topPointId, pointId, true);
		}
		else {
			unsigned int bottomPointId = createPoint(point.getX(), canvasHeight - offset, true);
			newLineEquationId = createSegment(bottomPointId, pointId, true);
			unsigned int topPointId = createPoint(point.getX(), offset, true);
			newLineEquationId = createSegment(topPointId, pointId, true);
		}
	}
	else {
		double calculatedA = -1.0 / lineEquation.geta();
		if (calculatedA > Constans::MAXIMAL_A_VALUE) {
			calculatedA = Constans::MAXIMAL_A_VALUE;
		}
		else if (calculatedA < -Constans::MAXIMAL_A_VALUE) {
			calculatedA = -Constans::MAXIMAL_A_VALUE;
		}

		double calculatedB = point.getY() - calculatedA * point.getX();

		std::vector<unsigned int> creatingPoints;

		if(offset < point.getX()) {
			double leftPointX = offset;
			double leftPointY = calculatedA * offset + calculatedB;

			if(leftPointY < offset) {
				leftPointX = (offset - calculatedB) / calculatedA;
				leftPointY = offset;
			}
			else if(leftPointY > canvasHeight - offset) {
				leftPointX = (canvasHeight - offset - calculatedB) / calculatedA;
				leftPointY = canvasHeight - offset;
			}

			unsigned int leftPointId = createPoint(leftPointX, leftPointY, true);
			creatingPoints.push_back(leftPointId);
			
		}
		creatingPoints.push_back(pointId);
		if(canvasWidth - offset > point.getX()) {
			double rightPointX = canvasWidth - offset;
			double rightPointY = calculatedA * (canvasWidth - offset) + calculatedB;

			if(rightPointY < offset) {
				rightPointX = (offset - calculatedB) / calculatedA;
				rightPointY = offset;
			}
			else if(rightPointY > canvasHeight - offset) {
				rightPointX = (canvasHeight - offset - calculatedB) / calculatedA;
				rightPointY = canvasHeight - offset;
			}

			unsigned int rightPointId = createPoint(rightPointX, rightPointY, true);
			creatingPoints.push_back(rightPointId);
		}

		for (int i = 0; i < (creatingPoints.size() - 1); i++) {
			newLineEquationId = createSegment(creatingPoints[i], creatingPoints[i + 1], true);
		}
	}

	return newLineEquationId;
}

unsigned int Manager::createParallelLine(LineEquation& lineEquation, unsigned int pointId) {
	PointEquation point = shapes.getPoint(pointId);
	unsigned int newLineEquationId;

	if(lineEquation.getType() == LineEquation::LineType::VERTICAL) {
		if(point.getY() <= offset) {
			unsigned int bottomPointId = createPoint(point.getX(), canvasHeight - offset, true);
			newLineEquationId = createSegment(bottomPointId, pointId, true);
		}
		else if(point.getY() >= canvasHeight - offset) {
			unsigned int topPointId = createPoint(point.getX(), offset, true);
			newLineEquationId = createSegment(topPointId, pointId, true);
		}
		else {
			unsigned int bottomPointId = createPoint(point.getX(), canvasHeight - offset, true);
			newLineEquationId = createSegment(bottomPointId, pointId, true);
			unsigned int topPointId = createPoint(point.getX(), offset, true);
			newLineEquationId = createSegment(topPointId, pointId, true);
		}
	}
	else if(lineEquation.getType() == LineEquation::LineType::HORIZONTAL) {
		if(point.getX() <= offset) {
			unsigned int bottomPointId = createPoint(canvasWidth - offset, point.getY(), true);
			newLineEquationId = createSegment(bottomPointId, pointId, true);
		}
		else if(point.getX() >= canvasWidth - offset) {
			unsigned int topPointId = createPoint(offset, point.getY(), true);
			newLineEquationId = createSegment(topPointId, pointId, true);
		}
		else {
			unsigned int bottomPointId = createPoint(canvasWidth - offset, point.getY(), true);
			newLineEquationId = createSegment(bottomPointId, pointId, true);
			unsigned int topPointId = createPoint(offset, point.getY(), true);
			newLineEquationId = createSegment(topPointId, pointId, true);
		}
	}
	else {
		double calculatedA = lineEquation.geta();
		double calculatedB = point.getY() - lineEquation.geta() * point.getX();

		std::vector<unsigned int> creatingPoints;

		if(offset < point.getX()) {
			double leftPointX = offset;
			double leftPointY = calculatedA * offset + calculatedB;

			if(leftPointY < offset) {
				leftPointX = (offset - calculatedB) / calculatedA;
				leftPointY = offset;
			}
			else if(leftPointY > canvasHeight - offset) {
				leftPointX = (canvasHeight - offset - calculatedB) / calculatedA;
				leftPointY = canvasHeight - offset;
			}

			unsigned int leftPointId = createPoint(leftPointX, leftPointY, true);
			creatingPoints.push_back(leftPointId);
			
		}
		creatingPoints.push_back(pointId);
		if(canvasWidth - offset > point.getX()) {
			double rightPointX = canvasWidth - offset;
			double rightPointY = calculatedA * (canvasWidth - offset) + calculatedB;

			if(rightPointY < offset) {
				rightPointX = (offset - calculatedB) / calculatedA;
				rightPointY = offset;
			}
			else if(rightPointY > canvasHeight - offset) {
				rightPointX = (canvasHeight - offset - calculatedB) / calculatedA;
				rightPointY = canvasHeight - offset;
			}

			unsigned int rightPointId = createPoint(rightPointX, rightPointY, true);
			creatingPoints.push_back(rightPointId);
		}

		for (int i = 0; i < (creatingPoints.size() - 1); i++) {
			newLineEquationId = createSegment(creatingPoints[i], creatingPoints[i + 1], true);
		}
	}

	return newLineEquationId;
}

std::vector<unsigned int> Manager::divideSegmentId(unsigned int segmentId, unsigned int n) {
	if (n < 2) {
		return std::vector<unsigned int>{};
	}

	SegmentShape segment = shapes.getSegment(segmentId);
	PointShape end1 = segment.getEnd1();
	PointShape end2 = segment.getEnd2();

	double dx = (end2.getX() - end1.getX()) / n;
	double dy = (end2.getY() - end1.getY()) / n;

	std::vector<unsigned int> availableToClick{ segmentId };
	std::vector<unsigned int> points{ segment.getEnd1Id() };

	std::vector<unsigned int>::iterator iIt;

	double x = end1.getX() + dx;
	double y = end1.getY() + dy;

	for (int i = 0; i < n - 1; i++) {
		PointEquation p = PointEquation(x, y);
		for (iIt = availableToClick.begin(); iIt != availableToClick.end(); iIt++) {
			SegmentShape s = shapes.getSegment(*iIt);
			if (s.liesOn(p)) {
				availableToClick = clickOnSegment(*iIt, x, y);
				points.push_back(availableToClick.at(0));
				std::reverse(availableToClick.begin(), availableToClick.end());
				break;
			}
		}

		x += dx;
		y += dy;
	}

	points.push_back(segment.getEnd2Id());

	return points;
}

std::vector<unsigned int> Manager::divideSegmentEnds(unsigned int end1Id, unsigned int end2Id, unsigned int n) {
	if (n < 2) {
		return std::vector<unsigned int>{};
	}

	PointShape end1 = shapes.getPoint(end1Id);
	PointShape end2 = shapes.getPoint(end2Id);

	double dx = (end2.getX() - end1.getX()) / n;
	double dy = (end2.getY() - end1.getY()) / n;

	unsigned int lineEquationId = lineEquationsIds.at(LineEquation(end1, end2).getStringHash());

	std::vector<PointEquation> pointsToCreate{};

	for (int i = 1; i < n; i++) {
		pointsToCreate.push_back(PointEquation(end1.getX() + i * dx, end1.getY() + i * dy));
	}

	std::vector<unsigned int> points{ end1Id };

	std::vector<PointEquation>::iterator pIt;
	std::vector<unsigned int>::iterator iIt;

	
	for (pIt = pointsToCreate.begin(); pIt != pointsToCreate.end(); pIt++) {
		bool t = true;
		try {
			std::vector<unsigned int> segments = segmentsOnLines.at(lineEquationId);
			for (iIt = segments.begin(); iIt != segments.end(); iIt++) {
				SegmentShape s = shapes.getSegment(*iIt);
				if (s.liesOn(*pIt)) {
					t = false;
					std::vector<unsigned int> clickResult = clickOnSegment(*iIt, (*pIt).getX(), (*pIt).getY());
					points.push_back(clickResult.at(0));
				}
			}
		}
		catch(...) {

		}

		if (t) {
			int newPointId = createPoint((*pIt).getX(), (*pIt).getY(), true);
			points.push_back(newPointId);
		}
	}

	points.push_back(end2Id);

	return points;
}

std::vector<std::pair<unsigned int, PointEquation>> Manager::sortVerticesClockwise(std::vector<std::pair<unsigned int, PointEquation>>& vertices) {
	int n = vertices.size();

	double meanCenterX = 0.0;
	double meanCenterY = 0.0;
	for(int i = 0; i<n; i++) {
		meanCenterX += vertices[i].second.getX();
		meanCenterY += vertices[i].second.getY();
	}

	meanCenterX /= n;
	meanCenterY /= n;

	std::vector<std::pair<unsigned int, PointEquation>> newVertices;
	for(int i = 0; i<n; i++) {
		newVertices.push_back({vertices[i].first, PointEquation(vertices[i].second.getX() - meanCenterX, vertices[i].second.getY() - meanCenterY)});
	}

	sort(newVertices.begin(), newVertices.end(), [](std::pair<unsigned int, PointEquation>& a, std::pair<unsigned int, PointEquation>& b) { 
		if(a.second.getX() >= 0 && b.second.getX() < 0) {
			return true;
		}
		else if(a.second.getX() < 0 && b.second.getX() >= 0) {
			return false;
		}
		else if(a.second.getX() == 0 && b.second.getX() == 0) {
			if (a.second.getY() >= 0 || b.second.getY() >= 0) {
				return a.second.getY() > b.second.getY();
			}
			else {
				return b.second.getY() > a.second.getY();
			}	
		}

		double det = (a.second.getX()) * (b.second.getY()) - (b.second.getX()) * (a.second.getY());
		if (det < 0) {
			return true;
		}
		if (det > 0) {
			return false;
		}

		double d1 = (a.second.getX()) * (a.second.getX()) + (a.second.getY()) * (a.second.getY());
		double d2 = (b.second.getX()) * (b.second.getX()) + (b.second.getY()) * (b.second.getY());

		return d1 > d2;
	});

	std::vector<std::pair<unsigned int, PointEquation>>sortedPoints;
	for(int i = 0; i<n; i++) {
		sortedPoints.push_back({newVertices[i].first, PointEquation(newVertices[i].second.getX() + meanCenterX, newVertices[i].second.getY() + meanCenterY)});
	}

	return sortedPoints;
}

void Manager::errorNotForeseen() {
	alertFunction(4, "Sorry. I did not foresee this error. This will certainly be well handled in the future. Errare humanum est.");
}