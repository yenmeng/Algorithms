#include "graph.h"
#include "maxheap.h"

void
Graph::DFS(long n, bool& flag, long& cost, vector<Edge>& R)
{
    if(this->V[n].color()=="white") { this->V[n].update_color("gray"); }
    vector<Edge> temp = this->V[n].get_adj();
    //cout<<n<<' ';
    //cout<<"adjlist size of vertex "<<n<<": "<<temp.size()<<endl;
    for(int i=0;i<temp.size();++i){
        if(!flag) return;
        if(this->V[temp[i].endpoint2()].color()=="gray" && this->V[temp[i].endpoint2()].pi()!= n ){
            //cout<<"case1"<<endl;
            Edge remove = temp[i];
            long index = temp[i].endpoint1();
            long minweight = remove.weight();
            if(this->V[index].prev().weight()<minweight){
                    minweight = this->V[index].prev().weight();
                    remove = this->V[index].prev();
                }
            while(index!=temp[i].endpoint2()){
                if(this->V[index].prev().weight()<minweight){
                    minweight = this->V[index].prev().weight();
                    remove = this->V[index].prev();
                }
                index = this->V[index].prev().endpoint1();
            }
            //cout<<"remove:"<<remove.endpoint1()<<' '<<remove.endpoint2()<<' '<<remove.weight()<<endl;
            cost+=remove.weight();
            R.push_back(remove);
            this->V[remove.endpoint1()].removeEdge(remove.endpoint2());
            this->V[remove.endpoint1()].reset();
            //this->V[temp[i].endpoint1()].removeEdge(temp[i].endpoint2());
            //return false;
            flag = false;
            return;
        }
        else if(this->V[temp[i].endpoint2()].color()=="gray" && this->V[temp[i].endpoint2()].pi()==temp[i].endpoint1()){
            //cout<<"case2"<<endl;
            DFS(temp[i].endpoint2(),flag, cost, R);
        }
        else if(this->V[temp[i].endpoint2()].color()=="white"){
            //cout<<"case3"<<endl;
            this->V[temp[i].endpoint2()].update_pi(temp[i].endpoint1());
            this->V[temp[i].endpoint2()].update_prev(temp[i]);
            DFS(temp[i].endpoint2(),flag, cost, R);
        }
        else {
            //cout<<"case4"<<endl;
            continue;
        }
    }
    this->V[n].update_color("black");
    //return true;
}
void
Graph::directedCycleDetect(ofstream& outfile)
{
    bool flag = true;
    int cnt = 1;
    long cost = 0;
    vector<Edge> remove;
    while(!flag || cnt==1 ){
        flag = true;
        this->recolor();
        //cout<<"-> round "<<cnt<<endl;
        for(int i=0;i<this->vertices();++i){
            //cout<<"vertex["<<i<<"]: "<<endl;
            if(this->V[i].color()!="black" && this->V[i].get_adj().size()!=0){
                DFS(i,flag,cost,remove);
                if(flag==false) { break; }
            }
            //cout<<endl;
        }
        ++cnt;
    }
    outfile<<cost<<'\n';
    for(int i=0;i<remove.size();++i){
        outfile<<remove[i].endpoint1()<<' '<<remove[i].endpoint2()<<' '<<remove[i].weight()<<'\n';
    }
    cout<<"remove cost: "<<cost<<'\n';
    outfile.close();
}
void
Graph::undirectedCycleDetect(ofstream& outfile, long& cost)
{
    map<Edge,long> include;
    bool visited[vertices()] = {false};
    long curr=0, prev=0, w=0;
    BinaryHeap pq(this->V);
    visited[0] = true;
    while(!pq.heap.empty()){
        curr = pq.ExtractMax();
        visited[curr] = true;
        //cout<<"curr Node: "<<curr<<'\n';
        if(curr!=0){
            prev = this->V[curr].pi();
            w = this->V[curr].key();
            include.insert(make_pair(Edge(curr,prev,w),w));
            include.insert(make_pair(Edge(prev,curr,w),w));
            //cout<<curr<<' '<<prev<<' '<<w<<endl;
            cost-=w;
        }
        vector<Edge> temp = this->V[curr].get_adj();
        for(long i=0;i<temp.size();++i){
            //cout<<temp[i].endpoint2()<<' ';
            if(!visited[temp[i].endpoint2()] && temp[i].weight()>V[temp[i].endpoint2()].key()){
                //cout<<"increase key "<<temp[i].endpoint1()<<' '<<temp[i].endpoint2()<<' '<<temp[i].weight()<<endl;
                this->V[temp[i].endpoint2()].update_key(temp[i].weight());
                this->V[temp[i].endpoint2()].update_pi(curr);
                pq.DecreaseKey(temp[i].endpoint2(),temp[i].weight(),curr);
            }
        }
    }
    outfile<<cost<<'\n';
    for(long i=0;i<E.size();++i){
        auto it = include.find(E[i]);
        if(it==include.end()){
            outfile<<E[i].endpoint1()<<' '<<E[i].endpoint2()<<' '<<E[i].weight()<<'\n';
        }
    }
    cout<<"remove cost: "<<cost<<'\n';
    outfile.close();
}
