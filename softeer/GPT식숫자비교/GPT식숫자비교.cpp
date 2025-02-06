#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

vector<pair<int, int> > answer;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.first) {
        return p1.second < p2.second;
    } return p1.first < p2.first;
}

vector<int> split(string origin) {
    vector<int> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, '.')) {
        result.push_back(stoi(token));
    }
    return result;
}

int main(int argc, char** argv)
{
    int num_cnt; cin>>num_cnt;
    for(int i=0; i<num_cnt; i++) {
        string num; cin>>num;
        vector<int> numbers = split(num);
        if (numbers.size() == 1) {
            // 소수점이 없음
            answer.push_back({numbers[0], -1});
        } else {
            answer.push_back({numbers[0], numbers[1]});
        }
    }
    sort(answer.begin(), answer.end(), compare);
    for(int i=0; i<answer.size(); i++) {
        if (answer[i].second == -1) {
            cout<<answer[i].first<<"\n";
        } else cout<<answer[i].first<<"."<<answer[i].second<<"\n";
    }

   return 0;
}