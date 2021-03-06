#ifndef network_hpp
#define network_hpp
//Network ist eine Datenstruktur mit drei dimensionen,
//in ihm werden die Neuronen gespeichert.

#include "Neurons/neuron.hpp"
#include "filehandling.hpp"
#include <vector>
#include <array>
#include <cstdio>
#include <stdio.h>
#include <cstdlib>

class Network{

public:
  Network(int l, int h, int w);
  Network(int* pos, double* weights);
  void populate();
  void populate(int* pos);
  void push_back(std::vector<std::vector<std::vector<Neuron>>>* vp, Neuron n);
  void connectNeurons(Neuron* n);
  Neuron* getNeuron(int x, int y, int z); //for debugging
  int getLength();
  int getHeight();
  int getWidth();
  void input(std::vector<int> in);
  void save(char* posFileName, char* wFileName);
  void load(char* posFileName, char* wFileName);
  void save();//if no name is defined use default
  void load();

private:
  int isInBounds(int i, int j, int k);
  int isValidNeighbor(int i, int j, int k, int x, int y, int z);
  bool isValidPos(int x, int y, int z, int* pos);
  double rndmWeight();//needs to be done in neuron
  int length;
  int height;
  int width;
  std::vector<std::vector<std::vector<Neuron>>> v;
  int* extractNeurons();
  void initFromFile(int* pos);

};

#endif
