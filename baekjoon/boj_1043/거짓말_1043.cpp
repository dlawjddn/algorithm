/**
 * @file 거짓말_1043.cpp
 * @brief 백준 gold4 거짓말
 * @version 0.1
 * @date 2024-06-25
 * 
 * @copyright Copyright (c) 2024
 * 
 * 오답 코드를 보면 알겠지만, 진실을 아는 사람을 업데이트 해서 그 사람이 참여하는 파티는 가면 안되는 것으로 했다.. 이게 왜 안되는지는 모르겠지만
 * 질문게시판을 뒤지는 중 부모를 찾는, 즉 유니온-파인드를 사용하지 않으면 알 수 없는 오류가 발생한다고 해서 고치게 되었다.
 * 유니온 파인드 잘 몰랐고 자신 없었는데.. 이 기회에 공부하려고 했다.
 * 
 * 
 * 유니온 파인드?
 * 
 * 유니온 파인드란 쉽게 말해서 연관성을 파악하는 것이다. a와 b가 연관성이 있어? 하는 것을 부모와 자식을 잇는 트리구조로 나타낸 것을 의미한다.
 * 따라서 유니온 파인드는 부모와 자식으로 이를 구성하고 부모의 값을 업데이트 해야 하기 때문에몇가지 구성단계가 존재한다.
 * 
 * 
 * 유니온 파인드의 구성 단계
 * 
 * 1. 초기세팅: 본인의 부모는 일단 본인으로 두고 시작한다.
 * 2. 제시된 배열 및 트리 구조에서 부모를 지정한다. 이때 재귀로써 find_parent()를 통해서 최상단 부모를 가져와 업데이트 한다.
 * 3. 연관관계가 궁금한 두 객체(or 숫자) 사이의 연관성을 조회한다. 이때도 역시 find_parent를 통해서 두 객체 사이의 부모가 동일한지 파악한다.
 * -> 두 객체의 부모가 동일하다는 것은 둘 사이의 연관성이 존재한다는 것이다. 지금 문제의 경우에는 진실을 아는 사람과 한번이라도 같은 파티에 참여했다가 된다
 * 
 * 
 * 유니온 파인드는 언제 사용할까?
 * 어떤 기준에 속해있는지를 판단할 때 사용하면 되는 것 같다. 지금도 진실을 아는 사람과 같은 행사에 속했던 적이 있는가?를 기준으로 진행했기 때문에 
 * 지금 이 문제처럼 어떤 기준에 대해서 판단할 때 연관성이 있는가? 연관되어 있는가? 같이 묶이는가? 정도의 기준으로 판단하면 될 것 같다.
 * 
 */
#include <iostream>
#include <vector>

using namespace std;

int people_cnt = 0, party_cnt = 0, know_cnt;
vector<int> knows;
vector<vector<int> > party_info(51);
vector<int> parents(51);

int find_parent(int num) {
    if (num == parents[num]) return parents[num];
    return parents[num] = find_parent(parents[num]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    parents[child] = parent;
}

bool same_union(int num1, int num2) {
    num1 = find_parent(num1);
    num2 = find_parent(num2);
    if (num1 == num2) return true;
    return false;
}

int main(){
    cin>>people_cnt>>party_cnt>>know_cnt;
    for(int i=0; i<know_cnt; i++) {
        int person; cin>>person;
        knows.push_back(person);
    }
    for(int i=0; i<party_cnt; i++) {
        int participate; cin>>participate;
        for(int j=0; j<participate; j++) {
            int person; cin>>person;
            party_info[i+1].push_back(person);
        }
    }
    // 유니온-파인드 기초 설정
    for(int i=1; i<=people_cnt; i++) parents[i] = i;

    // 각 파티의 첫번째 참여자를 부모로 설정하여 유니온 묶어주기
    for(int p = 1; p<=party_cnt; p++) {
        // 각 파티의 첫번째 참가자 선택
        int person1 = party_info[p][0];
        // 그 이후 사용자 가져오기
        for(int i = 1; i<party_info[p].size(); i++) {
            int person2 = party_info[p][i];
            // 유니온으로 묶기
            make_union(person1, person2);
        }
    }

    // 거짓말을 하지 못하는 파티 찾기
    
    // 파티마다 각 파타의 모든 참여자와 진실을 아는 사람과의 비교를 해야함
    int cant_go = 0;
    for(int p=1; p<=party_cnt; p++) {
        bool stop = false;
        for(int n=0; n<party_info[p].size(); n++) {
            if (stop) break;
            // 각 파티의 모든 참여자
            int participant = party_info[p][n];
            for(int k=0; k<knows.size(); k++) {
                // 진실을 알고 있는 사람
                int knower = knows[k];
                // 같은 부모를 갖는다면 -> 진실을 갖는 사람과 한번이라도 같은 파티에 참석한다 -> 즉, 일반 참가자도 진실을 아는 사람과 동일한 대우 -> 가지 못하는 행사
                if (same_union(participant, knower)) {
                    stop = true;
                    break;
                }
                
            }
        }
        if (stop) cant_go += 1;
    }

    cout<<party_cnt - cant_go;
}