default: dcas

dcas: dcas.cpp
	g++ dcas.cpp -o dcas -pthread -Wall -std=c++11

clean:
	rm -r dcas
