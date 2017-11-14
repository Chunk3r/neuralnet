#ifndef network_hpp
#define network_hpp
//Network ist eine Datenstruktur mit drei dimensionen,
//in ihm werden die Neuronen gespeichert.

#include "neuron.hpp"
#include <vector>
#include <array>
#include <cstdio>
#include <cstdlib>

class Network{

public:
  Network(int l, int h, int w);
  void populate();
  void push_back(std::vector<std::vector<std::vector<Neuron>>>* vp, Neuron n);
  //void populateWithDna(File* input);
  void connectNeurons(Neuron* n);
  Neuron* getNeuron(int x, int y, int z);
  int getLength();
  int getHeight();
  int getWidth();

private:
  int isInBounds(int i, int j, int k);
  double rndmWeight();
  int length;
  int height;
  int width;
  std::vector<std::vector<std::vector<Neuron>>> v;
  int[][] extractNeurons();

};

#endif
