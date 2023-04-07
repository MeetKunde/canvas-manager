#!/bin/bash

source ./../../../emsdk/emsdk_env.sh

em++ -std=c++17 --bind --no-entry -fsanitize=undefined -sWASM=1 -sALLOW_TABLE_GROWTH -sEXPORTED_RUNTIME_METHODS=addFunction,UTF8ToString -sNO_DISABLE_EXCEPTION_CATCHING \
./src/math/equations/PointEquation.cpp \
./src/math/equations/LineEquation.cpp \
./src/math/equations/CircleEquation.cpp \
./src/math/Constans.cpp \
./src/math/SystemOf2LinearEquations.cpp \
./src/math/QuadraticEquation.cpp \
./src/math/Distance.cpp \
./src/figures-creating/Lines.cpp \
./src/figures-creating/Circles.cpp \
./src/figures-creating/IntersectionPoints.cpp \
./src/manager/shapes/PointShape.cpp \
./src/manager/shapes/SegmentShape.cpp \
./src/manager/shapes/CircleShape.cpp \
./src/manager/dependencies/OrderedPair.cpp \
./src/manager/dependencies/Angle.cpp \
./src/manager/dependencies/LinesDependency.cpp \
./src/manager/dependencies/CirclesDependency.cpp \
./src/manager/dependencies/SegmentsDependency.cpp \
./src/manager/dependencies/AnglesDependency.cpp \
./src/manager/dependencies/LineAngleDependency.cpp \
./src/manager/dependencies/LineCircleDependency.cpp \
./src/manager/dependencies/LineSegmentDependency.cpp \
./src/manager/dependencies/PolygonCircleDependency.cpp \
./src/manager/dependencies/PolygonTypeDependency.cpp \
./src/manager/dependencies/SegmentArmsDependency.cpp \
./src/manager/dependencies/SegmentLength.cpp \
./src/manager/dependencies/AngleValue.cpp \
./src/manager/ShapesManager.cpp \
./src/manager/DependenciesManager.cpp \
./src/manager/Manager.cpp \
app/to-wasm-converter.cpp -o ./../web-application/backend/static/canvasManager.js
