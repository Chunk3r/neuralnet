#include "filehandling.hpp"

using namespace std;

void Filehandling::writePositions(const char* name, int* pos){
  ofstream output(name);
  if(output.is_open()){
    int size = pos[0]*pos[1]*pos[2];
    for(int i = 0; i < size; i++){
      output << pos[i*3+0] << ".";
      output << pos[i*3+1] << ".";
      output << pos[i*3+2] << ".\n";
    }
    output.close();
  }
  else
    cerr << "Unable to open File\n";
}//end writePositions

int* Filehandling::readPositions(const char* name){
  ifstream input(name);
  if(input.is_open()){
    //get first line
    //allocate memory
    int* pos = ;
    //read file and write to pos

    input.close();
    return pos;
  }
  else{
    cout << "Unable to open File\n";
    return NULL;
  }
}//end readPositions
