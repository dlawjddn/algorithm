/**
 * @file 거리두기확인하기_81302.cpp
 * @brief 프로그래머스 lv.2 2021 채용연계인턴십 거리두기 확인하기
 * @version 0.1
 * @date 2024-08-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int moveY[4] = {0,1,0,-1}, moveX[4]={1,0,-1,0};

bool check_outside(int y, int x) {
    return y < 0 || y >= 5 || x < 0 || x >= 5;
}

bool bfs(vector<string>& maps, int sy, int sx) {
    queue<pair<int, int> > q;
    vector<vector<bool> > visited(5, vector<bool>(5, false));
    q.push({sy, sx});
    visited[sy][sx] = true;

    while(!q.empty()) {
        auto [y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] || maps[ny][nx] == 'X') continue;
            int distance = abs(ny - sy) + abs(nx - sx);
            if (distance <= 2 && maps[ny][nx] == 'P') return false;
            if (distance < 2) {
                q.push({ny, nx});
                visited[ny][nx] = true;
            }
        }
    }
    return true;
}

int solve(vector<string>& place) {
    for(int y=0; y<place.size(); y++) {
        for(int x=0; x<place[y].size(); x++) {
            if (place[y][x] == 'P') {
                if(!bfs(place, y, x)) return 0;
            }
        }
    }
    return 1;
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    for(auto place : places) {
        answer.push_back(solve(place));
    }
    return answer;
}
/**
 * @file 거리두기확인하기_81302.cpp
 * @author your name (you@domain.com)
 * @brief 프로그래머스 lv.2 2021 채용연계인턴십 거리두기 확인하기
 * @version 0.1
 * @date 2024-09-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Info {
    int y, x, dist;
};
int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};

Info make_info(int y, int x, int cost) {
    Info info;
    info.y = y;
    info.x = x;
    info.dist = cost;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= 5 || x < 0 || x >= 5;
}

bool check_dist(int sy, int sx, vector<string>& maps) {
    queue<Info> q;
    vector<vector<bool> > visited(5, vector<bool>(5, false));
    q.push(make_info(sy, sx, 0));
    visited[sy][sx] = true;
    while(!q.empty()) {
        auto[y, x, cost] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int ncost = cost + 1;
            if (check_outside(ny, nx) || visited[ny][nx] || maps[ny][nx] == 'X' || ncost > 2) continue;
            if (maps[ny][nx] == 'P') return false;
            q.push(make_info(ny, nx, ncost));
            visited[ny][nx] = true;
        }
    }
    return true;
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    for(auto place : places) {
        // 사람들의 위치 파악
        vector<pair<int, int> > people;
        for(int y=0; y<place.size(); y++) {
            for(int x=0; x<place[y].size(); x++) {
                if (place[y][x] == 'P') people.push_back({y, x});
            }
        }
        bool success = true;
        for(auto person : people) {
            if (!check_dist(person.first, person.second, place)) {
                success = false;
                break;
            }
        }
        (success ? answer.push_back(1) : answer.push_back(0));
    }
    return answer;
}