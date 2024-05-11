#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){
    int len = 0, cnt = 0;
    cin >> len >> cnt;
    vector<double> scores(len, 0);
    
    for(int i = 0; i < len; i++){
        cin >> scores[i];
    }
    
    int left = 0, right = 0;
    for(int i = 0; i < cnt; i++){
        cin >> left >> right;
        double sum = 0; // sum을 double 형으로 변경
        for(int j = left - 1; j < right; j++){
            sum += scores[j];
        }
        cout.precision(2);
        cout << fixed << sum / (right - left + 1) << "\n"; // 나눗셈 결과를 double 형태로 형변환
    }
}
