all: head.o network.o neuron.o
	g++ -Wall -o brain head.o network.o neuron.o

head.o: head.cpp
	g++ -Wall -c head.cpp

network.o: network.cpp network.hpp
	g++ -Wall -c network.cpp network.hpp

neuron.o: neuron.cpp neuron.hpp
	g++ -Wall -c neuron.cpp neuron.hpp

rm:
	rm *.o brain
