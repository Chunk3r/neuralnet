#include "network.hpp"

Network::Network(int l, int h, int w){
  _length = l;
  _height = h;
  _width = w;

  populate();
}

Network::Network(int* pos, double *weights){
  _length = pos[0];
  _height = pos[1];
  _width = pos[2];

  populate(pos);
}



/************************
 *  populate functions  *
 ************************/


void Network::populate(){
  int anz = 0;//for debugging
  for(int x = 0; x < _length; x++){
    _v.push_back(std::vector<std::vector<Neuron>>());
    for(int y = 0; y < _height; y++){
      _v[x].push_back(std::vector<Neuron>());
      for(int z = 0; z < width; z++){
    _v[x][y].push_back(Neuron(x, y, z));
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
  for(int x = 0; x < _length; x++){
    _v.push_back(std::vector<std::vector<Neuron>>());
    for(int y = 0; y < _height; y++){
      _v[x].push_back(std::vector<Neuron>());
      for(int z = 0; z < width; z++){
        if(Network::isValidPos(x, y, z, pos)){
            _v[x][y].push_back(Neuron(x, y, z));
        }
      }
    }
  }
  std::printf("\n-----net populated-----\n");
}


/*********************
 * extract functions *
 *********************/

//insert operatoroverloading here.
ostream& operator<<(ostream& out, Network& net){
  out << net._length << " " << net._height << " " << net._width << "\n"
      << (net._length*net._height*net._width);

  return out;
}

//iterate through vector and return an array containing
//the dimensions of the network and (line 0) -> needs an own function
//all positions where a neuron is stored (line 1..n)
int* Network::extractPositions(){

  //calc max possible size
  int maxSize = _length*_height*_width;

  //allocate memory
  int* positions = new int[maxSize];

  //store dimensions
  positions[0] = _length;
  positions[1] = _height;
  positions[2] = _width;

  //index variable
  int row = 1;

  //store all neuron positions
  for(int x = 0; x < _length; x++){
    for(int y = 0; y < _height; y++){
      for(int z = 0; z < _width; z++){
        if(&_v[x][y][z] != NULL){
        positions[row*3+0] = x;
        positions[row*3+1] = y;
        positions[row*3+2] = z;
        row++;
        }
      }
    }
  }
  return positions;
}


double* extractWeights(){//TODO
    int maxSize = _length * _height * _width;
    double* weights = new double[maxSize];
    int count = 0;

    for(int x = 0; x < _lenght; x++){
        for(int y = 0; y < _height; y++){
            for(int z = 0; z < _width; z++){
                if(&_v[x][y][z] != NULL)
                    weights[count++] = _v[x][y][z].weight();
            }
        }
    }

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
  if(i >= 0 && i < _length)
    if(j >= 0 && j < _height)
      if(k >= 0 && k < _width)
	return 1;
  return 0;
}

int Network::isValidNeighbor(int i, int j, int k, int x, int y, int z){
  if(isInBounds(i, j, k) && &(_v[i][j][k])!=NULL)
    if(i!=x || j!=y || k!=z)
      return 1;
  return 0;
}

bool Network::isValidPos(int x, int y, int z, int* pos){
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
  return &(_v[x][y][z]);
}

int Network::getLength(){
  return _length;
}

int Network::getHeight(){
  return _height;
}

int Network::getWidth(){
  return _width;
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
