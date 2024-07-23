/**
 * @file boj_1253.cpp
 * @brief 백준 gold4 좋다
 * @version 0.1
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 * 투 포인터 어렵다.. 
 * 한 숫자에 대해서 투 포인터를 사용한다는 점이 생각하지 못한 부분이다..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int arr_size, answer = 0;
    cin >> arr_size;
    
    vector<int> numbers(arr_size);
    for (int i = 0; i < arr_size; i++) {
        cin >> numbers[i];
    }
    
    sort(numbers.begin(), numbers.end());
    
    for (int i = 0; i < arr_size; i++) {
        int number = numbers[i];
        int left = 0, right = arr_size - 1;
        
        while (left < right) {
            if (left == i) {
                left++;
                continue;
            }
            if (right == i) {
                right--;
                continue;
            }
            
            int sum = numbers[left] + numbers[right];
            if (sum == number) {
                answer++;
                break;  // We found a valid pair, move to the next number
            } else if (sum < number) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
