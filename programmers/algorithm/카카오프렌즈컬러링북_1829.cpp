/**
 * @file 카카오프렌즈컬러링북_1829.cpp
 * @brief 프로그래머스 lv.2 2017 카카오코드 예선
 * @version 0.1
 * @date 2024-08-12
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이 문제 진짜 별로임
 * 
 */
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    
    
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    vector<int> groups;
    int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
    
    for(int sy=0; sy<m; sy++) {
        for(int sx=0; sx<n; sx++) {
            if (picture[sy][sx] == 0 || visited[sy][sx]) continue;
            int cnt = 1;
            queue<pair<int, int> > q;
            q.push({sy, sx});
            visited[sy][sx] = true;
            while(!q.empty()) {
                auto[y, x] = q.front(); q.pop();
                for(int d=0; d<4; d++) {
                    int ny = y + moveY[d];
                    int nx = x + moveX[d];

                    if (ny < 0 || ny >= m || nx < 0 || nx >= n) continue;
                    if (visited[ny][nx] || picture[y][x] != picture[ny][nx]) continue;

                    q.push({ny, nx});
                    visited[ny][nx] = true;
                    cnt++;
                }
            }
            groups.push_back(cnt);
        }
    }
    answer[0] = groups.size();
    answer[1] = *max_element(groups.begin(), groups.end());
    return answer;
}