/**
 * @file boj_1092.cpp
 * @brief 백준 gold5 배
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 * 그리디.. 어렵다.. 
 * 
 * 이 문제를 통해 느낀 점..
 * 
 * 그리디를 풀면 왠지 모르게 n의 시간복잡도로 해결해야 한다는 강박이 있는 것 같다..
 * 항상 최선의 상황을 선택해야하기 때문이라고 생각을 해서 그런지는 몰라도.. 이 부분에서 실수가 발생한다고 생각한다.
 * 
 * 하지만 이 문제는 크레인의 개수가 최대 50개 박스의 개수가 10000개로, 이중 반복문을 통해도 500,000이고, 
 * 한 크레인이 모든 박스를 옮기는 경우가 가장 많은 이동횟수를 가지기 때문에 최대 작업량이 n(n+1) / 2이다.
 * 따라서 대략적으로 약 3억정도의 작업량이 존재하고 반복문 안의 로직이 간단하기 때문에 시도해볼법하다..
 * 
 * 결국 이 문제는 각 크레인들이 남아있는 박스들 중 자신이 들 수 있는 박스 중 가장 무거운 박스를 1개씩 들어서
 * 그 반복횟수가 크레인들이 가질 수 있는 최소의 횟수를 의미하게 된다..
 * 
 * 그리디는 항상 문제 풀 때마다 너무 아쉽고, 은근 간단한데 내가 못푸니까 참 힘든 문제인 것 같다..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int crane_cnt, box_cnt, answer = 0;
vector<int> cranes;
vector<int> boxes;

int main(){
    cin>>crane_cnt;
    cranes.resize(crane_cnt);
    for(int i=0; i<crane_cnt; i++) cin>>cranes[i];
    cin>>box_cnt;
    boxes.resize(box_cnt);
    for(int i=0; i<box_cnt; i++) cin>>boxes[i];

    sort(cranes.begin(), cranes.end());
    sort(boxes.begin(), boxes.end());

    if (cranes.back() < boxes.back()) {
        cout<<"-1"; return 0;
    }

    while(!boxes.empty()) {
        answer++;
        for(int i=cranes.size()-1; i>=0; i--) {
            for(int j=boxes.size()-1; j>=0; j--) {
                if (cranes[i] >= boxes[j]) {
                    boxes.erase(boxes.begin() + j);
                    break;
                }
            }
        }
    }
    cout<<answer;
}