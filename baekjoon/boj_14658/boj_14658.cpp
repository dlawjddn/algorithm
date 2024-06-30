/**
 * @file boj_14658.cpp
 * @brief 백준 gold3 하늘에서 별똥별이 빗발친다
 * @version 0.1
 * @date 2024-06-30
 * 
 * @copyright Copyright (c) 2024
 * 
 * 흠.. 점마다 시작점을 찾아서 트램펄린을 놓는건 파악했지만, 
 * 점들의 x,y 좌표들을 모두 조합하여 트램펄린의 시작점을 찾는 것을 놓쳤다..
 * 이 부분이 이해가 안 가서 고생했던 문제 ㅠ
 * 
 * 좀 더 깊이 고민해봐야겠다 이제..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sizeX = 0, sizeY = 0, sq_size = 0, star_cnt = 0, max_protect = 0;
vector<pair<int, int> > stars;
int main(){
    cin>>sizeX>>sizeY>>sq_size>>star_cnt;
    for(int i=0; i<star_cnt; i++) {
        int x; cin>>x;
        int y; cin>>y;
        stars.push_back(make_pair(x, y));
    }
    for(int i=0; i<stars.size(); i++) {
        for(int j=0; j<stars.size(); j++) {
            int cnt = 0;
            int sx = stars[i].first;
            int sy = stars[j].second;
            int fx = sx + sq_size;
            int fy = sy + sq_size;
            for(int k=0; k<stars.size(); k++) {
                if (sx <= stars[k].first && stars[k].first <= fx && sy <= stars[k].second && stars[k].second <= fy) cnt++;
            }
            max_protect = max(max_protect, cnt);
        }
    }
    cout<<star_cnt - max_protect;
}