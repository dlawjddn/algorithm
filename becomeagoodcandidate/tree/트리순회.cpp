#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> numbers;
vector<bool> visited;
vector<vector<int> > answer(3);

vector<int> split(string origin) {
    vector<int> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, ' ')) {
        result.push_back(stoi(token));
    }
    return result;
}

vector<int> input() {
    string input;
    getline(cin, input);
    return split(input);
}

void pre_dfs(int num) {
    answer[0].push_back(num);
    visited[num - 1] = true;
    int left = num * 2;
    if (left <= numbers.size() && !visited[left - 1]) {
        pre_dfs(left);
    }
    int right = num * 2 + 1;
    if (right <= numbers.size() && !visited[right - 1]) {
        pre_dfs(right);
    }
}

void mid_dfs(int num) {
    int left = num * 2;
    if (left <= numbers.size() && !visited[left - 1]) {
        mid_dfs(left);
    }
    answer[1].push_back(num);
    visited[num - 1] = true;

    int right = num * 2 + 1;
    if (right <= numbers.size() && !visited[right - 1]) {
        mid_dfs(right);
    }
}

void post_dfs(int num) {
    int left = num * 2;
    if (left <= numbers.size() && !visited[left - 1]) {
        post_dfs(left);
    }

    int right = num * 2 + 1;
    if (right <= numbers.size() && !visited[right - 1]) {
        post_dfs(right);
    }
    answer[2].push_back(num);
    visited[num - 1] = true;
}

int main() {
    numbers = input();
    visited = vector<bool>(numbers.size(), false);
    pre_dfs(1);
    visited = vector<bool>(numbers.size(), false);
    mid_dfs(1);
    visited = vector<bool>(numbers.size(), false);
    post_dfs(1);
    for(int i=0; i<3; i++) {
        for(int j=0; j<answer[i].size(); j++) {
            cout<<answer[i][j]<<" ";
        }
        cout<<"\n";
    }
}