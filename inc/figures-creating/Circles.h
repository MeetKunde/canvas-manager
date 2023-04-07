#ifndef CIRCLES_H
#define CIRCLES_H

#include "./../math/equations/CircleEquation.h"
#include "./../math/equations/LineEquation.h"
#include "Lines.h"
#include "IntersectionPoints.h"

#include <vector>
#include <algorithm>

/**
 * @brief Class creating specific circle equations
 */
class Circles {
public:
	/**
	 * @brief Class implementing a custom exception used in Circles class methods 
	 * when an attempt is made to create a circle equation based on invalid points
	 */
	class InvalidPointsException : public virtual std::invalid_argument {
	public:
		/**
		 * @brief Constructor of a new InvalidPointsException object 
		 */
		InvalidPointsException() : std::invalid_argument("Not all given points lie on the same circle.") { }
	};

	/**
	 * @brief Deactivating the class constructor because the class is supposed to be static
	 */
	Circles() = delete;

	/**
	 * @brief Finding equation of circle inscribed in polygon
	 * 
	 * @param vertices reference to vector of point objects representing polygon vertices
	 * @return equation of inscribed circle 
	 * @throws InvalidPointsException if no all given points lies on the same circle
	 */
	static CircleEquation getInscribedCircle(std::vector<PointEquation>& vertices) noexcept(false);

	/**
	 * @brief Finding equation of circle circumscribed on polygon
	 * 
	 * @param vertices reference to vector of point objects representing polygon vertices
	 * @return equation of circumscribed circle
	 * @throws InvalidPointsException if no all given points lies on the same circle
	 */
	static CircleEquation getCircumscribedCircle(std::vector<PointEquation>& vertices) noexcept(false);

	/**
	 * @brief Finding equation of escribed circle 
	 * 
	 * @param sideEnd1 reference to first side end point object
	 * @param sideEnd2 reference to second side end point object
	 * @param sideEquation reference to line equation object of side
	 * @param point reference to point object opposite to side
	 * @return equation of escribed circle 
	 */
	static CircleEquation getEscribedCircle(const PointEquation& sideEnd1, const PointEquation& sideEnd2, const LineEquation& sideEquation, const PointEquation& point);
};

#endif /* CIRCLES_H */