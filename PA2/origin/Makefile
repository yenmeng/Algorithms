.PHONY: all clean

TARGET= mps

all: $(TARGET) 

mps: src/maxPlanarSubset.cpp src/utils.h
	g++ -O3 src/maxPlanarSubset.cpp -o mps

clean:
	rm -f $(TARGET) 