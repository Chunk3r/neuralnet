#include "network.hpp"

Network::Network(int l, int h, int w){
  length = l;
  height = h;
  width = w;

  populate();
}

Network::Network(int* pos, double *weights){
  length = pos[0];
  height = pos[1];
  width = pos[2];

  populate(pos);
}



/************************
 *  populate functions  *
 ************************/


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
}

void Network::populate(int* pos){
  for(int x = 0; x < length; x++){
    v.push_back(std::vector<std::vector<Neuron>>());
    for(int y = 0; y < height; y++){
      v[x].push_back(std::vector<Neuron>());
      for(int z = 0; z < width; z++){
	if(Network::isValidPos(x, y, z, pos)){
	  v[x][y].push_back(Neuron(x, y, z));
	}
      }
    }
  }
  std::printf("\n-----net populated-----\n");
}


/*********************
 * extract functions *
 *********************/

//iterate through vector and return an array containing
//all positions where a neuron is stored
int* Network::extractNeurons(){

  //calc max possible size
  int maxSize = length*height*width;

  //allocate memory
  int* positions = new int[maxSize];

  //store dimensions
  positions[0] = length;
  positions[1] = height;
  positions[2] = width;

  //index variable
  int count = 1;

  //store all neuron positions
  for(int x = 0; x < length; x++){
    for(int y = 0; y < height; y++){
      for(int z = 0; z < width; z++){
	if(&v[x][y][z] != NULL){
	  positions[count*3+0] = x;
	  positions[count*3+1] = y;
	  positions[count*3+2] = z;
	  count++;
	}
      }
    }
  }
  return positions;
}


double* extractWeights(){//TODO
  double* weights;
  return weights;
}

void Network::connectNeurons(Neuron* n){
  int r = n->getRadius();
  std::printf("start looping\n");
  for(int i = (n->xPos() - r); i <= (n->xPos() + r); i++){
    for(int j = (n->yPos() - r); j <= (n->yPos() + r); j++){
      for(int k = (n->zPos() - r); k <= (n->zPos() + r); k++){
	if(isValidNeighbor(i, j, k, n->xPos(), n->yPos(), n->zPos())){
	  std::printf("add Neighbor\n");
	  n->addNeighbor(&v[i][j][k]);//check neuron.cpp
	  //there is the random weight function missing
	}
      }
    }
  }
}


/******************
 *  is functions  *
 ******************/

int Network::isInBounds(int i, int j, int k){
  if(i >= 0 && i < length)
    if(j >= 0 && j < height)
      if(k >= 0 && k < width)
	return 1;
  return 0;
}

int Network::isValidNeighbor(int i, int j, int k, int x, int y, int z){
  if(isInBounds(i, j, k) && &(v[i][j][k])!=NULL)
    if(i!=x || j!=y || k!=z)
      return 1;
  return 0;
}

bool isValidPos(int x, int y, int z, int* pos){
  for(int row = 1; row < pos[0]; row++){
    if(x == pos[row*3+0] && y == pos[row*3+1] && z == pos[row*3+2])
      return true;
  }
  return false;
}


/************
 *getter    *
 ************/


Neuron* Network::getNeuron(int x, int y, int z){
  return &(v[x][y][z]);
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


/*********************
 *save/load functions*
 *********************/


//if filename is specified

void Network::save(char* posFileName, char* wFileName){
  Filehandling fHandler;
  fHandler.writePositions(posFileName, extractNeurons());
  fHandler.writeWeights(wFileName, extractWeights());
}

void Network::load(char* posFileName, char* wFileName){
  Filehandling fHandler;
  Network(fHandler.readPositions(posFileName), fHandler.readWeights(wFileName));
}



//if no filename is specified use default names

void Network::save(){
  Filehandling fHandler;
  fHandler.writePositions((char*)"positions.net", extractNeurons());
  fHandler.writeWeights((char*)"weights.net", extractWeights());
}

void Network::load(){
  Filehandling fHandler;
  Network(fHandler.readPositions((char*)"positions.net"), fHandler.readWeights((char*)"weights.net"));
}
