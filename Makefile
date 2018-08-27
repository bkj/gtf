# gtf/Makefile

all :
	mkdir -p bin
	make ffa
	make gtf

ffa : min.cpp
	g++ -o bin/ffa $^

gtf : gtf/main.cpp gtf/graph.cpp gtf/graphtv.cpp
	g++ -std=c++11 -o bin/gtf $^

clean :
	rm -rf bin

