#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define INF 1e20

using namespace std;

struct Compare{
    bool operator()(pair<int, int> p1, pair<int, int> p2) {
        if (p1.second == p2.second) {
            return p1.first < p2.second;
        }
        return p1.second > p2.second;
    }
};
int arr_size, answer;
long long cnt = INF;
vector<pair<int, int> > arr;

int main(){
    cin>>arr_size;
    for(int i=0; i<arr_size; i++) {
        int pos, people_cnt; cin>>pos>>people_cnt;
        arr.push_back({pos, people_cnt});
    }
    sort(arr.begin(), arr.end(), Compare());
    for(int i=0; i<arr.size(); i++) {
        int pos = arr[i].first;
        long long temp_cnt = 0;
        for(int j=0; j<arr.size(); j++) {
            if (i == j) continue;
            temp_cnt += (long long)abs(pos - arr[j].first) * (long long)arr[j].second;
        }
        if (cnt > temp_cnt) {
            cnt = temp_cnt;
            answer = pos;
        }
        else break;
    }
    cout<<answer;
}