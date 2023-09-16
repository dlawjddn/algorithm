#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Sig{
    char s, d;
    int first, second;
};
char map[20][20][20];
int sizeY[20], sizeX[20], visited[20][20][20];
queue<pair<int, int > > q;
Sig sig[20][10];

int main(){
    int testCase = 0;
    char c = '0';
    cout<< (int) c;
    /*
    while(1){
        cin>>sizeY[testCase]>>sizeX[testCase];
        if (sizeY[testCase] == 0 && sizeX[testCase] == 0) break;
        int sCnt = 0;
        for(int i = 0;  i<sizeY[testCase]; i++){
            string tmp;
            cin>>tmp;
            for(int j=0; j<sizeX[testCase]; j++){
                map[i][j][testCase] = tmp[j];
                if (map[i][j][testCase] >= '0' && map[i][j][testCase] <='9') sCnt++;
                else if (map[i][j][testCase] == 'A'){
                    q.push(make_pair(i,j));
                    visited[i][j][testCase] = 1;
                }
            }
        }
        for(int i=0; i<sCnt; i++){
            Sig s;
            cin>>s.s>>s.d>>s.first>>s.second;
            sig[testCase][i] = s;
        }
        testCase++;
    }
    */
}