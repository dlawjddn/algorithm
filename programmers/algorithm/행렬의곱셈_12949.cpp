#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
    vector<vector<int>> answer;
    int y_size = arr1.size();
    int x_size = arr2[0].size();
    answer.resize(y_size, vector<int>(x_size, 0));
    for(int y=0; y<answer.size(); y++) {
        for(int x=0; x<answer[y].size(); x++) {
            for(int i=0; i<arr2.size(); i++) {
                answer[y][x] += (arr1[y][i] * arr2[i][x]);
            }
        }
    }
    return answer;
}