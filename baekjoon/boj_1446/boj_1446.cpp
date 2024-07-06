/**
 * @file boj_1446.cpp
 * @brief 백준 silver1 지름길
 * @version 0.1
 * @date 2024-07-07
 * 
 * @copyright Copyright (c) 2024
 * 
 * 실버 문제라고 쉽게 생각했다가 결국 포기한 문제..
 * 
 * 생각을 다시 하게 된 문제..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int road_cnt, destination;
vector<int> costs;
vector<vector<pair<int, int> > > roads;

int main(){
    cin>>road_cnt>>destination;
    costs.resize(destination + 1, 987654321);
    roads.resize(destination + 1, vector<pair<int, int> >());
    for(int i=0; i<road_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        if (dest > destination) continue;
        if (dest - src < cost) continue;
        roads[dest].push_back(make_pair(src, cost));
    }
    costs[0] = 0;
    for(int i=1; i<=destination; i++) {
        if (roads[i].size() == 0) costs[i] = costs[i-1] + 1;
        else {
            for(int j=0; j<roads[i].size(); j++) {
                costs[i] = min(costs[i], min(costs[i-1] + 1, costs[roads[i][j].first] + roads[i][j].second));
            }
        }
    }
    cout<<costs[destination];
}