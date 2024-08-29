/**
 * @file 1.cpp
 * @brief PCCP 모의고사 1회 1번
 * @version 0.1
 * @date 2024-08-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int> > alphas(26);

void print_alphas() {
    for(int i=0; i<alphas.size(); i++) {
        for(int j=0; j<alphas[i].size(); j++) {
            cout<<alphas[i][j]<<" ";
        }
        cout<<"\n";
    }
}

string solution(string input_string) {
    string answer = "";
    for(int i=0; i<input_string.size(); i++) {
        int alpha = input_string[i] - 'a';
        alphas[alpha].push_back(i);
    }
    for(int i=0; i<alphas.size(); i++) {
        if (alphas[i].size() < 2) continue;
        char alpha = i + 'a';
        for(int j=1; j<alphas[i].size(); j++) {
            if (alphas[i][j-1] == alphas[i][j] - 1) continue;
            answer += alpha;
            break;
        }
    }
    if (answer.size() == 0) return "N";
    return answer;
}