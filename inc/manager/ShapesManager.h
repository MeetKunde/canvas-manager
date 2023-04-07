#ifndef SHAPES_MANAGER_H
#define SHAPES_MANAGER_H

#include "./shapes/PointShape.h"
#include "./shapes/SegmentShape.h"
#include "./shapes/CircleShape.h"

#include "./../json.h"

#include <vector>
#include <map>

using json = nlohmann::json;

/**
 * @brief Class managing shapes(points, circles, segments)
 */
class ShapesManager {
private:
	/**
	 * @brief ID to set for the next created shape 
	 */
	unsigned int idCounter;

	/**
	 * @brief Map od points. Key is a point ID. Value is a point object
	 * 
	 * It is not possible to delete an already added shape
	 */
	std::map<unsigned int, PointShape> points;

	/**
	 * @brief Map od circles. Key is a circle ID. Value is a circle object
	 * 
	 * It is not possible to delete an already added shape
	 */
	std::map<unsigned int, CircleShape> circles;

	/**
	 * @brief Map od segments. Key is a segment ID. Value is a segment object
	 * 
	 * It is not possible to delete an already added shape 
	 */
	std::map<unsigned int, SegmentShape> segments;

	/**
	 * @brief Map od segments. Key is a segment ID. Value is a segment object
	 * 
	 * Removal of segment is performed at this object 
	 */
	std::map<unsigned int, SegmentShape> segmentsWithDeletions;

	/**
	 * @brief Map representing subdivisions of segments into smaller ones which make up the whole segment 
	 */
	std::map<unsigned int, std::pair<unsigned int, unsigned int>> deletedSegmentsMap;

	/**
	 * @brief Set with IDs of segments which was removed
	 */
	std::set<unsigned int> deletedSegmentIds;

public:
	/**
	 * @brief Constructor of a new ShapesManager object
	 */
	ShapesManager();

	/**
	 * @brief Constructor of a new ShapesManager object
	 * 
	 * @param shapesManager other ShapesManager object
	 */
	ShapesManager(const ShapesManager& shapesManager);

	/**
	 * @brief Override of the assignment operator
	 * 
	 * @param shapesManager object to be assigned 
	 * @return new ShapesManager object
	 */
    ShapesManager& operator=(const ShapesManager& shapesManager);

	/**
	 * @brief Current shapes ID counter value getter
	 * 
	 * @return current value of shapes ID counter
	 */
	unsigned int getIdCounter() const { return idCounter; }

	/**
	 * @brief Adding new PointShape object
	 * 
	 * @param x X coordinate of new point
	 * @param y Y coordinate of new point
	 * @return pair with ID of created shape and boolean value: true if point with given coordinates has not yet existed, false otherwise
	 */
	std::pair<unsigned int, bool> addPoint(double x, double y);

	/**
	 * @brief PointShape object getter
	 * 
	 * @param id ID of point shape to get
	 * @return reference to point object with given ID
	 * @throws std::out_of_range if point with given ID does not exist
	 */
	inline const PointShape& getPoint(unsigned int id) const noexcept(false){ return points.at(id); }

	/**
	 * @brief Bounds of points map iterator getter
	 * 
	 * Function writes iterator bounds to given references
	 * 
	 * @param start reference to the variable to which to write the start of the iterator
	 * @param end reference to the variable to which to write the end of the iterator
	 */
	inline void getIteratorBoundsOfPointsMap(std::map<unsigned int, PointShape>::const_iterator& start, std::map<unsigned int, PointShape>::const_iterator& end) const { start = points.begin(); end = points.end(); }
	
	/**
	 * @brief Count of point objects getter
	 * 
	 * @return number of point objects
	 */
	inline unsigned int getPointsNumber() const { return points.size(); }

	/**
	 * @brief Getting all point as written to JSON object as JSON objects
	 * 
	 * @return JSON object with JSON objects representing points
	 */
	json getPointsAsJsonObjects() const;

	/**
	 * @brief Adding new CircleShape object
	 * 
	 * @param centerPoint reference to center point object
	 * @param centerPointId ID of center point object
	 * @param pointOnCircle reference to point object which lies on circle
	 * @param pointOnCircleId ID of point object which lies on circle
	 * @return pair with ID of created shape and boolean value: true if circle with given center point and calculated radius has not yet existed, false otherwise
	 */
	std::pair<unsigned int, bool> addCircle(PointShape& centerPoint, unsigned int centerPointId, PointShape& pointOnCircle, unsigned int pointOnCircleId);
	
