#include "filehandling.hpp"

void Filehandling::write(char* fname, Network::Network* net){
  std::ofstream output(fname);
  if(output.is_open()){
    output << *net;

    int x = net.getLength();
    int y = net.getHeight();
    int z = net.getWidth();
    
    for(int i = 0; i < x; i++){
      for(int j = 0; j < y; j++){
	for(int k = 0; k < z; k++){
	  output << *net[i][j][k];
	}
      }
    }
    output.close();
  }
  else
    std::cerr << "Unable to open File\n";
}

void Filehandling::writePositions(char* name, int* pos){
  std::ofstream output(name);
  if(output.is_open()){
    int size = pos[0]*pos[1]*pos[2];
    
    for(int i = 0; i <= size; i++){
      output << pos[i*3+0] << " ";//check if correct
      output << pos[i*3+1] << " ";
      output << pos[i*3+2] << "\n";
    }
    output.close();
  }
  else
    std::cerr << "Unable to open File\n";
}

void Filehandling::writeWeights(char* name, double* weights){
  std::ofstream output(name);
  if(output.is_open()){
    int size = (int)weights[0];

    for(int i = 0; i <= size; i++){
      output << weights[i] << "\n";
    }
  }
}

int* Filehandling::readPositions( char* name){
  std::ifstream input(name);
  if(input.is_open()){
    int length, height, width;

    //get first line
    input >> length >> height >> width;

    //allocate memory
    int* pos = new int[(length*height*width)+3];

    //store dimensions in pos
    pos[0] = length;
    pos[1] = height;
    pos[2] = width;

    //read file and write to pos
    int size = length*height*width;
    
    for(int s = 1; s <= size; s++){
      input >> pos[s*3] >> pos[s*3+1] >> pos[s*3+2];
    }

    //close file and return
    input.close();
    return pos;
  }
  std::cerr << "Unable to open File\n";
  return NULL;
}

double* Filehandling::readWeights(char* name){
  std::ifstream input(name);
  if(input.is_open()){
    int size;
    
    //read first line
    input >> size;

    //allocate memory
    double* weights = new double[size+1];

    weights[0] = size;

    //read file and write to weights
    for(int i = 1; i <= size; i++){
      input >> weights[i];
    }

    //close file and return
    input.close();
    return weights;
  }
  return NULL;
}
