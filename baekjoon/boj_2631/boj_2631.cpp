#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int student_cnt;
vector<int> students;
vector<int> dp;

int main() {
    cin>>student_cnt;
    dp.resize(student_cnt, 1);
    for(int i=0; i<student_cnt; i++) {
        int student; cin>>student;
        students.push_back(student);
    }

    for(int i=0; i<students.size(); i++) {
        for(int j=0; j<i; j++) {
            if (students[j] < students[i]) dp[i] = max(dp[i], dp[j]+1);
        }
    }
    cout<<(student_cnt - *max_element(dp.begin(), dp.end()));
}