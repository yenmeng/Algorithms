#include "utils.h"
#include "graph.h"

using namespace std;

Graph readfile(ifstream &infile, long& cost)
{
    //cout<<"reading..."<<endl;
    string line;
    stringstream ss;
    char type;
    unsigned long vertices=0, edges=0;
    //get first 3 rows
    for(int i=0;i<3;++i){
        getline(infile,line);
        ss.clear();
        ss.str(line);
        if(i==0)
            ss>>type;
        if(i==1)
            ss>>vertices;
        if(i==2)
            ss>>edges;
    }
    //construct graph
    Graph G(type,vertices,edges);
    vector<Vertex> vec(vertices);
    vector<Edge> edge(edges);
    G.V = vec;
    G.E = edge;
    for(int i=0;i<vertices;++i){
        G.V[i] = Vertex(i);
    }
    bool flag = true;
    long cnt=0;
    while(getline(infile,line)){
        if(line!="0"){
            ss.clear();
            ss.str(line);
            long start,end,weight;
            ss>>start>>end>>weight;
            //undirected
            if(type=='u'){
                G.V[start].addEdge(Edge(start,end,weight));
                G.V[end].addEdge(Edge(end,start,weight));
            }
            //directed
            else{
                G.V[start].addEdge(Edge(start,end,weight));
            }
            G.E[cnt]=Edge(start,end,weight);
            cost+=weight;
            ++cnt;
        }
    }
    for(long i=0;i<G.vertices();++i){
        if(G.type()=='d') { G.V[i].sortAdjMIN(); }
        //else { G.V[i].sortAdjMAX(); }
    }
    return G;
}
