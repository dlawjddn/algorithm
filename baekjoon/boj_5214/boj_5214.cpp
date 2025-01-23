#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, connected, hypertube_cnt;
vector<vector<int> > maps;

void print_maps() {
    for(int i=1; i<=node_cnt; i++) {
        cout<<"node"<<i<<": \n";
        for(int x=0; x<maps[i].size(); x++) {
            cout<<maps[i][x]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    cin>>node_cnt>>connected>>hypertube_cnt;
    maps.resize(node_cnt + 1);
    for(int i=0; i<hypertube_cnt; i++) {
        vector<int> hypertube(connected);
        for(int j=0; j<connected; j++) {
            cin>>hypertube[j];
        }
        for(int a=0; a<hypertube.size(); a++) {
            for(int b=0; b<hypertube.size(); b++) {
                if (a == b) continue;
                maps[hypertube[a]].push_back(hypertube[b]);
            }
        }
    }
    print_maps();
}