#include "network.hpp"

Network::Network(int l, int h, int w){
  _length = l;
  _height = h;
  _width = w;

  populate();
}

Network::Network(const char* fname){
    std::ifstream in(fname);
    //TODO
}

/************************
 *  populate functions  *
 ************************/


void Network::populate(){
    int anz = 0;//for debugging
    for(int x = 0; x < _length; x++){
        _neurons.push_back(std::vector<std::vector<Neuron>>());
        for(int y = 0; y < _height; y++){
            _neurons[x].push_back(std::vector<Neuron>());
            for(int z = 0; z < _width; z++){
                _neurons[x][y].push_back(Neuron(x, y, z));
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
    _neurons.push_back(std::vector<std::vector<Neuron>>());
    for(int y = 0; y < _height; y++){
      _neurons[x].push_back(std::vector<Neuron>());
      for(int z = 0; z < _width; z++){
        if(Network::isValidPos(x, y, z, pos)){
            _neurons[x][y].push_back(Neuron(x, y, z));
        }
      }
    }
  }
  std::printf("\n-----net populated-----\n");
}


/*********************
 * extract functions *
 *********************/

void Network::toFile(char* fname){
    std::ofstream out(fname, std::ofstream::trunc);
    if(out.is_open()){
        out << _length << " " << _height << " " << _width << std::endl;
        out << "#" << std::endl;

        for(int i = 0; i < _length; i++){
            for(int j = 0; j < _height; j++){
                for(int k = 0; k < _width; k++){
                    _neurons[i][j][k].propertiesToStream(out);
                }
            }
        }

        out << "#" << std::endl;

        for(int i = 0; i < _length; i++){
            for(int j = 0; j < _height; j++){
                for(int k = 0; k < _width; k++){
                    _neurons[i][j][k].neighborsToStream(out);
                }
            }
        }

        out.close();
    }
}


//search for neighbors within a radius and
//connect them to the given neuron
void Network::connectNeurons(Neuron* n){
  int r = n->getRadius();
  std::printf("start looping\n");
  for(int i = (n->xPos() - r); i <= (n->xPos() + r); i++){
    for(int j = (n->yPos() - r); j <= (n->yPos() + r); j++){
      for(int k = (n->zPos() - r); k <= (n->zPos() + r); k++){
	if(isValidNeighbor(i, j, k, n->xPos(), n->yPos(), n->zPos())){
	  std::printf("add Neighbor\n");
      n->addNeighbor(&_neurons[i][j][k]);//check neuron.cpp
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
  if(isInBounds(i, j, k) && &(_neurons[i][j][k])!=NULL)
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
  return &(_neurons[x][y][z]);
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
