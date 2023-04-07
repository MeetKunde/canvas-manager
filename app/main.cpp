#include <iostream>

#include "./../inc/manager/Manager.h"

using namespace std;

double WIDTH = 900.0;
double HEIGHT = 900.0;
double OFFSET = 10.0;

void drawPoint(int id, double x, double y) {
	cout << "draw new point  ID = " << id << "  X = " << x << "  Y = " << y << endl;
}

void drawSegment(int id, double x1, double y1, double x2, double y2) {
	cout << "draw new segment  ID = " << id << "  X1 = " << x1 << "  Y1 = " << y1 << "  X2 = " << x2 << "  Y2 = " << y2 << endl;
}

void drawCicle(int id, double x, double y, double r) {
	cout << "draw new circle  ID = " << id << "  X = " << x << "  Y = " << y << "  R = " << r << endl;
}

void deleteShape(int id) {
	cout << "delete shape  ID = " << id << endl;
}

void setPromptingPoint(int set, double x, double y) {
	cout << "set prompting point  SET = " << set << "  X = " << x << "  Y = " << y << endl;
}

void processingCompleted() {
	cout << "processing complete" << endl;
}

void alert(int type, const char* message) {
	cout << "ALERT - " << type << ": " << message << endl;
}

double randomDouble(double maxi, double mini) {
	float r = (double)rand() / (double)RAND_MAX;

	return mini + r * (maxi - mini);
}

Manager manager = Manager(WIDTH, HEIGHT, OFFSET, &drawPoint, &drawSegment, &drawCicle, &deleteShape, &setPromptingPoint, &processingCompleted, &alert);

/*
* Clicking on canvas.
*/
void test1(int count) {
	manager.setCurrentlyCreatedShape(Manager::ShapeToCreate::POINT);

	double randomX, randomY;
	for (int i = 0; i < count; i++) {
		randomX = randomDouble(0, WIDTH);
		randomY = randomDouble(0, HEIGHT);

		manager.clickedOnCanvas(randomX, randomY);
	}
}

int main(int argc, char* argv[]) {
    std::cout << "Hello World. I'm Canvas Manager!" << std::endl;

    test1(1);

    return 0;
}