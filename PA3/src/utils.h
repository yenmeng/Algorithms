#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include "graph.h"

using namespace std;

Graph readfile(ifstream &infile, long& cost);

#endif
