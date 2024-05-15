/**
 * @file 7705.cpp
 * @brief 소프티어: 빨리 기다리기
 * @version 0.1
 * @date 2024-05-16
 * 
 * @copyright Copyright (c) 2024
 * 
 * 다익스트라의 많은 응용점..
 * 
 * 약간은 다익스트라에서 요구하는 지점들을 알게 된 문제
 * 
 * 다익스트라 문제에서 요구하는 사항들
 * 
 * 중요점: 그 점이 최소점이 맞나?
 * 내가 지금 탐색하는 지점이 최소인 경우가 아닐 수도 있다. 
 * 왜냐하면 이전에 최소인 지점이 연산을 거듭하면서 값이 바뀌는 경우가 생기기 때문이다.
 * 이런 경우에는 now점에 대해서 visited 배열의 값과 동일한지(그래야 최소인 경우이기 때문)를 확인해야 
 * 최소인 지점만 확인하며 시간을 줄일 수 있다. 
 * 
 * 따라서 다익스트라를 하는 경우에는 큐에 우선순위 기준으로 들어간다고 해서 안심하고 도착지점을 만난 경우에 return을 하는 것은..
 * 위에 설명대로 당연히 오류를 접하기 쉽다. 
 * 따라서 다익스트라를 하는 경우에는 탐색 함수를 void로 두고 해당 함수가 종료된 이후에 결과값을 비교하며 답을 찾는 것이 더 효율적이다. 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info{
    int dest, riding, waiting;
};
struct Person{
    int pos, time, skill;
    
    bool operator<(const Person& other) const {
        return time > other.time;
    }
};

int final_dest = 0, bus_cnt = 0, skill_cnt = 0;
vector<vector<Info> > bustime(501);
vector<vector<int> > visited(501, vector<int>(501, 987654321));

void print_visited(){
    for(int y=1; y<=final_dest; y++){
        for(int x=0; x<=skill_cnt; x++){
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

Info make_info(int dest, int riding, int waiting){
    Info info;
    info.dest = dest;
    info.riding = riding;
    info.waiting = waiting;
    return info;
}

Person make_person(int pos, int time, int skill){
    Person person;
    person.pos = pos;
    person.time = time;
    person.skill = skill;
    return person;
}

void go_dest(){
    priority_queue<Person> pq;
    pq.push(make_person(1, 0, 0));
    visited[1][0] = 0;
    while(!pq.empty()){
        Person now = pq.top(); pq.pop();
        //cout<<now.pos<<" "<<now.time<<" "<<now.skill<<"\n";
        if (visited[now.pos][now.skill] != now.time) continue;
        for(int d=0; d<bustime[now.pos].size(); d++){
            Info info = bustime[now.pos][d];
            // 바로 출발이 가능한 경우
            if (now.time % info.waiting == 0){
                if (visited[info.dest][now.skill] > now.time + info.riding){
                    //cout<<"check1\n";
                    pq.push(make_person(info.dest, now.time + info.riding, now.skill));
                    visited[info.dest][now.skill] = now.time + info.riding;
                    continue;
                }
            }
            // 기다려야 하는 경우
            else{
                int wait_time = info.waiting - (now.time % info.waiting);
                if (visited[info.dest][now.skill] > now.time + info.riding + wait_time){
                    //cout<<"check2\n";
                    pq.push(make_person(info.dest, now.time + info.riding + wait_time, now.skill));
                    visited[info.dest][now.skill] = now.time + info.riding + wait_time;
                }
            }
            // 빨리 기다리기를 사용하는 경우
            if (now.skill < skill_cnt && visited[info.dest][now.skill + 1] > now.time + info.riding){
                //cout<<"check3\n";
                pq.push(make_person(info.dest, now.time + info.riding, now.skill+1));
                visited[info.dest][now.skill+1] = now.time + info.riding;
            }
        }
    }
    
}
int main(int argc, char** argv)
{
    cin>>final_dest>>bus_cnt>>skill_cnt;
    for(int i=0; i<bus_cnt; i++){
        int start = 0, end = 0, riding = 0, waiting = 0;
        cin>>start>>end>>riding>>waiting;
        bustime[start].push_back(make_info(end, riding, waiting));
    }
    go_dest();
    //print_visited();
    int answer = 987654321;
    for(int i=0; i<visited[final_dest].size(); i++){
        answer = min(answer, visited[final_dest][i]);
    }
    if (answer == 987654321) cout<<-1;
    else cout<<answer;
}