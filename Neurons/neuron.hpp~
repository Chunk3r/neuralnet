#ifndef neuron_hpp
#define neuron_hpp

#include <vector>

class Neuron{

public:
  Neuron(int x, int y, int z);
  void addNeighbor(Neuron* n, double w);
  void addPotential(double p);
  int getRadius();
  int xPos();
  int yPos();
  int zPos();

private:
  int radius;
  int x;
  int y;
  int z;
  double membranePotential;
  double membraneThreshold;
  double weight;//-1 <= w <= 1
  std::vector<Neuron*> neighbors;
  std::vector<double> weights;
  void fire();
  void resetMembrane();
};

#endif
