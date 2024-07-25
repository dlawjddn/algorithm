/**
 * @file boj_21608.cpp
 * @brief 백준 gold5 상어 초등학교
 * @version 0.1
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int sq_size, answer = 0, moveY[4] = {0, 1, 0, -1}, moveX[4] = {1, 0, -1, 0};
vector<int> students;
vector<vector<bool>> likes;
vector<vector<int>> classroom;

void print_classroom() {
    for (int y = 0; y < sq_size; y++) {
        for (int x = 0; x < sq_size; x++) {
            cout << classroom[y][x] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}


int solve() {
    int result = 0;
    for(int y = 0; y < sq_size; y++) {
        for(int x = 0; x < sq_size; x++) {
            int cnt_like = 0;
            for(int d = 0; d < 4; d++) {
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (check_outside(ny, nx)) continue;
                if (likes[classroom[y][x]][classroom[ny][nx]]) cnt_like++;
            }
            if (cnt_like == 0) result += 0;
            else if (cnt_like == 1) result += 1;
            else if (cnt_like == 2) result += 10;
            else if (cnt_like == 3) result += 100;
            else if (cnt_like == 4) result += 1000;
        }
    }
    return result;
}

void dfs(int student_idx) {
    if (student_idx == students.size()) {
        answer = max(answer, solve());
        return;
    }
    int near_like = -1, near_empty = -1;
    int posy = -1, posx = -1;
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            if (classroom[y][x] != 0) continue;

            int temp_like = 0, temp_empty = 0;
            for(int d=0; d<4; d++) {
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (check_outside(ny, nx)) continue;
                if (classroom[ny][nx] == 0) temp_empty++;
                else {
                    if (likes[students[student_idx]][classroom[ny][nx]]) temp_like++;
                }
            }
            if (near_like <= temp_like) {
                if (near_like < temp_like) {
                    near_like = temp_like;
                    near_empty = temp_empty;
                    posy = y;
                    posx = x;
                } else {
                    if (near_empty < temp_empty) {
                        near_empty = temp_empty;
                        posy = y;
                        posx = x;
                    }
                }
            }

            // classroom[posy][posx] = students[student_idx];
            // dfs(student_idx + 1);
            // classroom[posy][posx] = 0;
        }
    }
    if (posy != -1 && posx != -1) {
        classroom[posy][posx] = students[student_idx];
        dfs(student_idx + 1);
        classroom[posy][posx] = 0;
    }
}

int main() {
    cin >> sq_size;
    students.resize(sq_size * sq_size);
    likes.resize(sq_size * sq_size + 1, vector<bool>(sq_size * sq_size + 1, false));
    classroom.resize(sq_size, vector<int>(sq_size, 0));

    for (int i = 0; i < (sq_size * sq_size); i++) {
        cin >> students[i];
        for (int j = 0; j < 4; j++) {
            int like_student; 
            cin >> like_student;
            likes[students[i]][like_student] = true;
        }
    }

    dfs(0);
    cout<<answer;
    return 0;
}
