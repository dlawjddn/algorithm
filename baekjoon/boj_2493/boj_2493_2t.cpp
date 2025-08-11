#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int building_cnt;
vector<int> buildings;
vector<int> answer;
stack<int> s;

int main() {
    cin>>building_cnt;
    answer.resize(building_cnt, 0);
    for(int i=0; i<building_cnt; i++) {
        int height; cin>>height;
        buildings.push_back(height);
    }

    for(int i=0; i<buildings.size(); i++) {
        while(!s.empty() && buildings[s.top()] < buildings[i]) {
            s.pop();
        }
        if (!s.empty()) {
            answer[i] = s.top() + 1;
        }
        s.push(i);
    }

    for(int i=0; i<answer.size(); i++) cout<<answer[i]<<" ";
}