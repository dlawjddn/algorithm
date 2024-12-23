#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int home_cnt;
vector<int> houses;

int main() {
    cin>>home_cnt;
    for(int i=0; i<home_cnt; i++) {
        int pos; cin>>pos;
        houses.push_back(pos);
    }
    sort(houses.begin(), houses.end());
    cout<<houses[(home_cnt-1) / 2];
}