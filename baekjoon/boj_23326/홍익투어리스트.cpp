#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int place_cnt, command_cnt;
set<int> places;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>place_cnt>>command_cnt;
    for(int i=0; i<place_cnt; i++) {
        int place; cin>>place;
        if (place == 1) {
            places.insert(i);
            places.insert(i + place_cnt);
        }
    }

    int pos = 0;
    for(int t=0; t<command_cnt; t++) {
        int command; cin>>command;
        if (command != 3) {
            int target; cin>>target;
            if (command == 1) {
                int target_pos = target - 1;
                if (places.find(target_pos) != places.end()) {
                    places.erase(target_pos);
                    places.erase(target_pos + place_cnt);
                } else {
                    places.insert(target_pos);
                    places.insert(target_pos + place_cnt);
                }
            } else {
                pos = (pos + target) % place_cnt;
            }
        } else {
            auto it = places.lower_bound(pos);
            if (it == places.end() || *it - pos >= place_cnt) {
                cout << -1 << "\n";
            } else {
                cout << (*it - pos) << "\n";
            }
        }
    }
}