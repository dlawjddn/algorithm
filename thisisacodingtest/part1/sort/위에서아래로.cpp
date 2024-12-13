#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int cnt; cin>>cnt;
    vector<int> numbers(cnt, 0);
    for(int i=0; i<cnt; i++) cin>>numbers[i];
    sort(numbers.rbegin(), numbers.rend());
    for(int i=0; i<cnt; i++) cout<<numbers[i]<<' ';
}