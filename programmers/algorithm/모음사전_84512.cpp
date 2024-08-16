#include <string>
#include <vector>
#include <iostream>

using namespace std;

int answer = 0, cnt = 0;
bool finish = false;
char alphabets[5]={'A', 'E', 'I', 'O', 'U'};

int dfs(int cnt, string src, string dest) {
    if (src == dest) {
        finish = true;
        return cnt;
    }
    if (src.size() >= 5) return cnt;
    for(int i=0; i<5; i++) {
        cnt = dfs(cnt + 1, src + alphabets[i], dest);
        if (finish) return cnt;
    }
    return cnt;
}

int solution(string word) {
    return dfs(0, "", word);
}