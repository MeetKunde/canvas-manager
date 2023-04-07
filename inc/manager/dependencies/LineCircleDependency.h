#ifndef LINE_CIRCLE_DEPENDENCY_H
#define LINE_CIRCLE_DEPENDENCY_H

#include <ostream>

class LineCircleDependency {
private:
    unsigned int lineId;
    unsigned int circleId;

public:
    LineCircleDependency(unsigned int line, unsigned int circle);
    LineCircleDependency(const LineCircleDependency& lineCircleDependency);

    LineCircleDependency& operator=(const LineCircleDependency& lineCircleDependency);

    unsigned int getLineId() const { return lineId; }
    unsigned int getCircleId() const { return circleId; }

    friend bool operator== (const LineCircleDependency& lcd1, const LineCircleDependency& lcd2);
    friend bool operator!= (const LineCircleDependency& lcd1, const LineCircleDependency& lcd2);

    friend std::ostream& operator<< (std::ostream& stream, const LineCircleDependency& lineCircleDependency);
};

#endif /* LINE_CIRCLE_DEPENDENCY_H */