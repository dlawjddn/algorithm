/**
 * @file 양궁대회_92342.cpp
 * @brief 프로그래머스 lv.2 2022 카카오 공채 양궁대회
 * @version 0.1
 * @date 2024-08-12
 * 
 * @copyright Copyright (c) 2024
 * 
 * dfs로 모든 경우에 대해서 파악하는 건 파악했지만.. 디테일하게 다가가지 못한 문제..
 * 
 * 1. 111~ 부터 10~~까지의 모든 경우의 수를 세려고 했었음
 * - 이렇게 되면 10자리 숫자에 대해서 최대 10^10의 경우에 대해서 고려하게 되기 때문에 무조건 시간 초과가 발생한다..
 * - 당연히 안되는 줄 알고는 있었지만, 그렇다면 어떻게 해결해가는가? 에 대해서 생각이 나지 않은 문제..
 * 
 * -> 문제의 특징을 잘 파악하자!
 * -> 이 문제의 경우에는 특정 점수에 상대보다 하나라도 많이 쏘면 되는 문제이기 때문에, 상대가 10점에 1개를 쏘았다면, 내가 10점에서 이길 수 있는 최적의 방법은 10점에 2개를 쏘는 것이다. 
 * -> 1개를 쏘거나 3개를 쏘는 경우에는 점수에 반영되지 않는, 즉, 무의미한 화살이기 때문에 고려하지 않는 것이 중요하다
 * -> 이 방법을 통해 약 10^10의 경우의 수에서 굉장히 많이 줄어든 것을 알 수 있다.
 * 
 * 
 * 2. 선택하지 않는 경우에 대한 판단
 * - 1번까지 이해하고, 이를 내가 알고 있던 dfs에 적용하려고 했는데, 내가 기존에 해왔던 dfs는 모든 경우에서 선택을 하는 경우였다. 따라서 큰 점수 차이로 이기기 위해서는 당장은 지더라도,
 * - 화살을 아껴서 다음 점수에서 승리를 따내는 것이 중요했다.
 * - 이를 하기 위해서는 큰 점수더라도 져야하는 경우가 필요했다. 그렇다면, 이걸 어떻게 처리할 것인가에서 생각이 나지 않았다.
 * 
 * -> 말 그대로를 구현하자
 * -> 단순히 생각해보자, 내가 그동안 dfs를 매번 선택하는 경우만 고려했다면, 지금은 선택하는 경우와 선택하지 않는 경우를 모두 고려해야 한다. 
 * -> 따라서 이 문제는 다음 dfs를 들어가는 로직에서 현재의 점수를 이기는 경우와, 이기지 않는 경우를 모두 고려하면 모든 경우의 수를 파악이 가능하다.
 * -> 선택하는 경우에는 선택이 가능한 경우에 넣고, 선택하지 않는 경우는 모든 경우에 대해서 dfs를 진행하면 된다.
 * 
 * 
 */
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int final_diff = -1;
vector<int> my_result;
vector<int> enemy;
vector<int> me;

void print_me() {
    for(auto cnt : me) cout<<cnt<<" ";
    cout<<"\n";
}

pair<int, int> check_score() {
    pair<int, int> scores = {0,0};
    for(int i=0; i<=10; i++) {
        int score = 10 - i;
        if (enemy[i] == me[i]) {
            if (me[i] == 0) continue;
            else scores.first += score;
        } else {
            if (enemy[i] < me[i]) scores.first += score;
            else scores.second += score;
        }
    }
    return scores;
}

void check_result() {
    auto[my_score, enemy_score] = check_score();
    int diff = my_score - enemy_score;
    if (diff <= 0 || final_diff > diff) {
        return ;
    }
    if (final_diff == -1) { // 처음 승리하는 경우
        final_diff = diff;
        my_result = me;
    } else { // 두 번 이상 승리하는 경우
        if (final_diff == diff) { // 점수가 동일하여 낮은 점수를 많이 쏜 것으로 확인해야함
            for(int i=10; i>=0; i--) {
                if (me[i] == my_result[i]) continue;
                else {
                    my_result = (me[i] < my_result[i]) ? my_result : me;
                    break;
                }
            }
        } else { // 지금 점수가 더 높음
            final_diff = diff;
            my_result = me;
        }
        
    }
}

void dfs(int idx, int cnt, int total_cnt) {
    if (cnt == total_cnt) { // 모든 화살을 다 쏜 경우
        check_result();
        return ;
    }
    int rest_cnt = total_cnt - cnt; // 앞으로 쏠 수 있는 화살의 개수
    if (idx == 10) { // 0점을 쏴야함
        me[idx] = rest_cnt;
        dfs(idx + 1, cnt + rest_cnt, total_cnt);
        me[idx] = 0;
    } else { // 0점 이외의 점수를 쏴야함
        if (enemy[idx] + 1 <= rest_cnt) { // 내가 쏴야하는 개수를 쏠 수 있음
            me[idx] = enemy[idx] + 1;
            dfs(idx + 1, cnt + enemy[idx] + 1, total_cnt);
            me[idx] = 0;
        }
        dfs(idx + 1, cnt, total_cnt); // 지금 쏴야하는 점수를 쏘지 않고 넘김
    }
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer;
    enemy = info;
    me.resize(11, 0);
    dfs(0, 0, n);
    if (final_diff == -1) return {-1};
    return my_result;
}