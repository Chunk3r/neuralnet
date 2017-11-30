#include "network.hpp"

Network::Network(int l, int h, int w){
  length = l;
  height = h;
  width = w;

  populate();
}//end Network

Network::Network(int* sizes, int* pos, double *w){
  length = sizes[0];
  height = sizes[1];
  width = sizes[2];

  populate(pos);
}//end Network



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
}//end populate

void Network::populate(int* pos){
  for(int x = 0; x < length; x++){
    v.push_back(std::vector<std::vector<Neuron>>());
    for(int y = 0; y < height; y++){
      v[x].push_back(std::vector<Neuron>());
      for(int z = 0; z < width; z++){
	if(isValidPos(x, y, z, pos)){
	  v[x][y].push_back(Neuron(x, y, z));
	}
      }
    }
  }
  std::prinf("\n-----net populated-----\n");
}//end populate


/*********************
 *                   *
 *********************/

//iterate through vector and return an array containing
//all positions where a neuron is stored
int** Network::extractNeurons(){
  int maxAnz = length*height*width;
  int** positions;//allocate memory
  int count = 0;
  for(int x = 0; x < length; x++){
    for(int y = 0; y < height; y++){
      for(int z = 0; z < width; z++){
	if(&v[x][y][z] != NULL){
	  positions[count][0] = x;
	  positions[count][1] = y;
	  positions[count][2] = z;
	  count++;
	}
      }
    }
  }
  return positions;
}//end extractNeurons

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
}//end connectNeurons


/******************
 *  is functions  *
 ******************/

int Network::isInBounds(int i, int j, int k){
  if(i >= 0 && i < length)
    if(j >= 0 && j < height)
      if(k >= 0 && k < width)
	return 1;
  return 0;
}//end isInBounds

int Network::isValidNeighbor(int i, int j, int k, int x, int y, int z){
  if(isInBounds(i, j, k) && &(v[i][j][k])!=NULL)
    if(i!=x || j!=y || k!=z)
      return 1;
  return 0;
}//end isValidNeighbor

bool isValidPos(int x, int y, int z, int* pos){
  for(int row = 1; row < pos[0]; row++){
    if(x == pos[row*3+0] && y == pos[row*3+1] && z == pos[row*3+2])
      return true;
  }
  return false;
}//end isValidPos


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


/**********************
 *read/write Positions*
 **********************/


//write the positions of neurons into a file
//format: x.y.z
//change it from C to C++
int Network::writePositions(int* pos, int size, const char* name){
   FILE *output = std::fopen(name, "w");
  if(output != NULL){
    std::fprintf(output, "%i\n", (length*height*width));//TODO write l.h.w
    for(int i = 0; i < size; i++){//size of pos
      std::fprintf(output, "%i.%i.%i\n", pos[i*3+0], pos[i*3+1], pos[i*3+2]);
    }
    std::fclose(output);
    return 0;//add exceptionhandling
  }
  else
    return -1;
}//end writePositions

//read positions from a file
//format: x.y.z
int* Network::readPositions(const char *name){
  FILE *input = std::fopen(name, "r");
  if(input != NULL){//check if input is available
    int count = 0;
    int anz;
    std::fscanf(input, "%i\n", &anz);
    int* positions = new int[anz*3];//allocate memory
    do{
      std::fscanf(input, "%i.%i.%i\n", &positions[count*3+0], &positions[count*3+1], &positions[count*3+2]);
      count++;
    }while(*input != EOF);
    
    std::fclose(input);
    return positions;
  }
  
  return NULL;
}//end readPositions


/*********************
 *save/load functions*
 *********************/


//if filename is specified

void Network::save(char* posFileName, char* wFileName){
  writePositions(extractNeurons(), posFileName);//TODO
}//end save

void Network::load(char* posFileName, char* wFileName){
  Network(readPositions(posFileName), readWeights(wFileName));
}//end load



//if no filename is specified use default

void Network::save(){
  writePositions(extractNeurons(), "positions.net");//const zeichenkette kann nicht nach char* konvertiert werden
}//end save

void Network::load(){
  Network(readPositions("positions.net"), readWeights("weights.net"));//warning
}//end load
