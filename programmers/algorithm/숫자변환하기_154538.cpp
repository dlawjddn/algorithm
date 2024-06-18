#include <string>
#include <vector>
#include <queue>

using namespace std;

int bfs(int x, int y, int n) {
    int plus[3] = {n, 0, 0}, multi[3]={1,2,3};
    queue<pair<int, int> > q;
    vector<bool> visited(1000001, 0);
    q.push(make_pair(x, 0));
    visited[x] = true;
    while(!q.empty()){
        int num = q.front().first;
        int cal = q.front().second; q.pop();
        if (num == y)
            return cal;
        for(int d=0; d<3; d++){
            int nnum = num * multi[d] + plus[d];
            if (nnum > y || visited[nnum]) continue;
            q.push(make_pair(nnum, cal+1));
            visited[nnum] = true;
        }
    }
    return -1;
}
int solution(int x, int y, int n) {
    return bfs(x, y, n);
}