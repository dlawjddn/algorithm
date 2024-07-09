/**
 * @file day1.cpp
 * @brief 엘리스 알고리즘 대회 DAY2 - 정리 정돈을 좋아하는 k씨
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * 
 * 
시간 제한: 1초
정리 정돈을 좋아하는 k씨의 본명은 아무도 모릅니다. 사람들은 k씨의 특이한 행동 2가지 때문에 그를 '정리 정돈을 좋아하는 k씨'라고 부릅니다. 그 두 가지 행동은 그가 숫자를 정리하는 일을 하면 아무 규칙없이 나열되어 있는 숫자중 범위를 정한 후 무조건 오름차순으로 정리한다는 것, 그리고 오름차순으로 정리된 숫자 중 k번째 숫자를 선택한다는 것입니다

예를 들어 a={1,7,6,8,1,6,4,5}라는 수열이 있습니다. 정리정돈을 좋아하는 k씨는 범위를 2에서 5로 정하고, k를 2라고 정했습니다.
그러면 ka={7,6,8,1}이 되고, 이것을 오름차순으로 정리를 하면 ka={1,6,7,8}이 됩니다. 그리고 k씨는 2번째인 6을 선택합니다.

배열 a가 주어지고, k씨가 일을 한 횟수가 주어졌을 때, k씨가 고른 숫자를 출력하는 프로그램을 작성하세요.


지시사항
입력
첫째 줄에 배열의 크기인 정수 n과 k씨가 일한 횟수인 정수 m을 입력합니다.
1≤n≤10000

1≤m≤500
둘째 줄에는 배열에 포함된 정수를 순서대로 입력합니다. 각 정수는 절댓값이 200을 넘지 않는 정수입니다.
다음 줄 부터 m개 줄에 걸쳐 k씨가 고른 범위인 정수 i, j와 정수 k를 입력합니다.
1≤i≤j≤n

1≤k≤j−i+1
출력
k씨가 일할 때마다 k씨가 선택한 숫자를 한 줄에 하나씩 출력합니다.
입력 예시
8 3
1 7 6 8 1 6 4 5
1 5 3
2 6 2
4 8 3
Copy
출력 예시
6
6
5


* 
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr_size, work_cnt;
vector<int> arr;

int main() {
    cin>>arr_size>>work_cnt;
    arr.resize(arr_size + 1);
    for(int i=0; i<arr_size; i++) {
        cin>>arr[i];
    }
    for(int i=0; i<work_cnt; i++) {
        int start, end, idx; cin>>start>>end>>idx;
        vector<int> work = arr;
        sort(work.begin() + start - 1, work.begin() + end);
        cout<<work[start + idx - 2]<<"\n";
    }
}