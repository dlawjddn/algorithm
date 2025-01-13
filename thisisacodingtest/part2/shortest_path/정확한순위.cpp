#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int student_cnt, compare_cnt, answer = 0;
vector<vector<int> > result;

int main() {
    cin>>student_cnt>>compare_cnt;
    result.resize(student_cnt + 1, vector<int>(student_cnt + 1, 0));
    for(int i=0; i<compare_cnt; i++) {
        int s1, s2; cin>>s1>>s2;
        result[s2][s1] = 1;
        result[s1][s2] = -1;
    }
    for(int i=1; i<=student_cnt; i++) {
        for(int j=1; j<=student_cnt; j++) {
            for(int k=1; k<=student_cnt; k++) {
                if (result[j][i] != 0 && result[j][i] == result[i][k]) {
                    result[j][k] = result[j][i];
                }
            }
        }
    }
    for(int y=1; y<=student_cnt; y++) {
        int cnt = 0;
        for(int x=1; x<=student_cnt; x++) {
            cnt += (result[y][x] == 0) ? 0 : 1;
        }
        if (cnt == student_cnt - 1) answer++;
    }
    cout<<answer;

}