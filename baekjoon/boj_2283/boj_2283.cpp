#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> values(1000002, 0);

int main() {
    int cnt, target; cin >> cnt >> target;
    
    int max_end = 0;
    for (int i = 0; i < cnt; i++) {
        int start, end; cin>>start >>end;
        values[start]++;
        values[end]--;
        max_end = max(max_end, end);
    }
    for(int i=1; i<values.size(); i++) {
        values[i] += values[i-1];
    }
    int left = 0, right = 0, sum = 0;
    while(1) {
        if (max_end < right) {
            left = right = 0;
            break;
        }
        if (sum == target) {
            break;
        }
        else if (sum < target) {
            sum += values[right];
            right++;
        } else {
            sum -= values[left];
            left++;
        }
    }
    cout<<left<<" "<<right;
}
