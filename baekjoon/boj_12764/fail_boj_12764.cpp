#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int person_cnt;
vector<pair<int, int>> people;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

int main(){
    cin >> person_cnt;
    people.resize(person_cnt);
    for(int i = 0; i < person_cnt; i++) {
        cin >> people[i].first >> people[i].second;
    }
    sort(people.begin(), people.end());

    vector<int> use(100001, 0);
    int room_number = 0; // To track the total number of rooms used
    
    for(int i = 0; i < people.size(); i++) {
        if (pq.empty() || pq.top().first > people[i].first) {
            // Need a new room
            room_number++;
            pq.push(make_pair(people[i].second, room_number));
            use[room_number] += 1;
        } else {
            // Reuse an existing room
            auto [end_time, room_idx] = pq.top();
            //cout<<"start: "<<room_number<<"\n";
            while(!pq.empty() && pq.top().first <= people[i].first) {
                //cout<<"top: "<<pq.top().first<<"\n";
                pq.pop();
                room_number--;
            }
            room_number++;
            //cout<<"room_number: "<<room_number<<"\n";
            pq.push(make_pair(people[i].second, room_number));
            use[room_number] += 1;
        }
    }
    int room_cnt = 1;
    while(use[room_cnt] != 0) room_cnt++;
    cout<<room_cnt-1<<"\n";
    for(int i=1; i<room_cnt; i++) cout<<use[i]<<" ";
    return 0;
}
