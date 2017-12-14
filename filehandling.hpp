#ifndef filehandling_hpp
#define filehandling_hpp

#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <stdio.h>

class Filehandling{

public:
  void writePositions(char* name, int* pos);
  void writeWeights(char* name, double* weights);
  int* readPositions(char* name);
  double* readWeights(char* name);
};
#endif
