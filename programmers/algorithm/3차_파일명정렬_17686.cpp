/**
 * @file 3차_파일명정렬_17686.cpp
 * @brief 프로그래머스 lv.2 2018 카카오 공채 3차 파일명 정렬
 * @version 0.1
 * @date 2024-08-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// head는 대소문자 구분 안 함
// number 앞에 0 제거

struct Info {
    string origin, head;
    int idx, number;
    
    bool operator<(const Info& other) const {
        if (head == other.head) {
            if (number == other.number) {
                return idx < other.idx;
            }
            return number < other.number;
        }
        return head < other.head;
    }
};
vector<Info> sorted_files;

Info make_info(string origin, string head, int number, int idx) {
    Info info;
    info.origin = origin;
    info.head = head;
    info.number = number;
    info.idx = idx;
    return info;
}

void split_file(int idx, string file) {
    int i = 0; 
    string head = "";
    string str_number ="";
    // head 추출
    while(i<file.size()) {
        if (file[i] >= '0' && file[i] <= '9') break;
        if (file[i] >= 'A' && file[i] <= 'Z') {
            head += (file[i] - 'A' + 'a');
            i++;
            continue;
        }
        head += file[i];
        i++;
    }
    // number 추출
    while(i < file.size()) {
        if (file[i] >= '0' && file[i] <= '9')
            str_number += file[i];
        else break;
        i++;
    }
    int number = stoi(str_number);
    sorted_files.push_back(make_info(file, head, number, idx));
}

vector<string> solution(vector<string> files) {
    vector<string> answer;
    for(int i=0; i<files.size(); i++) {
        split_file(i, files[i]);
    }
    sort(sorted_files.begin(), sorted_files.end());
    for(auto f : sorted_files) {
        answer.push_back(f.origin);
    }
    return answer;
}
