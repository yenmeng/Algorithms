#include "utils.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// global variable
vector< pair<int,int> > chord_set;
int create_MIS_Table(vector<pair <int,int> > data, int len, int **MIS,int **CASE){
    for(int j=0;j<=len-1;++j){
        //int k = find_index(data,j);
        int k = data[j].second;
        for(int i=0;i<j;++i){
                if(i<=k && k<=j-1 && MIS[i][k-1]+1+MIS[k+1][j-1] > MIS[i][j-1]){
                    //case3
                    if(i == k){
                        //cout<<"case3 ";
                        //cout<<"(i,j,k)=("<<i<<","<<j<<","<<k<<")"<<endl;
                        MIS[i][j] = 1+MIS[i+1][j-1];
                        CASE[i][j] = 3;
                    }
                    //case2
                    else{
                        //cout<<"case2 ";
                        //cout<<"(i,j,k)=("<<i<<","<<j<<","<<k<<")"<<endl;
                        MIS[i][j] = MIS[i][k-1]+1+MIS[k+1][j-1];
                        CASE[i][j] = 2;
                    }
                }
                //case1
                else{
                    //cout<<"case1 " ;
                    //cout<<"(i,j,k)=("<<i<<","<<j<<","<<k<<")"<<endl;
                    MIS[i][j] = MIS[i][j-1]; 
                    CASE[i][j] = 1;
                }
        }
    }
    return MIS[0][len-1];
}
void getChord(int i, int j, vector< pair<int,int> >data, int **CASE)
{
	while( j-i >= 0 )
	{
		if (CASE[i][j] == 2){
			int k = data[j].second;
			chord_set.push_back(make_pair(k,j));
			getChord(k, j-1, data, CASE);
			j = k - 1;
		}
		else if(CASE[i][j] == 3){
			int k = data[j].second;
			chord_set.push_back(make_pair(k,j));
			getChord(i+1, j-1, data, CASE);
			j = i - 1;
		} 
		else { j--; }
	}
}

int main(int argc, char* argv[])
{
    clock_t tStart = clock();
    vector< pair<int,int> > dict;
    int len = 0;
    if(argc != 3) {
        help_message(argc-1);
        return 0;
    }
    ifstream fin(argv[1]);
    if (!fin) { 
        cerr<<"error: cannot open \""<<argv[1]<<"\""<<endl; 
        exit(1);
    }
    else{
        dict = read(argv[1]);
        len = dict.size()/2;
    }
    int **MIS = mallocMatrix(2*len,2*len);
    int **CASE = mallocMatrix(2*len,2*len);
    int mps = create_MIS_Table(dict,2*len,MIS,CASE);
	getChord(0, 2*len-1, dict, CASE);
    cout<<"Maximum Planar Subset of Chords: "<<mps<<endl;
    sort(chord_set.begin(),chord_set.end());
    //print output
    /*cout<<mps<<endl;
    for(int i=0;i<mps;++i){
        cout<<chord_set[i].first<<" "<<chord_set[i].second<<endl;
    }*/
    writeFile(argv[2],chord_set);
    printf("execution time: %.2fs\n",(double)(clock()-tStart)/CLOCKS_PER_SEC);
    return 0;
}
