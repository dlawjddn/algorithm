#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int user_cnt;
unordered_map<string, int> username_cnt;
unordered_map<string, bool> nicknames;

int main() {
    cin>>user_cnt;
    for(int i=0; i<user_cnt; i++) {
        string username; cin>>username;
        username_cnt[username]++;

        string temp_nickname = "";
        string nickname = "";
        bool stop = false;
        for(int j=0; j<username.size(); j++) {
            temp_nickname += username[j];
            if (!stop && !nicknames[temp_nickname]) {
                nickname = temp_nickname;
                stop = true;
            }
            nicknames[temp_nickname] = true;
        }
        if (nickname == "") {
            // 별칭으로 지정할 수 없음, 사람 수 지정한 후 별칭 만들어야함
            nickname = (username + ((username_cnt[username] == 1) ? "" : to_string(username_cnt[username])));
        }
        nicknames[nickname] = true;
        cout<<nickname<<"\n";
    }
}