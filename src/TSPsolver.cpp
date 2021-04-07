#include <TSPsolver.h>

void TSPsolver::addNode(double x, double y, NodeColor color) {
    nodes.push_back(Point2D(x,y,color));
}

int TSPsolver::parseCSV(std::string file) {
    std::ifstream ifs(file);
    if (ifs.fail()) return 1;
    nodes.clear();
    std::string data;
    Point2D node;
    while (std::getline(ifs, data)) {
        std::istringstream iss(data);
        std::getline(iss, data, ',');
        node.x = std::stod(data);
        std::getline(iss, data, ',');
        node.y = std::stod(data);
        std::getline(iss, data, ',');
        if(std::stoi(data) == NodeColor::yellow || NodeColor::blue) {
            node.color = (NodeColor)std::stoi(data);
            nodes.push_back(node);
        }
    }
    ifs.close();
    if (nodes.size() == 0) return 1;

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(nodes), std::end(nodes), rng);

    return 0;
}

std::vector<Point2D> TSPsolver::getNodes() {
    return nodes;
}

float TSPsolver::E() {
    float dist_trav=0;
    for (int i = 0; i < nodes.size()-1; ++i)
        dist_trav+=nodes.at(i).distanceFrom(nodes.at(i+1));
    dist_trav+=nodes.at(nodes.size()-1).distanceFrom(nodes.at(0));
    return dist_trav;
}

void TSPsolver::swapping(unsigned int idx1, unsigned int idx2) {
    std::vector<Point2D> tmp;
    for (int i = idx1+1; i < idx2+1; ++i)
        tmp.push_back(nodes.at(i));
    for (int i = idx2; i > idx1; --i)
        nodes.at(i)=tmp.at(-i+idx2);
}

void TSPsolver::solve(float T0, int nsteps) {
    if (nodes.size() == 0) return;

    srand (time(NULL));

    float oldE = E();
    
    std::vector<float> array;
    for (int i = 0; i < nsteps; ++i)
        array.push_back(T0-(T0 / nsteps * i));

    for (float T: array) {
        unsigned int idx1 = rand() % nodes.size()-2;
        unsigned int idx2 = rand() % (nodes.size()-(idx1 + 2)) + idx1 + 2;
        swapping(idx1, idx2);
        float newE=E();
        if (newE>oldE) {
            if (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)) > exp(-(newE - oldE) / T)) {
                swapping(idx1, idx2);
                newE = oldE;
            }                
        }
        oldE = newE;
    }   
}

