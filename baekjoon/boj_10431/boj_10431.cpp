#include <iostream>
#include <vector>

using namespace std;

void print_students(vector<int> &students) {
    for (auto student : students) {
        cout << student << " ";
    }
    cout << "\n";
}

int main() {
    int total_test; 
    cin >> total_test;
    
    for (int i = 0; i < total_test; i++) {
        int answer = 0;
        int test_case; 
        cin >> test_case;
        
        vector<int> students(20, 0);
        
        for (int j = 0; j < 20; j++) {
            cin >> students[j];
        }
        
        for (int j = 0; j < 20; j++) {
            for (int k = 0; k < j; k++) {
                if (students[j] < students[k]) {
                    int num = students[j];
                    for (int a = j; a > k; a--) {
                        students[a] = students[a - 1];
                    }
                    students[k] = num;
                    answer += (j - k);  
                    //print_students(students);
                }
            }
        }
        
        cout << test_case << " " << answer << "\n";
    }
    
    return 0;
}
