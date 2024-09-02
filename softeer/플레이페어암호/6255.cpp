#include <iostream>
#include <vector>
#include <string>

using namespace std;

string origin = "", encrypt_info = "";
vector<vector<char> > board(5, vector<char>(5));

void print_board(){
    for(int y=0; y<5; y++){
        for(int x=0; x<5; x++){
            cout<<board[y][x]<<" ";
        }
        cout<<"\n";
    }
}

string split_origin(string origin){
    int start = 0;
    string result = "";
    while(start < origin.size()){
        string temp = origin.substr(start, 2);
        if (temp.size() == 0) break;
        else if (temp.size() == 1){
            temp += "X";
            start -= 1;
        }
        else {
            if (temp[0] == temp[1]){
                if (temp[0] == 'X' && temp[1] == 'X'){
                    temp = temp.substr(0, 1);
                    temp += "Q";
                    start -= 1;
                } else {
                    temp = temp.substr(0, 1);
                    temp += "X";
                    start -= 1;
                }
            }
        }
        start += 2;
        result += temp;
    }
    return result;
}

void fill_board(){
    string result = "";
    vector<bool> visited(26, false);
    visited['J' - 'A'] = true;
    for(int i=0; i<encrypt_info.size(); i++){
        int idx = encrypt_info[i] - 'A';
        if (visited[idx]) continue;
        result += encrypt_info.substr(i, 1);
        visited[idx] = true;
    }
    bool flag = false;
    for(int i=0; i<visited.size(); i++){
        if (visited[i]) continue;
        result += i + 'A';
    }
    for(int i=0; i<result.size(); i++){
        board[i/5][i%5] = result[i];
    }
}

pair<int, int> get_position(char alpha){
    for(int y=0; y<5; y++){
        for(int x=0; x<5; x++){
            if (board[y][x] == alpha){
                return make_pair(y, x);
            }
        }
    }
}

void last_encrypt(string after_split){
    string result = "";
    for(int i=0; i<after_split.size(); i+=2){
        string now = after_split.substr(i, 2);
        pair<int, int> f_alpha = get_position(now[0]);
        pair<int, int> s_alpha = get_position(now[1]);
        if (f_alpha.first == s_alpha.first){
            result += board[f_alpha.first][(f_alpha.second + 1) % 5];
            result += board[s_alpha.first][(s_alpha.second + 1) % 5];
            continue;
        }
        else if (f_alpha.second == s_alpha.second){
            result += board[(f_alpha.first + 1) % 5][f_alpha.second];
            result += board[(s_alpha.first + 1) % 5][s_alpha.second];
            continue;
        }
        else {
            result += board[f_alpha.first][s_alpha.second];
            result += board[s_alpha.first][f_alpha.second];
        }
    }
    cout<<result;
}
int main(int argc, char** argv)
{
    cin>>origin>>encrypt_info;
    string after_split = split_origin(origin);
    fill_board();
    last_encrypt(after_split);
}

/**
 * @file 6255.cpp
 * @brief [HSAT 3회 정기 코딩 인증평가 기출] 플레이페어 암호
 * @version 0.1
 * @date 2024-09-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char, pair<int, int> > position;
vector<bool> alphabets(26, false);
vector<vector<char> > board(5, vector<char>(5));

void print_board() {
    for(int y=0; y<5; y++) {
        for(int x=0; x<5; x++) {
            cout<<board[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void make_board(string origin, string encryption) {
    int idx = 0;
    alphabets['J' - 'A'] = true;
    for(int i=0; i<encryption.size(); i++) {
        if (alphabets[encryption[i] - 'A']) continue;
        alphabets[encryption[i] - 'A'] = true;
        board[idx / 5][idx % 5] = encryption[i];
        idx++;
    }
    for(int i=0; i<alphabets.size(); i++) {
        if (alphabets[i]) continue;
        board[idx / 5][idx % 5] = i + 'A';
        idx++;
    }
    for(int y=0; y<5; y++) {
        for(int x=0; x<5; x++) {
            position[board[y][x]] = {y, x};
        }
    }
}

vector<string> split(string origin) {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    vector<string> result;
    for(int i=0; i<origin.size(); i++) {
        string splited = "";
        char before = origin[i];
        if (i + 1 < origin.size()) {
            char after = origin[i+1];
            // 두 글자가 같다면
            if (before == after) {
                if (before == 'X') {
                    after = 'Q';
                }
                else after = 'X';
                i--;
            }
            splited += before;
            splited += after;
        }
        else {
            splited += before;
            splited += 'X';
            i--;
        }
        result.push_back(splited);
        i++;
    }
    return result;
}

int main(int argc, char** argv){
    string origin; cin>>origin;
    string encryption; cin>>encryption;
    make_board(origin, encryption);
    for(auto s : split(origin)) {
        //cout<<s<<"\n";
        char before = s[0];
        char after = s[1];
        // 같은 행에 존재한다면
        if (position[before].first == position[after].first) {
            before = board[position[before].first][(position[before].second + 1) % 5];
            after = board[position[after].first][(position[after].second + 1) % 5];
        }
        // 같은 열에 존재한다면
        else if (position[before].second == position[after].second) {
            before = board[(position[before].first + 1) % 5][position[before].second];
            after = board[(position[after].first + 1) % 5][position[after].second];
        }
        else {
            char new_before = board[position[before].first][position[after].second];
            char new_after = after = board[position[after].first][position[before].second];
            before = new_before;
            after = new_after;
        }
        cout<<before<<after;
    }
}