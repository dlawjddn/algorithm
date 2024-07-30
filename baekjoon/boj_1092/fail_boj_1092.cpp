#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int crane_cnt, box_cnt, avg_carry;
vector<int> cranes;
vector<int> boxes;
vector<int> carry;

void print_carry() {
    for(auto cnt : carry) cout<<cnt<<" ";
    cout<<"\n";
}

int main(){
    cin>>crane_cnt;
    cranes.resize(crane_cnt);
    carry.resize(crane_cnt, 0);
    for(int i=0; i<crane_cnt; i++) cin>>cranes[i];
    cin>>box_cnt;
    boxes.resize(box_cnt);
    for(int i=0; i<box_cnt; i++) cin>>boxes[i];

    avg_carry = (box_cnt % crane_cnt == 0) ? box_cnt / crane_cnt : box_cnt / crane_cnt + 1;
    //cout<<"avg: "<<avg_carry<<"\n";
    sort(cranes.begin(), cranes.end());
    sort(boxes.begin(), boxes.end());
    if (cranes.back() < boxes.back()) { // 크레인이 들 수 있는 무게보다 박스 무게가 무겁다면
        cout<<"-1"; return 0;
    }
    int idx = box_cnt - 1, selected = 0;
    for(int i=crane_cnt-1; i>=0; i--) { // 크레인 뒤에서부터 선택
        if (idx < 0) break;
        bool stop = false;
        int ability = cranes[i]; // 해당 크레인이 들 수 있는 무게
        int cnt = 0;
        while(cnt < avg_carry && idx >= 0) {
            if (ability < boxes[idx]) {
                stop = true;
                break;
            }
            cnt++;
            idx--;
        }
        if (stop) break;
        carry[i] = cnt;
        selected++;
    }
    int extra = ((idx + 1) % selected == 0) ? (idx + 1) / selected : (idx + 1) / selected + 1;
    cout<<*max_element(carry.begin(), carry.end()) + extra;
}