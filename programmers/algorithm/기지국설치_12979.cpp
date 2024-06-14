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