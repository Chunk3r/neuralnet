#include "network.hpp"

Network::Network(int l, int h, int w){
  length = l;
  height = h;
  width = w;
}//end Network()

Neuron* Network::getNeuron(int x, int y, int z){
  return &(v[x][y][z]);
}

void Network::populate(){
  int anz = 0;//for debugging
  for(int x = 0; x < length; x++){
    v.push_back(std::vector<std::vector<Neuron>>());
    for(int y = 0; y < height; y++){
      v[x].push_back(std::vector<Neuron>());
      for(int z = 0; z < width; z++){
	v[x][y].push_back(Neuron(x, y, z));
	anz++;
	std::printf("anz neurons: %i\n", anz);
	std::printf("z");
      }
      std::printf("y");
    }
    std::printf("x");
  }
  std::printf("\n-----net populated-----\n");
}//end populate

/*void Network::populateWithDna(FileInput){
  for(int i = 0; i < a.size; i++){
    //add neuron an durch vector gegebener stelle
  }
}//end populateWithDna
*/

//iterate through vector and return an array containing
//all positions where a neuron is stored
int[][] Network::extractNeurons(){
  int[(length*height*width)][3] pos;//required size is calculated
  int count = 0;
  for(int x = 0; x < length; x++){
    for(int y = 0; y < height; y++){
      for(int z = 0; z < width; z++){
	if(v[x][y][z] != NULL){
	  pos[count][0] = x;
	  pos[count][1] = y;
	  pos[count][2] = z;
	  count++;
	}
      }
    }
  }
  return pos;
}//end extractNeurons

void Network::connectNeurons(Neuron* n){
  int r = n->getRadius();
  std::printf("start looping\n");
  for(int i = (n->xPos() - r); i <= (n->xPos() + r); i++){
    for(int j = (n->yPos() - r); j <= (n->yPos() + r); j++){
      for(int k = (n->zPos() - r); k <= (n->zPos() + r); k++){
	if(isInBounds(i, j, k) == 1 && &v[i][j][k] != NULL){
	  if(i != n->xPos() || j != n->yPos() || k != n->zPos()){
	    std::printf("add Neighbor\n");
	    n->addNeighbor(&v[i][j][k]);
	  }
	}
      }
    }
  }
}//end connectNeurons

int Network::isInBounds(int i, int j, int k){
  if(i >= 0 && i < length)
    if(j >= 0 && j < height)
      if(k >= 0 && k < width)
	return 1;
  return 0;
}

int Network::getLength(){
  return length;
}

int Network::getHeight(){
  return height;
}

int Network::getWidth(){
  return width;
}
