#ifndef filehandling_hpp
#define filehandling_hpp

#include <cstdlib>

class Filehandling{

public:
  void writePositions(char* name, int* pos);
  void writeWeights(char* name, int* weights);
  int* readPositions(char* name);
  int* readWeights(char* name);
}
