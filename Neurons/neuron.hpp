#ifndef neuron_hpp
#define neuron_hpp

#include <vector>
#include <cstdio>
#include <random>

class Neuron{

public:
  Neuron(int x, int y, int z);
  void addNeighbor(Neuron* n, double w);
  void addNeighbor(Neuron* n);
  void addPotential(double p);
  int getRadius();
  int xPos();
  int yPos();
  int zPos();
  friend std::ostream operator<<(std::ostream out, Neuron n);

private:
  int radius;
  int x;
  int y;
  int z;
  double membranePotential;
  double membraneThreshold;
  double weight;//0 <= w < 1
  std::vector<Neuron*> neighbors;
  std::vector<double> weights;
  void fire();
  void resetMembrane();
};

#endif
