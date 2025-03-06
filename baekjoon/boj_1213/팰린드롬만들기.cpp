#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    string str; 
    cin >> str;

    // 1. 빈도수 체크
    vector<int> freq(26, 0);
    for(char c : str) {
        freq[c - 'A']++;
    }

    // 2. 홀수 빈도 문자 개수 파악
    int oddCount = 0; 
    int oddIndex = -1;
    for(int i = 0; i < 26; i++){
        if(freq[i] % 2 == 1){
            oddCount++;
            oddIndex = i;
        }
    }

    // 3. 팰린드롬 구성 가능 여부
    if ((str.size() % 2 == 0 && oddCount != 0) || 
        (str.size() % 2 == 1 && oddCount != 1)){
        // 만들 수 없는 경우
        cout << "I'm Sorry Hansoo\n";
        return 0;
    }

    // 4. 절반(halfStr) 만들기
    string halfStr = "";
    for(int i = 0; i < 26; i++){
        halfStr += string(freq[i] / 2, 'A' + i);
    }

    // 5. 팰린드롬 완성
    //    (홀수 빈도 문자가 있으면 가운데에 1개만 추가)
    string result = halfStr;
    if (oddIndex != -1) {
        result.push_back('A' + oddIndex);
    }
    reverse(halfStr.begin(), halfStr.end());
    result += halfStr;

    cout << result << endl;
    return 0;
}
