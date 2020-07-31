all: d1s1 d1s2 d2s1 d2s2

d1s1:
	g++ -o d1s1 -std=c++11 d1s1.cc

d1s2:
	g++ -o d1s2 -std=c++11 d1s2.cc

d2s1: d2s1.cc
	g++ -o d2s1 -std=c++11 d2s1.cc

d2s2: d2s2.cc
	g++ -o d2s2 -std=c++11 d2s2.cc

clean:
	rm -rf *.o d1s1 d1s1 d2s1
