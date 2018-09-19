#include "network.hpp"
#include <vector>
#include <array>
#include <cstdlib>

void initNetwork(Network* net);
void connectNeighbors(Network* net, Neuron* n);

int main(){
    int length = 3;
    int height = 3;
    int width = 3;

    Network net(length, height, width);

    //TEST_AREA
    std::printf("net lenght:%i\n", net.getLength());

    //test if fire Function of Neurons is working
    net.getNeuron(0, 0, 0)->addPotential(20.0);
    net.getNeuron(1, 2, 0)->addPotential(21.0);

    //
    initNetwork(&net);


    net.toFile("net.txt");
    net.getNeuron(0, 0, 0)->addPotential(80.0);

    Network net1("net.txt");
    net1.toFile("net1.txt");

    //cleanMemory();

    return 0;
}//end main

void initNetwork(Network* net){
    for(int x = 0; x < net->getLength(); x++){
        for(int y = 0; y < net->getHeight(); y++){
            for(int z = 0; z < net->getWidth(); z++){
                net->connectNeurons(net->getNeuron(x, y, z));
            }
        }
    }
}//end initNetwork

//connects neuros with their neighbours within their radius
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
