#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cnt_three(int end_time) {
    int result = 0;
    int end_second = (end_time + 1) * 60 * 60;
    for(int t = 0; t < end_second; t++) {
        int sec = t % 60;
        int min = (t / 60) % 60;
        int hour = (t / 3600);
        string t_string = to_string(hour) + to_string(min) + to_string(sec);
        //cout<<t_string<<"\n";
        for(int i=0; i<t_string.size(); i++) {
            if (t_string[i] == '3') {
                result += 1;
                break;
            }
        }
    }
    return result;
}

int main() {
    int hour; cin>>hour;
    cout<<cnt_three(hour);
}