#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int order_cnt;
long long answer = 0;
vector<int> results(60 * 60 * 24 + 1, 0);

vector<int> convert_time(string time) {
    vector<int> result;
    string token;
    istringstream token_stream(time);
    while(getline(token_stream, token, ':')) {
        result.push_back(stoi(token));
    }
    return result;
}

int convert_second(vector<int> time) {
    return time[0] * 60 * 60 + time[1] * 60 + time[2];
}

int main() {
    cin>>order_cnt;
    for(int i=0; i<order_cnt; i++) {
        int type; cin>>type;
        if (type == 1) {
            string start, end; cin>>start>>end;
            int start_second = convert_second(convert_time(start));
            int end_second = convert_second(convert_time(end));
            results[start_second] += 1;
            results[end_second] -= 1;

        } else {
            string bound; cin>>bound;
            // 누적합 계산하기
            for(int i=1; i<results.size(); i++) results[i] += results[i-1];
            int bound_second = convert_second(convert_time(bound));
            if (bound_second == 0) {
                cout<<"-1";
                return 0;
            }

            // bound의 범위만큼 투포인터로 최대 합 구하기
            int left = 0, right = 0;
            long long sum = 0;
            while(right < 60 * 60 * 24 - 1) {
                sum += results[right];
                if ((right - left + 1) < bound_second) {
                    right++;
                    continue;
                }
                answer = max(answer, sum);
                sum -= results[left++];
                right++;
            }
        }
    }
    cout<<answer;   
}