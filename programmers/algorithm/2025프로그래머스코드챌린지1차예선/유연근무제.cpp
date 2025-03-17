#include <string>
#include <vector>
#include <iostream>

using namespace std;

int change_time(int time, int add) {
    int hour = time / 100;
    int minute = time % 100;
    minute += add;
    if (minute >= 60) {
        hour += (minute / 60);
        minute = minute % 60;
    }
    return hour * 100 + minute;
}

int next_day(int d) {
    d++;
    return ((d == 8) ? 1 : d);
}

int solution(vector<int> schedules, vector<vector<int>> timelogs, int startday) {
    int answer = 0;
    for(int i=0; i<schedules.size(); i++) {
        schedules[i] = change_time(schedules[i], 10);
    }
    for(int i=0; i<timelogs.size(); i++) {
        int cnt = 0;
        int day = startday;
        for(int j=0; j<timelogs[i].size(); j++) {
            if (day == 6 || day == 7) {
                day = next_day(day);
                continue;
            }
            if (timelogs[i][j] <= schedules[i]) cnt++;
            else cnt = 0;
            day = next_day(day);
        }
        if (cnt == 5) answer++;
        
    }
    return answer;
}