/**
 * @file 도둑질_42897.cpp
 * @brief 프로그래머스 lv.4 도둑질
 * @version 0.1
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 * 원형 구조에서 하나를 선택할 때, 양 옆에 원소를 접근하지 못하는 경우 -> 이 문제 종종 보인다.
 * 
 * 결국 중요한건 첫번째 원소를 선택? 두번째 원소를 선택하나에 따라 답이 달라진다.
 * 이때 중요한 것은 첫번째 원소를 선택하는 경우, dp 배열에 두번째에도 값을 초기화 해줘야 가능하다..
 * 
 * 이 문제 확실히 알아가자 이거 코테에서 한번쯤은 나올거 같긴 하다.
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> take_first;
vector<int> take_second;

int solution(vector<int> money) {
    take_first.resize(money.size(), 0);
    take_second.resize(money.size(), 0);
    
    take_first[0] = money[0];
    take_first[1] = take_first[0];
    take_second[1] = money[1];
    
    // 각 경우에서의 dp 배열 채우기
    for(int i=2; i<money.size()-1; i++) {
        take_first[i] = max(take_first[i-1], take_first[i-2] + money[i]);
    }
    for(int i=2; i<money.size(); i++) {
        take_second[i] = max(take_second[i-1], take_second[i-2] + money[i]);
    }
    return max(*max_element(take_first.begin(), take_first.end()), *max_element(take_second.begin(), take_second.end()));
}