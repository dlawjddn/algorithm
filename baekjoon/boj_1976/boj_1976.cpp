#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt, plan_cnt;
vector<vector<bool> > maps;
vector<int> plan;

int main() {
    cin>>node_cnt>>plan_cnt;
    maps.resize(node_cnt, vector<bool>(node_cnt, false));
    for(int i=0; i<node_cnt; i++) {
        for(int j=0; j<node_cnt; j++) {
            int result; cin>>result;
            if (i == j) result = true;
            maps[i][j] = (result == 1) ? true : false;
        }
    }
    for(int i=0; i<node_cnt; i++) { // 중간
        for(int j=0; j<node_cnt; j++) { // 시작
            for(int k=0; k<node_cnt; k++) { //끝
                if (maps[j][i] && maps[i][k]) maps[j][k] = true;
            }
        }
    }
    for(int i=0; i<plan_cnt; i++) {
        int node; cin>>node;
        plan.push_back(node);
    }
    if (plan.size() == 1) {
        cout<<"YES";
    } else {
        bool success = true;
        for(int i=1; i<plan.size(); i++) {
            int before_node = plan[i-1] - 1;
            int now_node = plan[i] - 1;
            if (!maps[before_node][now_node]) {
                success = false;
                break;
            }
        }
        cout<<((success) ? "YES" : "NO");
    }
}