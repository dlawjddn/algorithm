#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lecture_cnt;
vector<bool> booked(10001, false);
vector<pair<int, int> > lectures;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.first) return p1.second > p2.second;
    return p1.first > p2.first;
}

int main() {
    cin>>lecture_cnt;
    for(int i=0; i<lecture_cnt; i++) {
        int value, day; cin>>value>>day;
        lectures.push_back({value, day});
    }
    sort(lectures.begin(), lectures.end(), compare);

    int answer = 0;
    for(int i=0; i<lectures.size(); i++) {
        auto[value, day] = lectures[i];
        for (int j = day; j > 0; j--) {
            if (!booked[j]) {
                booked[j] = true;
                answer += value;
                break;
            }
        }
    }
    cout<<answer;
}