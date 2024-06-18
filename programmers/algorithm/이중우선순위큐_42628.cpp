/**
 * @file 이중우선순위큐_42628.cpp
 * @brief 프로그래머스 lv3 이중 우선 순위 큐
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이 문제를 보자마자 엥 이거 우선순위 큐 쓸게 아니라 set 쓰면 편할거 같은데라는 생각을 했다.
 * 하지만 중복을 보장해야해서 어떻게.. 그리고 최소와 최대를 어떻게 찾아야하나가 고민이었다.
 * 하지만 두번째 문제의 경우 너무 쉽게 해결됐다. set은 자동으로 오름차순으로 정렬이 되는 자료구조이기 때문에
 * set.begin()과 set.end()를 사용하면 최소값과 최대값을 찾을 수 있었다. 
 * 
 * 첫번째 문제의 경우에는 set과 유사하지만 더 중복이 가능하고 정렬도 내가 선택할 수 있는 multiset<> 자료구조를 통해 해결할 수 있었다.
 * (다시 찾아본 결과 set, multiset 모두 정렬의 기준을 선택할 수 있다. greater<자료형>, less<자료형>을 통해 가능하다)
 * 
 * 세번째.. 유레카를 외친 부분이다. sstream 라이브러리를 통해서 split을 매우 편하게 할 수 있다. (물론 공백과 줄바꿈에 한해서 가능하다. 그래도 이게 어디냐!)
 * stringstream을 사용하면 공백과 줄바꿈을 통해서 split을 할 수 있으며 stringstream을 input처럼 받으면 가능하다... 진짜 이런게 있다니..ㅠㅠ 
 * 
 */
#include <string>
#include <vector>
#include <set>
#include <sstream>
using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    multiset<int, less<int> > ms;
    char order;
    int num;
    for(string operation : operations){
        stringstream ss(operation);
        ss >> order;
        ss >> num;
        if (order == 'I')
            ms.insert(num);
        else {
            if (num == 1 && !ms.empty()) { // 최대값 삭제
                ms.erase(--ms.end());
            } else if (num == -1 && !ms.empty()) { // 최소값 삭제
                ms.erase(ms.begin());
            }
        }
    }
    if (ms.empty()){
        answer.push_back(0);
        answer.push_back(0);
    } else {
        answer.push_back(*(--ms.end()));
        answer.push_back(*(ms.begin()));
    }
    
    return answer;
}