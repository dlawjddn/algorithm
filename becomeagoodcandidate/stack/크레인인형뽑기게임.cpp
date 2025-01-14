#include <string>
#include <vector>
#include <stack>

using namespace std;

stack<int> s;
vector<stack<int> > stacks;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    stacks.resize(board.size());
    for(int x=0; x<board.size(); x++) {
        for(int y=board.size() - 1; y >=0; y--) {
            if (board[y][x] == 0) continue;
            stacks[x].push(board[y][x]);
        }
    }
    for(int i=0; i<moves.size(); i++) {
        int idx = moves[i] - 1;
        if (!s.empty() && !stacks[idx].empty() && stacks[idx].top() == s.top()) {
            stacks[idx].pop();
            s.pop();
            answer += 2;
            continue;
        }
        if (!stacks[idx].empty()) {
            s.push(stacks[idx].top());
            stacks[idx].pop();
        }   
    }
    
    return answer;
}