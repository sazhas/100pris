all:
	g++ -std=c++17 -O2 -Wall 100prisoners.cpp -o sim

clean:
	rm *.exe
