#ifndef CONSTANS_H
#define CONSTANS_H

/**
 * @brief Class containing constants used in mathematical calculations
 */
class Constans {
public:
	/**
	 * @brief Constant for comparing numbers with a possible big discrepancy 
	 */
	static const double BIG_EPSILON;

	/**
	 * @brief Constant for comparing numbers with a possible normal discrepancy 
	 */
	static const double NORMAL_EPSILON;

	/**
	 * @brief Constant for comparing numbers with a possible small discrepancy 
	 */
	static const double SMALL_EPSILON;

	/**
	 * @brief Constant defining maximal value of coefficient of x in line equation
	 */
	static const double MAXIMAL_A_VALUE;

	/**
	 * @brief Constant defining minimal value of coefficient of x in line equation
	 */
	static const double MINIMAL_A_VALUE;
};

#endif /* CONSTANS_H */