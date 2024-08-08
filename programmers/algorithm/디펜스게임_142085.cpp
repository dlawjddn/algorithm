/**
 * @file 디펜스게임_142085.cpp
 * @brief 프로그래머스 lv.2 디펜스 게임
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * 왜 이 생각을 못했을까.. 우선순위 큐를 사용해야 한다는 것을 전혀 생각하지 못했다...
 * 
 * 체력이 낮은 순으로 우선순위를 두고, 
 * 그때 우선순위 큐의 사이즈가 내가 방어할 수 있는 개수를 넘어간다면 나의 누적 데미지에 더한다.
 * 
 * 결국 큐는 내가 감당할 지나갈 수 '무적권'을 사용할 수 있는 적들의 데미지가 존재하게 된다.
 * 따라서 그 개수가 넘어갈 경우 가장 낮은 데미지를 누적 데미지에 더하는 것이다.
 * 
 * 이때 누적 데미지가 나의 체력을 넘어간다면 그때의 라운드를 리턴한다..
 * 
 * 아 이거 괜찮은 문제인데.. 너무 아쉽다..
 * 
 * 
 */
#include <string>
#include <vector>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int> > pq;

int solution(int n, int k, vector<int> enemy) {
    int answer = 0;
    for(int i=0; i<enemy.size(); i++) {
        pq.push(enemy[i]);
        if (pq.size() > k) {
            answer += pq.top();
            pq.pop();
        }
        if (answer > n) return i;
    }
    return enemy.size();
}