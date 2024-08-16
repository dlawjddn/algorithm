/**
 * @file 숫자게임_12987.cpp
 * @brief 프로그래머스 lv.3 숫자 게임
 * @version 0.1
 * @date 2024-08-16
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이분탐색을 사용하는 문제인지 아닌지 판단하는 또 다른 기준이 생겼다
 * 
 * 밑에 틀린 코드를 보면 선택한 인덱스를 지우는 것을 확인할 수 있다.
 * 하지만 erase함수가 log(n)의 시간이 걸리기 때문에 틀린 코드의 시간복잡도는 O(n * log(n + n))으로
 * 왜 시간초과가 나는지는 파악하기 힘들지만,, 시간초과가 발생한다. 
 * 
 * 그에 반면에 둘 다 정렬한 상태에서 자기보다 가장 가까운 큰 수를 확인하는 로직은 정확히 O(n + n) -> O(n)의 시간이 걸리기 때문에
 * 더 빠른 것은 확실하다
 * 
 * 결론적으로 이분탐색을 사용할 때는 O(n * log(n))의 시간복잡도로 해결할 수 있는 문제여야 가능하다는 점을 알게 되었다..
 * 이분 탐색을 할 때는 이분 탐색 외 로직을 추가하지 말자..!
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    int b_cnt = 0;
    for(int i=0; i<A.size(); i++) {
        while(b_cnt < B.size() && A[i] >= B[b_cnt]) b_cnt++;
        if (b_cnt < B.size()) {
            b_cnt++;
            answer++;
            if (b_cnt == B.size()) break;
        }
    }
    return answer;
}

/*
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    sort(B.begin(), B.end());
    for(int i=0; i<A.size(); i++) {
        int left = 0, right = B.size() - 1;
        int value = -1, idx = -1;
        while(left <= right) {
            int mid = (left + right) / 2;
            if (A[i] < B[mid]) {
                right = mid - 1;
                if (value == -1) {
                    idx = mid;
                    value = B[mid];
                } else {
                    if (value > B[mid]) {
                        idx = mid;
                        value = B[mid];
                    }
                }
            } else left = mid + 1;
        }
        if(idx != -1) {
            B.erase(B.begin() + idx);
            answer++;
        }
    }
    return answer;
}
*/