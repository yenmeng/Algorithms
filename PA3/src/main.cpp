#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include "graph.h"
#include "utils.h"
#include "maxheap.h"

using namespace std;

static void usage()
{
    cout<<"Usage: ./cb <input file name> <output file name>"<<endl;
}
int main(int argc, char** argv)
{
    clock_t tStart = clock();
    //error handling
    if(argc!=3){
        if(argc>3)
            cerr<<"ERROR: Too many arguments!"<<endl;
        else
            cerr<<"ERROR: Expected 2 arguments but "<<argc-1<<" given."<<endl;
        usage();
        exit(1);
    }
    ifstream infile(argv[1]);
    if(!infile){
        cerr<<"ERROR: Cannot open input file \""<<argv[1]<<"\"!"<<endl;
        exit(1);
    }
    long cost=0;
    Graph G = readfile(infile,cost);
    //graph info
    /*cout<<"read \""<<argv[1]<<"\" success."<<endl;
    cout<<"-------------------"<<endl;
    cout<<"graph type: "<<G.type()<<endl;
    cout<<"vertices: "<<G.vertices()<<endl;
    if(G.type()=='u')
        cout<<"edges: "<<G.edges()*2<<endl;
    else
        cout<<"edges: "<<G.edges()<<endl;
    cout<<"-------------------"<<endl;*/
    /*for(long i=0;i<G.vertices();++i){
        cout<<"vertex["<<i<<"]: ";
        vector<Edge> temp = G.V[i].get_adj();
        for(int j=0;j<temp.size();++j){
            cout<<temp[j].endpoint2()<<"("<<temp[j].weight()<<") ";
        }
        cout<<endl;
    }*/
    ofstream outfile(argv[2]);
    if(G.type() == 'd'){
        G.directedCycleDetect(outfile);
    }
    else { 
        G.undirectedCycleDetect(outfile,cost); 
    }
    printf("execution time: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}