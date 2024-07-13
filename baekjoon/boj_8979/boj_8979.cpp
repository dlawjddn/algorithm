/**
 * @file boj_8979.cpp
 * @brief 백준 silver5 올림픽 
 * @version 0.1
 * @date 2024-07-13
 * 
 * @copyright Copyright (c) 2024
 * 
 * 일단 처음에 틀렸다.. 생각해보니 중복을 제거하여 순위를 센다는건 참 좋았는데
 * 나보다 앞선 순서에서 중복이 발생할 경우에 내 순위가 달라진다는 점을 놓쳐서 틀렸다.
 * 
 * 따라서 이 문제는 중복을 허용하고 일치하는 것이 나오자마자 리턴하면 제대로된 순위를 알 수 있을 뿐 아니라 앞선 사람들에게 중복이 존재하는 경우에도 잘 파악할 수 있다.
 * 
 * 이번에는 multiset<>이나 set<>을 사용할 때 custom compare를 만드는 방법에 대해서 알게 되었다.
 * 
 */
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct MedalCompare {
    bool operator()(vector<int> a, vector<int> b) const {
        if (a[0] != b[0]) return a[0] > b[0];  // 금메달 비교
        if (a[1] != b[1]) return a[1] > b[1];  // 은메달 비교
        return a[2] > b[2];                    // 동메달 비교
    }
};

int country_cnt, country;
vector<int> dest_scores;
multiset<vector<int>, MedalCompare> s;

int main()
{
    cin >> country_cnt >> country;
    for (int i = 0; i < country_cnt; i++) {
        int country_num; cin >> country_num;
        vector<int> scores(3);
        for (int j = 0; j < 3; j++) cin >> scores[j];
        s.insert(scores);
        if (country_num == country) dest_scores = scores;
    }

    int grade = 1;
    for (auto scores : s) {
        if (scores == dest_scores) {
            cout << grade;
            break;
        }
        grade++;
    }
    return 0;
}
