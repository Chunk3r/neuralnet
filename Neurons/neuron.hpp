#ifndef neuron_hpp
#define neuron_hpp

#include <vector>
#include <cstdio>
#include <iostream>
#include <random>

class Neuron{

public:
    Neuron(int x, int y, int z);
    Neuron(int x, int y, int z, int r, double th, double po);
    void addNeighbor(Neuron* n, double w);
    void addNeighbor(Neuron* n);
    void addPotential(double p);
    int getRadius();
    int xPos();
    int yPos();
    int zPos();
    void propertiesToStream(std::ostream out);
    void neighborsToStream(std::ostream out);

private:
    int _radius;
    int _x;
    int _y;
    int _z;
    double _membranePotential;
    double _membraneThreshold;
    std::vector<Neuron*> _neighbors;
    std::vector<double> _weights;
    void fire();
    void resetMembrane();
};

#endif
