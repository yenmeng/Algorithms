#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <map>

using namespace std;
#define INF std::numeric_limits<long>::max()
class Edge;
class Vertex;
class Graph;

class Edge
{
    public:
        friend bool operator < (const Edge& e1 ,const Edge& e2) {
            if(e1._weight != e2._weight)
                return e1._weight < e2._weight;
            if(e1._u != e2._u)
               return e1._u < e2._u;
            return e1._v < e2._v;
        }
        friend bool operator == (const Edge& e1 ,const Edge& e2){
            return (e1._v == e2._u && e1._u == e2._v && e1._weight == e2._weight);
        }
        bool operator() (Edge& e) { return e.endpoint2() == this->endpoint2(); }
        Edge() {}
        Edge(long u, long v, long w): _u(u), _v(v), _weight(w) {}
        long endpoint1() const{
            return _u;
        }
        long endpoint2() const{
            return _v;
        }
        long weight() const{
            return _weight;
        }
    private:
        long _u;
        long _v;
        long _weight;
};

class Vertex
{
    public:
        Vertex() {}
        Vertex(int no): _no(no) { _key=-INF; _pi=-1; _prev = Edge(-1,-1,INF), _color="white";}
        long no() const{
            return _no;
        }
        long key() const{
            return _key;
        }
        long pi() const{
            return _pi;
        }
        Edge prev() const{
            return _prev;
        }    
        string color() const{
            return _color;
        }
        void update_no(long no){
            _no=no;
        }
        void update_key(long new_key){
            _key = new_key;
        }
        void update_pi(long pi){
            _pi = pi;
        }
        void update_prev(Edge e){
            _prev = e;
        }
        void update_color(string color){
            _color = color;
        }
        void addEdge(Edge e){
            _adjlist.push_back(e);
        }
        void sortAdjMIN(){
            sort(_adjlist.begin(), _adjlist.end());
        }
        vector<Edge> get_adj(){
            return _adjlist;
        }
        void removeEdge(long idx){
            vector<Edge>::iterator it = find_if(_adjlist.begin(), _adjlist.end(), [&idx](const Edge& obj) {return obj.endpoint2() == idx;});
            if(it!=_adjlist.end()){
                _adjlist.erase(it);
            }
        }
        void reset(){
            _pi = -1;
            _prev = Edge(-1,-1,INF);
            _color = "white";
        }
    private:
        long _no;
        long _key;
        long _pi;
        Edge _prev;
        string _color;
        vector<Edge> _adjlist;
};

class Graph
{
    public:
        Graph(char type, long vertices, long edges): 
            _type(type), _vertices(vertices), _edges(edges) {}
        char type(){
            return _type;
        }
        long vertices(){
            return _vertices;
        }
        long edges(){
            return _edges;
        }
        void recolor(){
            for(int i=0;i<_vertices;++i){
                V[i].update_color("white");
            }
        }
        void undirectedCycleDetect(ofstream& outfile, long& cost);
        void DFS(long n, bool& flag, long& cost, vector<Edge>& R);
        void directedCycleDetect(ofstream& outfile);
        vector<Edge> E;
        vector<Vertex> V;
    private:
        char _type;
        long _vertices;
        long _edges;
};

#endif
