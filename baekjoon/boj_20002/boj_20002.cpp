#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sq_size;
vector<vector<int> > maps;

int main() {
    int answer = -1000;
    cin>>sq_size;
    maps.resize(sq_size, vector<int>(sq_size, 0));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
        }
    }
    for(int k=1; k<=sq_size; k++) {
        for(int sy=0; sy<=sq_size - k; sy++) {
            for(int sx=0; sx<=sq_size - k; sx++) {
                int temp = 0;
                for(int y=sy; y<sy+k; y++) {
                    for(int x=sx; x<sx+k; x++) {
                        temp += maps[y][x];
                    }
                }
                answer = max(answer, temp);
            }
        }
    }
    cout<<answer;
}