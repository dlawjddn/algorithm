#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int flower_cnt, answer = 0;
vector<pair<int, int>> flowers;

int change_to_date(int month, int day) {
    return month * 100 + day;
}

struct Compare {
    bool operator()(pair<int, int> flower1, pair<int, int> flower2) {
        if (flower1.first == flower2.first) {
            return flower1.second > flower2.second;
        }
        return flower1.first < flower2.first;
    }
};

int main() {
    cin >> flower_cnt;
    for (int i = 0; i < flower_cnt; i++) {
        int sm, sd, em, ed;
        cin >> sm >> sd >> em >> ed;
        flowers.push_back(make_pair(change_to_date(sm, sd), change_to_date(em, ed)));
    }

    sort(flowers.begin(), flowers.end(), Compare());

    int last_date = 301, idx = 0;
    while (last_date < 1201) {
        int max_date = last_date;
        bool found = false;

        for (int i = idx; i < flower_cnt; i++) {
            if (flowers[i].first <= last_date) {
                if (flowers[i].second > max_date) {
                    max_date = flowers[i].second;
                    found = true;
                    idx = i + 1;
                }
            } else {
                break;
            }
        }

        if (!found) {
            cout << "0";
            return 0;
        }

        answer++;
        last_date = max_date;
    }

    cout << answer;
    return 0;
}
