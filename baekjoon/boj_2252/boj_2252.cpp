/**
 * @file boj_2252.cpp
 * @brief 백준 gold3 줄 세우기
 * @version 0.1
 * @date 2024-07-05
 * 
 * @copyright Copyright (c) 2024
 * 
 * 위상정렬을 처음으로 공부하게 된 문제
 * 
 * 위상 정렬이란? 
 * - 노드의 개수와 간선에 대한 정보들이 주어질 때, 어떤 조건들에 대해서 노드 방문해야하는 순서가 정해질 때, 이 순서를 파악하는 알고리즘
 * 
 * 문제를 보고 위상 정렬 문제인지 파악하는 방법
 * - 위상정렬은 위 설명처럼 노드들을 모두 탐색하는데 일정 순서에 따라 방문해야 한다. 따라서 간선 간 이동의 비용 또는 시간과 같은 최소 비용, 최대 비용이 아니라
 * 단순한 이동이지만, X노드를 탐색하기 전에 Y노드를 선수해야 한다. 이정도의 조건이 있다면 위상정렬이다. 또한 위상정렬의 특징을 만족해야 한다.
 * 
 * 위상 정렬의 특징!
 * - 위상정렬은 노드들의 순서를 정하는 알고리즘이다. 따라서 노드들은 자신에게 들어오는 간선의 개수를 가지고 선수 여부를 파악하며 자신에게 들어오는 간선의 개수를 '진입차수'라고 한다.
 * 순서를 정하는 알고리즘이지만, 만약 사이클이 발생한다면 어떨까? 사이클이 발생한다면 시작점을 찾을 수 없다. 즉, 순서를 정하기 위한 시작점을 찾을 수 없다. 
 * 따라서 위상정렬은 양방향이 아닌 단방향으로 이루어지며, 사이클이 존재하지 않는 그래프에 적용이 가능한 알고리즘이다. (DAG: Directed Acyclic Graph)
 * 
 * 구현!
 * 위상정렬을 하기 위해서 필요한 데이터는
 * 1. 진입차수를 알기 위한 배열
 * 2. 간선들의 연결 정보를 알기 위한 2차원 배열
 * 3. 결과를 저장하기 위한 배열
 * 이 필요하다. 
 * 
 * 진입차수 배열은 말 그대로 노드의 개수만큼 크기를 할당하며 각 노드의 인덱스가 노드를 의미하여 안에 내용은 해당 노드의 진입차수의 수를 저장한다.
 * 간선들의 연결정보를 알기 위한 2차원 배열은 특정 노드로 부터 연결된 노드의 수를 담는다. 
 * 
 * 자세한 구현
 * 1. 이 진입차수가 0이 되는 것은 현재 선택해야 하는 노드라는 것을 의미하며 간선들의 데이터를 받으며 초기 진입차수를 계산한다.
 * 2. 진입차수 배열에서 진입차수가 0인 것을 큐에 삽입한다.
 * 3. 큐의 크기 or 노드의 개수만큼 반복하며 큐의 첫번째 요소를 꺼내어 결과 배열에 삽입하고 깨낸 숫자(노드)의 간선을 제거한다(진입차수의 수를 1씩 빼준다)
 * 4. 2와 3 과정을 반복한다.
 * 5. 결과 배열에 담긴 순서대로 그래프에서 방문해야 하는 순서이다.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int vertex_cnt, edge_cnt;
vector<int> in_degree;
vector<vector<int> > maps;

void topology_sort(){
    vector<int> result;
    queue<int> q;
    // 초기 진입차수가 0인 것을 큐에 넣는다
    for(int i=1; i<in_degree.size(); i++) {
        if (in_degree[i] == 0) q.push(i);
    }
    while(!q.empty()) {
        int node = q.front(); q.pop();
        // 큐에 빠져 나온 순서대로 그래프를 생성해야함
        result.push_back(node);
        for(int i=0; i<maps[node].size(); i++) {
            // 큐에서 나온 노드 기준으로 연결된 간선 끊기
            int connected = maps[node][i];
            in_degree[connected] -= 1;
            // 간선이 끊어진 노드가 0이 된다면 큐에 넣기
            if (in_degree[connected] == 0) q.push(connected);
        }
    }
    for(int i=0; i<result.size(); i++) cout<<result[i]<<" ";

}

int main(){
    cin>>vertex_cnt>>edge_cnt;
    in_degree.resize(vertex_cnt + 1, 0);
    maps.resize(vertex_cnt + 1, vector<int>());
    for(int i=0; i<edge_cnt; i++) {
        int src, dest; cin>>src>>dest;
        maps[src].push_back(dest);
        in_degree[dest]++;
    }
    topology_sort();
}