#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

stack<int> deleted;
vector<int> up_parents;
vector<int> down_parents;

void init(int size) {
    up_parents.resize(size + 1, 0);
    for(int i=0; i<size; i++) up_parents[i] = i;
    down_parents.resize(size + 1, 0);
    for(int i=0; i<size; i++) down_parents[i] = i;
}

int up_find_parent(int node) {
    if (node == up_parents[node]) return node;
    return up_parents[node] = up_find_parent(up_parents[node]);
}

int down_find_parent(int node) {
    if (node == down_parents[node]) return node;
    return down_parents[node] = down_find_parent(down_parents[node]);
}

void up_make_union(int node1, int node2, bool first) {
    int n1p = up_find_parent(node1);
    int n2p = up_find_parent(node2);
    
    if (n1p > n2p) swap(n1p, n2p);
    
    if (first) {
        up_parents[n1p] = n2p;
    } else up_parents[n2p] = n1p;
}

void down_make_union(int node1, int node2, bool last) {
    int n1p = down_find_parent(node1);
    int n2p = down_find_parent(node2);
    
    if (n1p > n2p) swap(n1p, n2p);
    
    if (last) {
        down_parents[n2p] = n1p;
    }else down_parents[n1p] = n2p;
}

// bool is_valid(int node1, int node2, bool up) {
//     if (up) return up_find_parent(node1) != up_find_parent(node2);
//     return down_find_parent(node2) != down_find_parent(node2);
// }

vector<string> split(string origin) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, ' ')) {
        result.push_back(token);
    }
    return result;
}

string solution(int n, int k, vector<string> cmds) {
    string answer = "";
    init(n);
    for(auto c : cmds) {
        vector<string> cmd = split(c);
        if (cmd[0] == "D") {
            int move = stoi(cmd[1]);
            k = down_find_parent(k + move);
        }
        else if (cmd[0] == "U") {
            int move = stoi(cmd[1]) * -1;
            k = up_find_parent(k + move);
        }
        else if (cmd[0] == "C"){
            deleted.push(k);
            if (k == 0) {
                up_make_union(k, k+1, true);
                down_make_union(k, k+1, false);
            }
            else if (k == n - 1) {
                up_make_union(k, k-1, false);
                down_make_union(k, k-1, true);
            }
            else {
                up_make_union(k, k-1, false);
                down_make_union(k, k+1, false);
            }
            k = down_find_parent(k);
        }
        else {
            up_parents[deleted.top()] = deleted.top();
            down_parents[deleted.top()] = deleted.top();
            deleted.pop();
        }
    }
    // for(int i=0; i<n; i++) {
    //     cout<<up_parents[i]<<" ";
    // }
    // cout<<"\n";
    // for(int i=0; i<n; i++) {
    //     cout<<down_parents[i]<<" ";
    // }
    // cout<<"\n";
    for(int i=0; i<n; i++) {
        answer += (up_parents[i] != down_parents[i]) ? "X" : "O";
    }
    return answer;
}