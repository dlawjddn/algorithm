#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int hole;
    while (cin >> hole){
        hole *= 10000000;
        int hole_cnt; cin>>hole_cnt;
        vector<int> blocks(hole_cnt);
        for(int i=0;i<hole_cnt;i++){
            cin>>blocks[i];
        }
        sort(blocks.begin(),blocks.end());

        int left = 0, right = hole_cnt - 1;
        bool find = false;
        while(left < right){
            int sum = blocks[left] + blocks[right];
            if(sum==hole){
                find = true;
                cout << "yes " << blocks[left] << " " << blocks[right] << '\n';
                break;
            }
            else if(sum < hole) left++;
            else right--;
        }
        if(!find) cout << "danger\n";
    }
    return 0;
}