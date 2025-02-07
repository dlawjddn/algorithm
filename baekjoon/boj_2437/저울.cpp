#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int num_cnt;
    cin >> num_cnt;
    vector<int> numbers(num_cnt);
    
    for (int i = 0; i < num_cnt; i++) {
        cin >> numbers[i];
    }
    sort(numbers.begin(), numbers.end());

    set<int> unique_numbers;
    int answer = 1;
    
    if (answer != numbers.front()) {
        cout << answer;
        return 0;
    } else {
        answer++;
        unique_numbers.insert(numbers.front());
    }

    for (int i = 1; i < numbers.size(); i++) {
        if (answer >= numbers[i]) {
            if (answer == numbers[i]) unique_numbers.insert(answer++);
        } else {
            cout << answer;
            return 0;
        }
        
        vector<int> to_add;  // 새로운 값 저장할 벡터
        for (auto before_value : unique_numbers) {
            int now_value = before_value + numbers[i];
            if (answer >= now_value) {
                if (answer == now_value) to_add.push_back(answer++);
            } else {
                cout << answer;
                return 0;
            }
        }
        
        for (auto value : to_add) unique_numbers.insert(value);  // 한 번에 추가
    }

    cout << answer;  // 최종 정답 출력
    return 0;
}
