#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sizeX = 0, sizeY = 0, sq_size = 0, star_cnt = 0, max_protect = 0;
vector<pair<int, int> > stars;

int main() {
    cin>>sizeX>>sizeY>>sq_size>>star_cnt;
    for(int i=0; i<star_cnt; i++) {
        int x; cin>>x;
        int y; cin>>y;
        stars.push_back(make_pair(x, y));
    }
    for(int i=0; i<stars.size(); i++) {
        int cnt = 0;
        int sx = stars[i].first;
        int sy = stars[i].second;
        int fx = stars[i].first + sq_size;
        int fy = stars[i].second + sq_size;
        for(int j=0; j<stars.size(); j++) {
            if (sx <= stars[j].first && stars[j].first <= fx && sy <= stars[j].second && stars[j].second <= fy) cnt++;
        }
        max_protect = max(max_protect, cnt);
    }
    cout<<star_cnt - max_protect;
}