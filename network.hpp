#ifndef network_hpp
#define network_hpp

#include "Neurons/neuron.hpp"
#include "tokenizer.hpp"
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <cstdio>

class Network{

public:
    Network(int l, int h, int w);
    Network(const char* fname);
    void populate();
    void populate(int* positions);
    void connectNeurons(Neuron* n);
    Neuron* getNeuron(int x, int y, int z);
    int getLength();
    int getHeight();
    int getWidth();
    void toFile(const char* fname);

private:
    int isInBounds(int i, int j, int k);
    int isValidNeighbor(int i, int j, int k, int x, int y, int z);
    bool isValidPos(int x, int y, int z, int* pos);
    double rndmWeight();//needs to be done in neuron
    int _length;
    int _height;
    int _width;
    std::vector<std::vector<std::vector<Neuron>>> _neurons;
    int* extractNeurons();
    double* extractWeights();
    void initFromFile(int* pos);

};

#endif
