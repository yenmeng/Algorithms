#ifndef UTILS_H_
#define UTILS_H_

#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <time.h>
using namespace std;
//usage
void help_message(int num) {
    cout << "error: 2 parameters expected but "<< num << " given."<<endl;
    cout << "usage: ./mps <input file name> <output file name>" << endl;
    cout << "ex: ./mps 12.in 12.out"<<endl;
}
//malloc
int **mallocMatrix(int dim1, int dim2){
    int i,j,k;
    int **array = new int*[dim1];
    for(int i = 0; i < dim2; ++i)
	    array[i] = new int[dim2];
    for(int i = 0; i < dim1; ++i)
	    for(int j = 0; j < dim2; ++j)
		    array[i][j] = 0;
    return array;
}
//readfile
vector< pair<int,int> > read(string filename){
    vector<string> buf;
    vector< pair<int,int> > data;
    ifstream fin(filename.c_str());
    string line; 
    bool ignore = true;
    int start,end;
    while(getline(fin,line)){
        if(ignore || line=="0") { 
            ignore = false; 
            continue;
        }  
        else{
            buf.push_back(line);
        }
    }
    for(vector<string>::const_iterator i = buf.begin(); i != buf.end(); ++i) {
        stringstream ss(*i);
        ss>>start>>end;
        data.push_back(make_pair(start,end));
        data.push_back(make_pair(end,start));
    }
    cout<<"read \""<<filename<<"\" success."<<endl;
    fin.close(); 
    sort(data.begin(),data.end());
    return data;
}

//output
void writeFile(string filename,vector< pair<int,int> > chord_set) 
{
  ofstream fout;
  fout.open(filename.c_str());
  fout<<chord_set.size()<<endl;
  for(int i=0;i<chord_set.size();++i){
        fout<<chord_set[i].first<<" "<<chord_set[i].second<<endl;
  }
  fout.close();
}
#endif
