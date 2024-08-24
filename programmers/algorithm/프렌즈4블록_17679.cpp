#include <string>
#include <vector>
#include <iostream>

using namespace std;

int moveY[3] = {0,1,1}, moveX[3]={1,0,1}, answer = 0;
vector<string> real_board;

void print_board(){
    for(int y=0; y<real_board.size(); y++){
        for(int x=0; x<real_board[y].size(); x++){
            cout<<real_board[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x, vector<string> board){
    return y < 0 || y >= board.size() || x < 0 || x >= board[y].size();
}

void get_down(vector<string> board){
    for(int x=0; x<board[0].size(); x++){
        int cnt = 0;
        for(int y=board.size()-1; y>=0; y--){
            if (board[y][x] == '0')
                cnt++;
            else{
                if (cnt != 0){
                    board[y+cnt][x] = board[y][x];
                    board[y][x] = '0';
                }
            }
        }
    }
    real_board = board;
}

bool bomb(vector<string> board){
    vector<vector<bool> > visited(30, vector<bool>(30, false));
    bool bombed = false;
    for(int y=0; y<board.size(); y++){
        for(int x=0; x<board[y].size(); x++){
            if (board[y][x] == '0') continue;
            bool stop = false;
            for(int d=0; d<3; d++){
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (check_outside(ny, nx, board) || board[y][x] != board[ny][nx]) {
                    stop = true;
                    break;
                }
            }
            if (!stop){
                bombed = true;
                visited[y][x] = true;
                for(int d=0; d<3; d++){
                    visited[y + moveY[d]][x + moveX[d]] = true;
                }
            }
        }
    }
    real_board = board;
    if (bombed){
        for(int y=0; y<board.size(); y++){
            for(int x=0; x<board[y].size(); x++){
                if (visited[y][x]){
                    board[y][x] = '0';
                    answer++;
                }
            }
        }
        get_down(board);
    }
    return bombed;
}


int solution(int m, int n, vector<string> board) {
    real_board = board;
    while(1){
        if (!bomb(real_board))
            break;
        //print_board();
    }
    return answer;
}