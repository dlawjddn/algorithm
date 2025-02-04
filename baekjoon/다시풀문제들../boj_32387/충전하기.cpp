#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int port_cnt, order_cnt;
    set<int> available_ports;
    unordered_map<int, int> use;

    cin>>port_cnt>>order_cnt;
    for(int i=1; i<=port_cnt; i++) available_ports.insert(i);
    for(int i=1; i<=order_cnt; i++) {
        int order, x; cin>>order>>x;
        if (order == 1) {
            // 포트에 꽂는 명령
            auto it = available_ports.lower_bound(x);
            if (it == available_ports.end()) {
                cout<<"-1\n";
                continue;
            }
            int dest_port = *it;
            cout<<dest_port<<"\n";
            use[dest_port] = i;
            available_ports.erase(dest_port);
        }
        else {
            // 포트에 있는 것을 빼는 명령
            if (use.find(x) == use.end()) {
                cout<<"-1\n";
                continue;
            }
            cout<<use[x]<<"\n";
            use.erase(x);
            available_ports.insert(x);

        }
    }
}