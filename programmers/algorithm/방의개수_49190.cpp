/**
 * @file 방의개수_49190.cpp
 * @brief 프로그래머스 lv.5 방의 개수
 * @version 0.1
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 * X자로 교차하는 경우에 방이 2개 생길 수 있다는 점이 이 문제의 킥이라고 생각된다
 * 그리고 어떤 점 A에서 B로 가고, B에서 A를 가는 경우에 공간이 생기지 않기 때문에 이런 경우에 예외처리가 들어가야 한다..
 * 
 * 두 방법 둘 다 생각 못했는데.. 사실 이 방법은 한번씩 접해본 방법이긴 하다..
 * 
 * 깊이가 아직 얕구나 정우야..
 * 
 */
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

int y=0, x=0;
int moveY[8]={-1, -1, 0, 1, 1, 1, 0, -1}, moveX[8]={0, 1, 1, 1, 0, -1, -1, -1};
set<pair<int, int> > visited_node;
set<pair<pair<int, int>, pair<int, int> > > visited_edge;

int solution(vector<int> arrows) {
    int answer = 0;
    visited_node.insert({y, x});
    for(auto dir : arrows) {
        int ny = y + moveY[dir];
        int nx = x + moveX[dir];
        // 중간점이 이미 들른 지점인 경우
        if (visited_node.find({ny, nx}) != visited_node.end()
           && visited_edge.find({{y, x}, {ny, nx}}) == visited_edge.end()) {
            answer += 1;
        }
        visited_node.insert({ny, nx});
        visited_edge.insert({{y, x},{ny, nx}});
        visited_edge.insert({{ny, nx},{y, x}});
        
        int nny = ny + moveY[dir];
        int nnx = nx + moveX[dir];
        // 끝점이 이미 들른 지점인 경우
        if (visited_node.find({nny, nnx}) != visited_node.end()
           && visited_edge.find({{ny, nx}, {nny, nnx}}) == visited_edge.end()) {
            answer += 1;
        }
        visited_node.insert({nny, nnx});
        visited_edge.insert({{ny, nx},{nny, nnx}});
        visited_edge.insert({{nny, nnx},{ny, nx}});
        y = nny;
        x = nnx;
    }
    return answer;
}