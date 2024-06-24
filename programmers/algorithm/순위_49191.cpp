/**
 * @file 순위_49191.cpp
 * @brief 프로그래머스 lv.3 순위 
 * @version 0.1
 * @date 2024-06-25
 * 
 * @copyright Copyright (c) 2024
 * 
 * 플로이드 와샬에 대해서 알게 된 문제이다.. 이 문제는 사실 플로이드 와샬 문제라는 것을 파악하면 굉장히 쉽게 풀 수 있는 문제인 것 같다.
 * 
 * 플로이드 와샬?
 * -> 플로이드 와샬은 2차원 배열을 통해서 주어진 모든 정점 간의 최소 거리를 나타낸다. 3중 반복문을 사용하며 기준이 되는 정점(i)을 중간으로 j -> i -> k가 최소가 될 때 값을 갱신 시킨다.
 * j -> i -> k는 j에서 i를 거쳐 k를 가는 것이 j -> k 보다 최단거리라면~ 이라는 의미이다.
 * 본 문제에서는 j가 i를 이겼고, i가 k를 이기면 ~ j가 k도 이긴다 라는 의미로 사용
 * 
 * 이러한 점을 이용하여 초기 경기 결과를 저장하고 플로이드 와샬을 응용하여 최단거리가 아닌 승리 여부를 저장한다. (해당 문제에서는 승리만 저장)
 * 따라서 위에도 설명이 있지만, i를 기준으로 i가 j한테 졌지만, i가 k를 이긴다면 j는 k도 이긴다 라는 의미이다.
 * 
 * 따라서 승리 여부를 저장하는 배열에 모든 값을 저장한 뒤, 한 사람에 대해서 records[i][j] or records[j][i] 가 하나라도 참이라면
 * i가 j를 이기거나 진 결과이기 때문에 승부가 결정난 상황을 의미한다. 따라서 승부가 결정한 경우를 모두 세어서 n - 1와 같다면 본인을 제외한 모든 결과가 나온 것이기 때문에 순위를 특정할 수 있다.
 * 
 * 플로이드 와샬의 특징
 * 
 * 1. 플로이드 와샬을 사용하는 문제는 3중 반복문을 사용해야 하기 때문에 시간복잡도가 n^3이다. 따라서 제시되는 배열의 사이즈가 n^3을 적용해도 괜찮을 수준으로 나타난다. (ex. 100)
 * 2. 특정한 부분이 아닌(ex. 최소의 결과, 최단거리) 전체적인 흐름을 물어보는 문제이다. 플로이드 와샬의 특징은 모든 정점에 대해서 결과를 나타내는 것이기 때문에 플로이드 와샬을 사용해야 하는 문제라면
 *    지금 문제처럼 순위를 특정할 수 있는 사람의 수 혹은 어디로 갈지 모르지만 or 두 번 이상의 방문을 허용~ 와 같이 전체 경우의 수를 모두 파악해야 하는 문제를 낸다.
 *  기억하자! 플로이드 와샬은 정점 i에 대해서 j -> i -> k 이다. 그리고 제시되는 n이 1000 미만일 것이다. 대충.. 500정도..? ㅋㅋ
 * 
 */
#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    vector<vector<bool> > records(n+1, vector<bool>(n+1, false));
    for (auto result : results) {
        int winner = result[0];
        int loser = result[1];
        records[winner][loser] = true;
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            for(int k=1; k<=n; k++) {
                if (records[j][i] && records[i][k])
                    records[j][k] = true;
            }
        }
    }
    for(int i=1; i<=n; i++) {
        int cnt = 0;
        for(int j=1; j<=n; j++) {
            if (records[i][j] || records[j][i]) cnt++;
        }
        if (cnt == n - 1) answer += 1;
    }
    return answer;
}