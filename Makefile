all: code

code: main.cpp
	g++ -O2 -pipe -std=c++17 -o code main.cpp

clean:
	rm -f code *.o

