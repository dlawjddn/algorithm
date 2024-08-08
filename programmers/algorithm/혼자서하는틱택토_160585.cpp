/**
 * @file 혼자서하는틱택토_160585.cpp
 * @brief 프로그래머스 lv.2 혼자서 하는 틱택토
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>

using namespace std;

bool is_winner(vector<string>& board, char symbol) {
    // 가로줄 (행) 체크
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return true;
        }
    }
    // 세로줄 (열) 체크
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
            return true;
        }
    }
    // 대각선 체크
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return true;
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return true;
    }
    return false;
}

int solution(vector<string> board) {
    int o_count = 0, x_count = 0;
    
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[y][x] == 'O') o_count++;
            else if (board[y][x] == 'X') x_count++;
        }
    }
    
    // 기본적인 개수 조건 확인
    if (x_count > o_count || o_count > x_count + 1) return 0;
    
    bool o_wins = is_winner(board, 'O');
    bool x_wins = is_winner(board, 'X');
    
    // O가 승리했을 때, O가 X보다 하나 더 많아야 함
    if (o_wins && o_count != x_count + 1) return 0;
    
    // X가 승리했을 때, O와 X의 개수가 같아야 함
    if (x_wins && o_count != x_count) return 0;
    
    // O와 X가 동시에 승리할 수 없음
    if (o_wins && x_wins) return 0;
    
    // 그 외의 모든 경우는 유효한 상태
    return 1;
}
