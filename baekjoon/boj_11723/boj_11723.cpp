#include <iostream>
#include <vector>

using namespace std;

int main(){
    int trial; cin>>trial;
    vector<bool> exists(21, false);
    vector<bool> all(21, true);
    vector<bool> empty(21, false);
    for(int i=0; i<trial; i++) {
        string order; cin>>order;
        int num;

        if (order == "add") {
            cin>>num;
            exists[num] = true;
        } else if (order == "remove") {
            cin>>num;
            exists[num] = false;
        } else if (order == "check") {
            cin>>num;
            if (exists[num]) cout<<"1\n";
            else cout<<"0\n";
        } else if (order == "toggle") {
            cin>>num;
            if (exists[num]) exists[num] = false;
            else exists[num] = true;
        } else if (order == "all") {
            exists = all;
        } else if (order == "empty") {
            exists = empty;
        }
    }
 }