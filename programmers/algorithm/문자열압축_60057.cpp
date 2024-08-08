/**
 * @file 문자열압축_60057.cpp
 * @brief 프로그래머스 lv.2 문자열 압축
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * substr.. 그냥 쓰자.. 단일 문자열에 대해서는 상수 시간이 걸린다고 한다..
 */
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(string s) {
    int answer = s.size();
    for(int i=1; i<=s.size() / 2; i++) { // 비교 사이즈 지정
        string result = "";
        string str1 = s.substr(0, i); // 비교 대상이 되는 문자열
        int cnt = 1;
        for(int j=i; j<s.size(); j+=i) {
            string str2 = s.substr(j, i);
            if (str1 == str2) cnt++;
            else {
                if (cnt > 1)
                    result += to_string(cnt);
                result += str1;
                str1 = str2;
                cnt = 1;
            }
        }
        if (cnt > 1)
            result += to_string(cnt);
            result += str1;
        //cout<<result<<"\n";
        answer = min(answer, (int)result.size());
    }
    return answer;
}