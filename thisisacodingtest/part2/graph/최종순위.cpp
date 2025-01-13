#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

int node_cnt, change_cnt;
vector<vector<int> > win;
vector<int> in_degree;

void print_win() {
    for(int y=1; y<=node_cnt; y++) {
        for(int x=1; x<=node_cnt; x++) {
            cout<<win[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void print_indegree() {
    for(int i=1; i<in_degree.size(); i++) cout<<in_degree[i]<<" ";
    cout<<"\n";
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        cin>>node_cnt;
        win = vector<vector<int> >(node_cnt + 1, vector<int>(node_cnt + 1, 0));
        in_degree = vector<int>(node_cnt + 1, 0);
        map<int, bool> checker;

        // 작년 등수에 의한 결과 설정하기
        for(int i=0; i<node_cnt; i++) {
            int team; cin>>team;
            in_degree[team] = i;
            for(int j=1; j<=node_cnt; j++) {
                if (team == j) continue;
                if (checker[j]) {
                    win[team][j] = -1;
                    win[j][team] = 1;
                }
            }
            checker[team] = true;
        }

        //print_indegree();

        // 올해 등수에 의한 변화 파악하기
        cin>>change_cnt;
        for(int i=0; i<change_cnt; i++) {
            //int winner, loser; cin>>winner>>loser;
            int team1, team2; cin>>team1>>team2;
            if (win[team1][team2] == 1) {
                // team1이 작년에는 이겼지만, 올해는 짐
                win[team1][team2] = -1;
                win[team2][team1] = 1;
                in_degree[team1] += 1;
                in_degree[team2] -= 1;
            } else {
                // team1이 작년에는 졌지만, 올해는 이김
                win[team1][team2] = 1;
                win[team2][team1] = -1;
                in_degree[team1] -= 1;
                in_degree[team2] += 1;
            }
        }

        //print_indegree();

        // 올해 등수 정리하기
        queue<int> q;
        vector<int> result;
        bool finish = false;
        for(int i=1; i<=node_cnt; i++) {
            if (in_degree[i] == 0) q.push(i);
        }

        for(int i=0; i<node_cnt; i++) {
            if (q.empty()) {
                // 사이클이 발생해서 인디그리가 0이 된 녀석이 없음 -> 사이클이 발생했다
                cout<<"IMPOSSIBLE\n";
                finish = true;
                break;
            }
            if (q.size() > 1) {
                // 데이터 일관성이 보장되지 않아서 동일한 등수인 팀이 여러 팀이 등장 -> 데이터 일관성이 깨짐
                cout<<"?\n";
                finish = true;
                break;
            }

            int team = q.front(); q.pop();
            result.push_back(team);
            for(int x=1; x<=node_cnt; x++) {
                in_degree[x] -= 1;
                if (in_degree[x] == 0) q.push(x);
            }
        }
        if (finish) continue;
        else {
            for(int i=0; i<result.size(); i++) cout<<result[i]<<" ";
            cout<<"\n";
        }
    }
}


// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <map>
// #include <numeric>

// using namespace std;

// int node_cnt, change_cnt;
// vector<vector<int> > board;
// vector<int> result;

// void print_board() {
//     for(int y=1; y<board.size(); y++) {
//         for(int x=1; x<board[y].size(); x++) {
//             cout<<board[y][x]<<" ";
//         }
//         cout<<"\n";
//     }
// }

// int main() {
//     int test_case; cin>>test_case;
//     for(int t=0; t<test_case; t++) {
//         cin>>node_cnt;
//         map<int, bool> checker;
//         board = vector<vector<int> >(node_cnt + 1, vector<int>(node_cnt + 1, 0));
//         for(int i=0; i<node_cnt; i++) {
//             int team; cin>>team;
//             for(int x=1; x<=node_cnt; x++) {
//                 if (team == x) continue;
//                 if (checker[x]) board[team][x] = -1;
//                 else board[team][x] = 1;
//             }
//             checker[team] = true;
//         }
//         bool wrong = false;
//         cin>>change_cnt;
//         for(int i=0; i<change_cnt; i++) {
//             int winner, loser; cin>>winner>>loser;
//             if (board[winner][loser] == -1 && board[loser][winner] == 1) {
//                 // 데이터 일관성 있음
//                 board[winner][loser] = 1;
//                 board[loser][winner] = -1;
//             } else {
//                 wrong = true;
//                 break;
//             }
//         }
//         //print_board();
//         if (wrong) {
//             cout<<"IMPOSSIBLE\n";
//             continue;
//         }
//         else {
//             result = vector<int>(node_cnt, 0);
//             for(int y=1; y<=node_cnt; y++) {
//                 int win_cnt = 0;
//                 for(int x=1; x<=node_cnt; x++) {
//                     if (board[y][x] == 1) win_cnt++;
//                 }
//                 if (result[win_cnt] == 0) {
//                     result[win_cnt] = y;
//                 } else {
//                     wrong = true;
//                     break;
//                 }
//             }
//         }
//         if (wrong) {
//             cout<<"?\n";
//             continue;
//         }
//         else {
//             for(int i=result.size()-1; i>=0; i--) cout<<result[i]<<" ";
//             cout<<"\n";
//         }
//         //print_board();
//     }
// }

