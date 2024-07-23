#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long weight;
vector<long long> answer;

int main(){
    cin>>weight;
    long long now = weight;
    for(long long now=sqrt(weight); now<=weight; now++) {
        long long before = 1;
        while(before < now) {
            long long temp = pow(now, 2) - pow(before, 2);
            if (temp == weight) {
                answer.push_back(now);
                break;
            }else if (temp > weight) before++;
            else break;
        }
    }
    if (answer.empty()) {
        cout<<"-1";
    } else {
        sort(answer.begin(), answer.end());
        for(auto a : answer) cout<<a<<"\n";
    }
}