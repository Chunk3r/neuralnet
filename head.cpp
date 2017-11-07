//#include "head.hpp"

#include "network.hpp"
#include "neuron.hpp"
#include <vector>
#include <array>
#include <cstdlib>

void initNetwork(Network* net);
void connectNeighbors(Network* net, Neuron* n);
void cleanMemory();
//void populate(Network* net);

int main(){
  int length = 30;
  int height = 30;
  int width = 30;
  std::vector<std::array<int, 3>> positions;
  Network net(length, height, width);

  net.populate();

  //TEST_AREA
  std::printf("net lenght:%i\n", net.getLength());

  net.getNeuron(0, 0, 0)->addPotential(20.0);
  net.getNeuron(1, 2, 0)->addPotential(21.0);

  //net.connectNeurons(net.getNeuron(0, 0, 0));
  initNetwork(&net);
  net.getNeuron(0, 0, 0)->addPotential(80.0);
  
  //initNetwork(&net);
  
  //cleanMemory();
  
  return 0;
}//end main

void initNetwork(Network* net){//Name der funktion passt nicht richtig
  for(int x = 0; x < net->getLength(); x++){
    for(int y = 0; y < net->getHeight(); y++){
      for(int z = 0; z < net->getWidth(); z++){
	net->connectNeurons(net->getNeuron(x, y, z));
      }
    } 
  }
}//end scanNetwork

//verbindet neuronen mit ihren nachbarn innerhalb des eigenen Radius
void connectNeighbors(Network* net, Neuron* n){
  int r = n->getRadius();
  for(int i = -r; i <= r; i++){
    for(int j = -r; j <= r; j++){
      for(int k = -r; k <= r; k++){
	Neuron* neigh = net->getNeuron(n->xPos()+i, n->yPos()+j, n->zPos()+k);
	double weight = (-1) + (rand() % static_cast<int>(1 - (-1) + 1));//random [-1,1]
	n->addNeighbor(neigh, weight);
      }
    }
  }
}//end connectNeighbors

/*void cleanMemory(Network net){
  //Network::~Network(net);
}//end cleanMemory
//*/
