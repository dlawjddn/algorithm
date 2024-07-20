#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int answer1 = 0, answer2 = 0;
vector<int> numbers;
vector<bool> visited;

int main(){
    int arr_size; cin>>arr_size;
    numbers.resize(arr_size);
    visited.resize(arr_size, false);
    for(int i=0; i<arr_size; i++) cin>>numbers[i];
    sort(numbers.begin(), numbers.end());
    for(int i=numbers.size()-1; i>=0; i--) {
        if (visited[i]) continue;
        int max_value = numbers[i];
        int choose_idx = -1;
        for(int j=i-1; j>=0; j--) {
            if (visited[j]) continue;
            if (max_value < numbers[i] * numbers[j]) {
                max_value = numbers[i] * numbers[j];
                choose_idx = j;
            }
        }
        if (max_value == numbers[i]) {
            answer1 += max_value;
            visited[i] = true;
        } else {
            answer1 += max_value;
            visited[i] = true;
            visited[choose_idx] = true;
        }
    }
    visited = vector<bool>(arr_size, false);
    for(int i=0; i<numbers.size(); i++) {
        if (visited[i]) continue;
        int max_value = numbers[i];
        int choose_idx = -1;
        for(int j=i+1; j<numbers.size(); j++) {
            if (visited[j]) continue;
            if (max_value < numbers[i] * numbers[j]) {
                max_value = numbers[i] * numbers[j];
                choose_idx = j;
            }
        }
        if (max_value == numbers[i]) {
            answer2 += max_value;
            visited[i] = true;
        } else {
            answer2 += max_value;
            visited[i] = true;
            visited[choose_idx] = true;
        }
    }
    cout<<max(answer1, answer2);
}