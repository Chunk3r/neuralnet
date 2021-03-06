all: head.o network.o neuron.o filehandling.o
	g++ -Wall -o brain head.o network.o neuron.o filehandling.o

head.o: head.cpp
	g++ -Wall -c head.cpp

network.o: network.cpp network.hpp
	g++ -Wall -c network.cpp network.hpp

neuron.o: Neurons/neuron.cpp Neurons/neuron.hpp
	g++ -Wall -c Neurons/neuron.cpp Neurons/neuron.hpp

filehandling.o: filehandling.cpp filehandling.hpp
	g++ -Wall -c filehandling.cpp filehandling.hpp

rm:
	rm *.o brain
