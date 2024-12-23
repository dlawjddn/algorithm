#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int> > pq;

int main(){
    int answer = 0;
    int arr_size; cin>>arr_size;
    for(int i=0; i<arr_size; i++) {
        int num; cin>>num;
        pq.push(num);
    }
    while(pq.size() > 1) { 
        int num1 = pq.top(); pq.pop();
        int num2 = pq.top(); pq.pop();
        answer += (num1 + num2);
        pq.push(num1 + num2);
    }
    cout<<answer;
}