# CC and CFLAGS are varilables
CC = g++
CFLAGS = -std=c++11 -c
AR = ar
ARFLAGS = rcv
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

# optimized version
cb	: graph.o utils.o maxheap.o main.o 
			$(CC) -std=c++11 $(OPTFLAGS) graph.o utils.o maxheap.o main.o -o cb
main.o 	   	: src/main.cpp src/graph.h src/utils.h src/maxheap.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
graph.o		: src/graph.cpp src/graph.h src/maxheap.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
utils.o		: src/utils.cpp src/utils.h src/graph.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
maxheap.o	: src/maxheap.cpp src/maxheap.h src/graph.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
# clean all the .o and executable files
clean:
		rm -rf cb *.o 

