#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> people, int limit) {
    int boat = 0, left = 0, right = people.size() - 1;
    sort(people.begin(), people.end());
    while(left <= right){
        if (people[left] + people[right] <= limit){
            left ++;
            right --;
            boat ++;
        } else {
            right--;
            boat++;
        }
    }
    return boat;
}