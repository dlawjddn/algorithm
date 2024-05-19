/**
 * @file 6291.cpp
 * @brief 소프티어: 강의실 배정하기
 * @version 0.1
 * @date 2024-05-14
 * 
 * @copyright Copyright (c) 2024
 * 
 * 그리디를 처음 풀어본 문제
 * 문제 이해가 중요했던 문제 강의들을 모두 강의하는데 1개의 강의실에 최대의 강의를 배정하려고 한다.
 * 이때의 강의실 1개에서 진행될 수 있는 최대의 강의 개수는? 이 이 문제의 요점이다.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    int len = 0;
    vector<pair<int, int> > lectures;
    cin>>len;
    for(int i=0; i<len; i++){
        int start = 0, end = 0;
        cin>>start>>end;
        lectures.push_back(make_pair(end, start));
    }
    sort(lectures.begin(), lectures.end());
    int now_time = 0, answer = 0;
    for(int i=0; i<lectures.size(); i++){
        int end_time = lectures[i].first;
        int start_time = lectures[i].second;
        if (now_time <= start_time){
            now_time = end_time;
            answer += 1;
        }
    }
    cout<<answer;
}