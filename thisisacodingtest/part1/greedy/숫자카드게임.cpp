#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > maps;

int main() {
    int answer = 0, sizeY, sizeX; cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
        }
        int temp_min = *min_element(maps[y].begin(), maps[y].end());
        answer = max(answer, temp_min);
    }
    cout<<answer;
}