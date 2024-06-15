#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

unordered_map<int, int> map;
unordered_map<int, int> front;

void print_map(){
    for(const auto& pair : map) {
        cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
    }
    cout<<map.size();
}

int solution(vector<int> topping) {
    int answer = 0;
    
    for(int num : topping)
        map[num] += 1;
    
    for(int i = 0; i<topping.size(); i++){
        front[topping[i]] += 1;
        map[topping[i]] -= 1;
        if (map[topping[i]] == 0)
            map.erase(topping[i]);
        if (front.size() == map.size())
            answer++;
    }
    return answer;
}

