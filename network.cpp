#include "network.hpp"

Network::Network(int l, int h, int w){
    _length = l;
    _height = h;
    _width = w;

    populate();
}

Network::Network(const char* fname){
    std::string data;
    data = readFromFile(fname);

    int state = 0;
    int x, y, z, radius;
    double weight, threshold, potential;
    Neuron* posNeuron = nullptr;
    Neuron* posNeighbor = nullptr;

    StringTokenizer tokenizer(data, "\n");
    while (tokenizer.hasMoreTokens()) {
        StringTokenizer lineTokenizer(tokenizer.nextToken(), " ");
        std::string token = lineTokenizer.nextToken();
        std::cout << "Token: " << token;
        if(token[0] == '#'){
            if(state == 3)
                state--;
            else
                state++;
            continue;
        }

        std::cout << "State: " << state;

        switch(state){
        case 0:
            std::cout << "Token: " << token;
            _length = std::stoi(token);
            _height = std::stoi(lineTokenizer.nextToken());
            _width = std::stoi(lineTokenizer.nextToken());
            populateWithDummies();
            break;
        case 1:
            //create neuron object
            x = std::stoi(token);
            y = std::stoi(lineTokenizer.nextToken());
            z = std::stoi(lineTokenizer.nextToken());
            radius = std::stoi(lineTokenizer.nextToken());
            threshold = std::stod(lineTokenizer.nextToken());
            potential = std::stod(lineTokenizer.nextToken());
            addNeuron(x, y, z, radius, threshold, potential);
            break;
        case 2:
            //get coordinates of neuron, wich gets its neighbors
            x = std::stoi(token);
            y = std::stoi(lineTokenizer.nextToken());
            z = std::stoi(lineTokenizer.nextToken());
            posNeuron = getNeuron(x, y, z);
            break;
        case 3:
            //add neighbors
            x = std::stoi(token);
            y = std::stoi(lineTokenizer.nextToken());
            z = std::stoi(lineTokenizer.nextToken());
            weight = std::stod(lineTokenizer.nextToken());
            posNeighbor = getNeuron(x, y, z);
            if(posNeuron != nullptr && posNeighbor != nullptr){
                posNeuron->addNeighbor(posNeighbor, weight);
            }
            break;
        }
    }
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

void Network::populateWithDummies(){
    for(int x = 0; x < _length; x++){
        _neurons.push_back(std::vector<std::vector<Neuron>>());
        for(int y = 0; y < _height; y++){
            _neurons[x].push_back(std::vector<Neuron>());
            for(int z = 0; z < _width; z++){
                _neurons[x][y].push_back(Neuron(x, y, z, 0, 0.0, 0.0));
            }
        }
    }
    //std::printf("\n-----net populated-----\n");
}


/*********************
 * extract functions *
 *********************/

void Network::toFile(const char* fname){
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


/*****************
 *               *
 *****************/

std::string Network::readFromFile(const char* fname){
    std::ifstream in(fname);
    in.open(fname);

    std::ostringstream oss;
    oss << in.rdbuf();
    in.close();

    std::string data;
    data = oss.str();

    return data;
}

void Network::addNeuron(int x, int y, int z, int radius, double threshold, double potential){
    if(isInBounds(x, y, z)){
        _neurons[x][y][z].setParameters(radius, threshold, potential);
    }
}
