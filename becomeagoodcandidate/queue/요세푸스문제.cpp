#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int number, target;
vector<int> answer;
queue<int> q;

int main() {
    cin>>number>>target;
    for(int i=1; i<=number; i++) q.push(i);

    int cnt = 0;
    while(!q.empty()) {
        int num = q.front(); q.pop();
        cnt++;
        if (cnt == target) {
            answer.push_back(num);
            cnt = 0;
            continue;
        }
        q.push(num);
    }
    cout<<'<';
    for(int i=0; i<answer.size(); i++) {
        if (i == answer.size() - 1) cout<<answer[i];
        else cout<<answer[i]<<", ";
    }
    cout<<">";
}