	/**
	 * @brief Adding included point to circle
	 * 
	 * @param circleId ID of circle to add included point
	 * @param includedPointId ID of point to include
	 * @throws std::out_of_range if circle with given ID does not exist
	 */
	void addIncludedPointToCircle(unsigned int circleId, unsigned int includedPointId) noexcept(false) { circles.at(circleId).addIncludedPoint(includedPointId); }

	/**
	 * @brief CircleShape object getter
	 * 
	 * @param id ID of circle shape to get
	 * @return reference to circle object with given ID
	 * @throws std::out_of_range if circle with given ID does not exist
	 */
	inline const CircleShape& getCircle(unsigned int id) const noexcept(false) { return circles.at(id); }

	/**
	 * @brief Bounds of circles map iterator getter
	 * 
	 * Function writes iterator bounds to given references
	 * 
	 * @param start reference to the variable to which to write the start of the iterator
	 * @param end reference to the variable to which to write the end of the iterator
	 */
	inline void getIteratorBoundsOfCirclesMap(std::map<unsigned int, CircleShape>::const_iterator& start, std::map<unsigned int, CircleShape>::const_iterator& end) const { start = circles.begin(); end = circles.end(); }
	
	/**
	 * @brief Count of circle objects getter
	 * 
	 * @return number of circle objects
	 */
	inline unsigned int getCirclesNumber() const { return circles.size(); }

	/**
	 * @brief Getting all circles as written to JSON object as JSON objects
	 * 
	 * @return JSON object with JSON objects representing circles
	 */
	json getCirclesAsJsonObjects() const;

	/**
	 * @brief Adding new SegmentShape object
	 * 
	 * @param point1 reference to first end point object
	 * @param point1Id ID of first end point object
	 * @param point2 reference to second end point object
	 * @param point2Id ID of secind end point object
	 * @return pair with ID of created shape and boolean value: true if segment with given ends has not yet existed, false otherwise
	 */
	std::pair<unsigned int, bool> addSegment(PointShape& point1, unsigned int point1Id, PointShape& point2, unsigned int point2Id);

	/**
	 * @brief SegmentShape object getter
	 * 
	 * @param id ID of segment shape to get
	 * @return reference to segment object with given ID
	 * @throws std::out_of_range if segment with given ID does not exist
	 */
	inline const SegmentShape& getSegment(unsigned int id) const noexcept(false){ return segments.at(id); }
	
	/**
	 * @brief Bounds of segments map iterator getter
	 * 
	 * Function writes iterator bounds to given references
	 * 
	 * @param start reference to the variable to which to write the start of the iterator
	 * @param end reference to the variable to which to write the end of the iterator
	 */
	inline void getIteratorBoundsOfSegmentsMap(std::map<unsigned int, SegmentShape>::const_iterator& start, std::map<unsigned int, SegmentShape>::const_iterator& end) const { start = segmentsWithDeletions.begin(); end = segmentsWithDeletions.end(); }

	/**
	 * @brief Bounds of all segments map iterator getter
	 * 
	 * Function writes iterator bounds to given references
	 * 
	 * @param start reference to the variable to which to write the start of the iterator
	 * @param end reference to the variable to which to write the end of the iterator
	 */
	inline void getIteratorBoundsOfAllSegmentsMap(std::map<unsigned int, SegmentShape>::const_iterator& start, std::map<unsigned int, SegmentShape>::const_iterator& end) const { start = segments.begin(); end = segments.end(); }
	
	/**
	 * @brief Count of segments objects getter
	 * 
	 * @return number of segment objects
	 */
	inline unsigned int getSegmentsNumber() const { return segmentsWithDeletions.size(); }

	/**
	 * @brief Getting all segments as written to JSON object as JSON objects
	 * 
	 * @return JSON object with JSON objects representing segments
	 */
	json getSegmentsAsJsonObjects() const;

	/**
	 * @brief Deleting segment. 2 new segments come out instead
	 * 
	 * @param id ID of segment to delete
	 * @param newId1 ID of first new segment
	 * @param newId2 ID of second new segment
	 */
	void deleteSegment(unsigned int id, unsigned int newId1, unsigned int newId2);

	/**
	 * @brief Checking if shapes is deleted
	 * 
	 * @param id ID of segment to check
	 * @return true if segment with given shape is deleted
	 * @return false if segment with given shape is deleted
	 */
	inline bool isDeleted(unsigned int id) const { return deletedSegmentIds.find(id) != deletedSegmentIds.end(); } 

	/**
	 * @brief Ids from deleted segment getter
	 * 
	 * @param id ID of deleted segment
	 * @return pair of IDs which make up the deleted segment
	 */
	inline std::pair<unsigned int, unsigned int> getIdsFromDeletedSegment(unsigned int id) const { return deletedSegmentsMap.at(id); }
};

#endif /* SHAPES_MANAGER_H */