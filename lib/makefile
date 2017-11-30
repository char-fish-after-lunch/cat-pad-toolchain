catass: catass.o catpad.h catpad.o
	g++ --std=c++14 -O2 -o catass catass.o catpad.o

catpad.o: catpad.h catpad.cpp
	g++ --std=c++14 -O2 -c -o catpad.o catpad.cpp

catass.o: catpad.h catass.cpp
	g++ --std=c++14 -O2 -c -o catass.o catass.cpp

