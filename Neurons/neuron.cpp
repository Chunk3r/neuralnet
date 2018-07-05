#include "neuron.hpp"

Neuron::Neuron(int x, int y, int z){
  this->x = x;
  this->y = y;
  this->z = z;
  radius = 1;
  membranePotential = 0;
  membraneThreshold = 20;
  printf("Neuron created\n");
}

//adds a neuron wich shoud receive signals from this neuron
void Neuron::addNeighbor(Neuron* n, double w){
  neighbors.push_back(n);
  printf("Neighbor added\n");
  weights.push_back(w);
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
  membranePotential += p;
  if(membranePotential >= membraneThreshold){
    std::printf("fire neuron[%i][%i][%i]\n", xPos(), yPos(), zPos());
    fire();
  }
}

int Neuron::getRadius(){
  return radius;
}

int Neuron::xPos(){
  return x;
}

int Neuron::yPos(){
  return y;
}

int Neuron::zPos(){
  return z;
}

//sends a signal to all connected neurons
void Neuron::fire(){
  for(unsigned int i = 0; i < neighbors.size(); i++){
    neighbors[i]->addPotential(membranePotential * weights[i]);
  }
  std::printf("fired\n");
  resetMembrane();
}

//resets the Membrane and does the cooldown
void Neuron::resetMembrane(){
  membranePotential = 0;
}

//overloading << for simplified saving //overloading might be inappropriate
std::ostream& operator<<(std::ostream& out, Neuron::Neuron& n){
  out << n.x << " " << n.y << " " << n.z << " " << n.radius
      << n.membraneThreshold << " " << n.membranePotential;

  return out;
}
