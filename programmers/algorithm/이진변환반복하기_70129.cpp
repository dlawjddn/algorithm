/**
 * @file 이진변환반복하기_70129.cpp
 * @brief 프로그래머스 이진 변환 반복하기 lv.2
 * @version 0.1
 * @date 2024-05-29
 * 
 * @copyright Copyright (c) 2024
 * 
 * 있을 거 같은데.. 했지만 역시나 있던 라이브러리..
 * bitset에 대해서 공부했다. 
 * 
 * 1. 이진 변환
 * bitset<나타낼 길이>(숫자변수); 를 하면 내가 파라미터로 넘긴 숫자가 제시된 길이만큼 이진수로 변환된다.
 * 이는 string 객체가 아니기 때문에 .to_string()을 사용해줘야 한다.
 * 
 * 2. 문자열 자르기
 * 가만 생각해보니.. 이렇게 되면 앞에 0이 계속 생기는데 이거 어떻게 처리하지?
 * 역시나.. 또 라이브러리에 존재했다. find_first_not_of(해당 되는 문자)와 substr을 사용하여 문자열을 자를 수 있었다.
 * 
 */
#include <string>
#include <vector>
#include <bitset>

using namespace std;

int cal_len(int num){
    int len = 0;
    while(num > 0){
        num /= 2;
        len++;
    }
    return len;
}

vector<int> solution(string s) {
    int convert_cnt = 0, delete_cnt = 0;
    while(s.size() > 1){
        int temp_delete = 0;
        for(int i=0; i<s.size(); i++){
            if (s[i] == '0')
                temp_delete++;
        }
        int change_num = s.size() - temp_delete;
        int len = cal_len(change_num);
        s = bitset<32>(change_num).to_string();
        s = s.substr(s.find_first_not_of('0'));
        delete_cnt += temp_delete;
        convert_cnt++;
    }
    return {convert_cnt, delete_cnt};
}
/**
 * @file 이진변환반복하기_70129.cpp
 * @brief 프로그래머스 lv.3 월간 코드 챌린지 시즌1 이진 변환 반복하기
 * @version 0.1
 * @date 2024-08-22
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이걸 왜 틀렸지?
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int answer_depth = 0, answer_delete = 0;

string convert_number(int num) {
    string result = "";
    while(num > 0) {
        result += to_string(num % 2);
        num /= 2;
    }
    reverse(result.begin(), result.end());
    return result;
}

void dfs(string s, int depth, int d_cnt) {
    if (s == "1") {
        answer_depth = depth;
        answer_delete = d_cnt;
        return ;
    }
    int zero_cnt = 0;
    for(int i=0; i<s.size(); i++) {
        if (s[i] - '0' == 0) zero_cnt++;
    }
    dfs(convert_number(s.size() - zero_cnt), depth+1, d_cnt + zero_cnt);
}

vector<int> solution(string s) {
    vector<int> answer;
    dfs(s, 0, 0);
    return {answer_depth, answer_delete};
}