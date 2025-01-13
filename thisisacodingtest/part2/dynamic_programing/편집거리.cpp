#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_DISTANCE 1001

string input, target;
int edit_distance[MAX_DISTANCE][MAX_DISTANCE];

int main() {
    cin >> input >> target;

    int in_n = input.length();
    int tar_n = target.length();

    // 초기화
    edit_distance[0][0] = 0;
    for (int i = 1; i <= in_n; i++)
        edit_distance[i][0] = i;
    for (int i = 1; i <= tar_n; i++)
        edit_distance[0][i] = i;

    // 편집 거리 계산
    for (int i = 1; i <= in_n; i++) {
        for (int j = 1; j <= tar_n; j++) {
            if (input[i - 1] == target[j - 1]) {
                edit_distance[i][j] = edit_distance[i - 1][j - 1];
            } else {
                edit_distance[i][j] = min({
                    edit_distance[i - 1][j],       // 삭제
                    edit_distance[i][j - 1],       // 삽입
                    edit_distance[i - 1][j - 1]    // 치환
                }) + 1;
            }
        }
    }

    // 결과 출력
    cout << edit_distance[in_n][tar_n];
    return 0;
}
