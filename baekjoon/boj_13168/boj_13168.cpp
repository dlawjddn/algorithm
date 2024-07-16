/**
 * @file boj_13168.cpp
 * @brief 백준 gold3 내일로 여행
 * @version 0.1
 * @date 2024-07-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

#define INF 987654321

using namespace std;

int node_cnt, ticket_cost, trip_cnt, edge_cnt;
map<string, int> stations;
vector<int> trip_path;
vector<vector<int> > normal_map;
vector<vector<int> > ticket_map;

void print_path() {
    for(auto p : trip_path) cout<<p<<" ";
    cout<<"\n";
}

void print_normal_map(){
    for(int y=0; y<node_cnt; y++) {
        for(int x=0; x<node_cnt; x++) {
            cout<<normal_map[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void print_ticket_map() {
    for(int y=0; y<node_cnt; y++) {
        for(int x=0; x<node_cnt; x++) {
            cout<<ticket_map[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

int main() {
    cin>>node_cnt>>ticket_cost;
    normal_map.resize(node_cnt, vector<int>(node_cnt, INF));
    ticket_map.resize(node_cnt, vector<int>(node_cnt, INF));
    for(int i=0; i<node_cnt; i++) {
        string name; cin>>name;
        stations.insert(make_pair(name, i));
    }
    cin>>trip_cnt;
    for(int i=0; i<trip_cnt; i++) {
        string name; cin>>name;
        auto station = stations.find(name);
        if (station != stations.end()) trip_path.push_back(station->second);
    }
    cin>>edge_cnt;
    for(int i=0; i<edge_cnt; i++) {
        string traffic; cin>>traffic;
        string city1; cin>>city1;
        string city2; cin>>city2;
        int cost; cin>>cost;
        cost *=2;
        int sale_cost = cost;
        if (traffic == "ITX-Saemaeul" || traffic == "ITX-Cheongchun" || traffic == "Mugunghwa") {
            sale_cost = 0;
        } else if (traffic == "V-Train" || traffic == "S-Train") {
            sale_cost /= 2;
        }
        auto city1_pointer = stations.find(city1);
        int city1_idx = city1_pointer->second;

        auto city2_pointer = stations.find(city2);
        int city2_idx = city2_pointer->second;

        normal_map[city1_idx][city2_idx] = min(normal_map[city1_idx][city2_idx], cost);
        normal_map[city2_idx][city1_idx] = min(normal_map[city2_idx][city1_idx], cost);
        ticket_map[city1_idx][city2_idx] = min(ticket_map[city1_idx][city2_idx], sale_cost);
        ticket_map[city2_idx][city1_idx] = min(ticket_map[city2_idx][city1_idx], sale_cost);
    }
    // 플로이드 워셜 초기 작업
    for(int i=0; i<node_cnt; i++) {
        normal_map[i][i] = 0;
        ticket_map[i][i] = 0;
    }
    // 플로이드 워셜
    for(int i=0; i<node_cnt; i++) {
        for(int j=0; j<node_cnt; j++) {
            for(int k=0; k<node_cnt; k++) {
                normal_map[j][k] = min(normal_map[j][k], normal_map[j][i] + normal_map[i][k]);
                ticket_map[j][k] = min(ticket_map[j][k], ticket_map[j][i] + ticket_map[i][k]);
            }
        }
    }
    int normal_cost = 0;
    ticket_cost *= 2;
    for(int i=0; i<trip_path.size()-1; i++) {
        int start = trip_path[i];
        int end = trip_path[i+1];
        normal_cost += normal_map[start][end];
        ticket_cost += ticket_map[start][end];
    }
    //cout<<normal_cost<<" "<<ticket_cost<<"\n";
    cout<<((normal_cost > ticket_cost) ? "Yes" : "No");
}