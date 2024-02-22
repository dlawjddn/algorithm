#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Info {
    int w, in, out;
};

queue<Info> q;
// 다리를 지나는 트럭
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0, sum_weight = 0, time = 1, idx=0;
    while(1){
        //cout<<"time: "<<time<<" idx: "<<idx<<"\n";
        if (!q.empty() && time == q.front().out){
            sum_weight -= q.front().w;
            //cout<<"     **out: time: "<<time<<" "<<"sum_weight: "<<sum_weight<<" in: "<<q.front().in<<" out: "<<q.front().out<<"\n";
            q.pop();
        }
        if (q.empty() && idx >= truck_weights.size()) {
            break;
        }
        if (sum_weight + truck_weights[idx] <= weight && idx < truck_weights.size()){ // 트럭이 들어와도 되는 경우
            Info truck;
            truck.w = truck_weights[idx];
            truck.in = time;
            truck.out = time + bridge_length;
            q.push(truck);
            sum_weight += truck_weights[idx++];
            //cout<<"     **in: time: "<<time<<" "<<"sum_weight: "<<sum_weight<<" in: "<<q.front().in<<" out: "<<q.front().out<<"\n";
        }
        
        time++;
    }
    return time;
}
int main() {
    vector<int> truck_weights;
    // truck_weights.push_back(7);
    // truck_weights.push_back(4);
    // truck_weights.push_back(5);
    // truck_weights.push_back(6);
    for(int i=0; i<10; i++) truck_weights.push_back(10);
    //vector<int> truck_weights = {10};
    //vector<int> truck_weights = {10,10,10,10,10,10,10,10,10,10};
    int weight = 100;
    int bridge_length = 100;
    cout<<solution(bridge_length, weight, truck_weights);
    return 0;
}