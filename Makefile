CXX=g++
BINARIES=snl.o game.o

all: snl

snl: ${BINARIES}
	${CXX} $^ -o $@

game.o: game.cpp
	${CXX} $^ -c

snl.o: snl.cpp
	${CXX} $^ -c

clean:
	rm -rf *.o snl