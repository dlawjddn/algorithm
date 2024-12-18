#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string numbers; cin>>numbers;
    int left_number = numbers[0] - '0';
    for(int i=1; i<numbers.size(); i++) {
        int num = numbers[i] - '0';

        int plus = left_number + num;
        int mul = left_number * num;

        left_number = (plus < mul) ? mul : plus;
    }
    cout<<left_number;
}