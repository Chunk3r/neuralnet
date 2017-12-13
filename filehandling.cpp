#include "filehandling.hpp"

using namespace std;

void Filehandling::writePositions(const char* name, int* pos){
  ofstream output(name);
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
    cerr << "Unable to open File\n";
}

void Filehandling::writeWeights(char* name, int* weights){
  ofstream output(name);
  if(output.is_open()){
    int size = weights[0];

    for(int i = 0; i <= size; i++){
      output << weights[i] << "\n";
    }
  }
}

int* Filehandling::readPositions(const char* name){
  ifstream input(name);
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
  else{
    cout << "Unable to open File\n";
    return NULL;
  }
}

int* readWeights(char* name){
  ifstream input(name);
  if(input.is_open){
    int size;
    
    //read first line
    input >> size;

    //allocate memory
    int* weights = new int[size+1];

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
