#include "neuron.hpp"

Neuron::Neuron(int _x, int _y, int _z){
  this->_x = _x;
  this->_y = _y;
  this->_z = _z;
  _radius = 1;
  _membranePotential = 0;
  _membraneThreshold = 20;
  printf("Neuron created\n");
}

//adds a neuron wich shoud receive signals from this neuron
void Neuron::addNeighbor(Neuron* n, double w){
  _neighbors.push_back(n);
  printf("Neighbor added\n");
  _weights.push_back(w);
  printf("Weight added\n");
}

//add Neighbor with random weight
void Neuron::addNeighbor(Neuron* n){
  //stuff to generate random double
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  //call addNeighbor with random double
  addNeighbor(n, dis(gen));
}

//adds signals from inputs to the Potential
//calls fire if Threshold is reached
void Neuron::addPotential(double p){
  _membranePotential += p;
  if(_membranePotential >= _membraneThreshold){
    std::printf("fire neuron[%i][%i][%i]\n", xPos(), yPos(), zPos());
    fire();
  }
}

int Neuron::getRadius(){
  return _radius;
}

int Neuron::xPos(){
  return _x;
}

int Neuron::yPos(){
  return _y;
}

int Neuron::zPos(){
  return _z;
}

//sends a signal to all connected neurons
void Neuron::fire(){
  for(unsigned int i = 0; i < _neighbors.size(); i++){
    _neighbors[i]->addPotential(_membranePotential * _weights[i]);
  }
  std::printf("fired\n");
  resetMembrane();
}

//resets the Membrane and does the cooldown
void Neuron::resetMembrane(){
  _membranePotential = 0;
}

void Neuron::propertiesToStream(std::ostream out){
    out << n._x << " " << n._y << " " << n._z << " " << n._radius
        << n._membraneThreshold << " " << n._membranePotential;
}

void Neuron::neighborsToStream(std::ostream out){
    out << _x << " " << _y << " " << _z << std::endl;
    out << "#" << std::endl;

    int size = _neighbors.size();

    for(int i = 0; i < size; i++){
        out << _neighbors[i]->xPos() << " "
            << _neighbors[i]->yPos() << " "
            << _neighbors[i]->zPos() << " "
            << _weights[i] << std::endl;
    }
}
