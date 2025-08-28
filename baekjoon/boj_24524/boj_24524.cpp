#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<queue<int> > alphas(26);

int main() {
    string origin, target; cin>>origin>>target;
    for(int i=0; i<origin.size(); i++) {
        alphas[origin[i] - 'a'].push(i);
    }
    int answer = 0;
    while(1) {
        bool stop = false;
        int last_idx = -1;
        for(int i=0; i<target.size(); i++) {
            while(!alphas[target[i] - 'a'].empty() && alphas[target[i] - 'a'].front() <= last_idx)
                alphas[target[i] - 'a'].pop();
            
            if (alphas[target[i] - 'a'].empty()) {
                stop = true;
                break;
            }
            last_idx = alphas[target[i] - 'a'].front(); alphas[target[i] - 'a'].pop();
        }
        if (stop) break;
        answer++;
    }
    cout<<answer;
}