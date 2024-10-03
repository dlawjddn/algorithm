#include <iostream>
#include <vector>

using namespace std;

int solution(int n, vector<int> stations, int w){
    int answer = 0;
    int service_point = 1;
    for(int i=0; i<stations.size(); i++){
        // 기지국 왼쪽 구간
        int station_left = stations[i] - w;
        int check = station_left - service_point;
        // 시작점과 서비스 범위 동일 혹은 초과 -> 추가 없이 서비스 가능
        // 추가를 해야함 -> 개수 파악
        if (check > 0){
            answer += (check / (2*w + 1));
            if (check % (2*w + 1) != 0 )
                answer += 1;
        }
        service_point = stations[i] + w + 1;
    }
    // service_point도 적용해야하는 부분이기 때문에 등호가 필요함 !
    if (service_point <= n){
        int check = n - service_point + 1;
        answer += (check / (2*w + 1));
        if (check % (2*w + 1) != 0 )
            answer += 1;
    }
    return answer;
}

/**
 * @file 기지국설치_12979.cpp
 * @brief 프로그래머스 lv.3 기지국 설치
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이분탐색인줄 알고 풀었지만.. 풀면서 굳이라는 생각이 들었다.. 아니나 다를까 그냥 단순히 계산 문제였다..
 * 
 */

#include <iostream>
#include <vector>

using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    int area = 2*w + 1;
    int left = 0, right = n;
    int pos = 1;
    for(auto station : stations) {
        int start = station - w;
        int end = station + w;
        if (start - pos <= 0) {
            pos = end + 1;
            continue;
        }
        answer += ((start - pos) % area == 0) ? (start - pos) / area : (start - pos) / area + 1;
        pos = end + 1;
    }
    // 맨 마지막 스테이션에 대한 계산 필요
    if (pos <= n) {
        int len = ((n - pos + 1) % area == 0) ? (n - pos + 1) / area : (n - pos + 1) / area + 1;
        answer += len;
    }
    return answer;
}

/*
이분탐색 코드

#include <iostream>
#include <vector>

using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 987654321;
    int area = 2*w + 1;
    int left = 0, right = n;
    while(left <= right) {
        int mid = (left + right) / 2;
        int pos = 1;
        int cnt = 0;
        for(auto station : stations) {
            int start = station - w;
            int end = station + w;
            if (start - pos <= 0) {
                pos = end + 1;
                continue;
            }
            cnt += ((start - pos) % area == 0) ? (start - pos) / area : (start - pos) / area + 1;
            pos = end + 1;
        }
        // 맨 마지막 스테이션에 대한 계산 필요
        if (pos <= n) {
            int len = ((n - pos + 1) % area == 0) ? (n - pos + 1) / area : (n - pos + 1) / area + 1;
            cnt += len;
        }
        if (cnt < mid) {
            answer = min(answer, cnt);
            right = mid - 1;
        } else left = mid + 1;
    }
    return answer;
}
*/



/**
 * @file 기지국설치_12979.cpp
 * @brief 프로그래머스 lv.3 기지국 설치
 * @version 0.1
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> stations, int w){
    int answer = 0;
    int pos = 1, coverage = 2*w + 1;
    for(auto station : stations) {
        int start = station - w;
        int end = station + w;
        if (pos < start) {
            int dist = start - pos;
            if (dist % coverage == 0) answer += dist / coverage;
            else answer += (dist / coverage) + 1;
        }
        pos = end + 1;
    }
    if (pos <= n) {
        int dist = n - pos + 1;
        if (dist % coverage == 0) answer += dist / coverage;
        else answer += (dist / coverage) + 1;
    }
    return answer;
}