#ifndef filehandling_hpp
#define filehandling_hpp

#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include "network.hpp"

class Filehandling{

public:
  void write(char* fname, Network::Network* net);
  void writePositions(char* name, int* pos);
  void writeWeights(char* name, double* weights);
  int* readPositions(char* name);
  double* readWeights(char* name);
};
#endif
