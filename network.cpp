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
int** Network::extractNeurons(){
  int maxAnz = length*height*width;
  int[maxAnz][3] positions;//change it to pointer
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

int Network::isInBounds(int i, int j, int k){
  if(i >= 0 && i < length)
    if(j >= 0 && j < height)
      if(k >= 0 && k < width)
	return 1;
  return 0;
}

int Network::isValidNeighbor(int i, int j, int k, int x, int y, int z){
  if(isInBounds(i, j, k) && v[i][j][k]!=NULL)//no match for operator!=
    if(i!=x || j!=y || k!=z)
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

//write the positions of neurons into a file
//format: x.y.z
int Network::writePositions(int **pos, char *name){
   FILE *output = std::fopen(name, "w");
  if(output != NULL){
    std::fprintf(output, "%i\n", &(length*height*width));
    for(int i = 0; i < pos.size(); i++){//size must be a parameter
      std::fprintf(output, "%i.%i.%i\n", pos[i][0], pos[i][1], pos[i][2]);
    }
    std::fclose(output);
    return 0;//add exceptionhandling
  }
  else
    return -1;
}//end writePositions

//read positions from a file
//format: x.y.z
int** Network::readPositions(char *name){
  FILE *input = std::fopen(name, "r");
  if(input != NULL){
    int count = 0;
    int anz;
    std::fscanf(input, "%i\n", &anz);
    int[anz][3] positions;//make it a pointer
    while(input != EOF){//must read line first
      std::fscanf(input, "%i.%i.%i\n", positions[count][0], positions[count][1], positions[count][2]);
      count++;
    }
    std::fclose(input);
    return positions;
  }
  else
    return -1;//wrong return-type
}//end readPositions

void Network::save(){
  writePositions(extractNeurons(), "pos.net");//const zeichenkette kann nicht nach char* konvertiert werden
}//end save

void Network::load(){
  initFromFile(readPositons("pos.net"));
}//end load
