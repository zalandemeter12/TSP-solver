#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <time.h>
#include <math.h>

#include <algorithm>
#include <random>

enum NodeColor {
    orange = 0, blue = 1, yellow = 2, red = 3
};

struct Point2D {
    double x, y;
    NodeColor color;
    Point2D (double x = 0, double y = 0, NodeColor color = NodeColor::blue) :x(x), y(y), color(color) {}
    double distanceFrom(Point2D p) {return sqrt(pow((abs(x-p.x)),2)+pow(abs(y-p.y),2));}
};

class TSPsolver {
private:
    std::vector<Point2D> nodes;
public:
    TSPsolver() {}
    ~TSPsolver() {}

    void addNode(double x, double y, NodeColor color);
    float E();
    void swapping(unsigned int idx1, unsigned int idx2);
    void solve(float T0 = 1, int nsteps = 10000);
    int parseCSV(std::string file);
    std::vector<Point2D> getNodes();
};

#endif