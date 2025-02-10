#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        string str; cin>>str;
        sort(str.begin(), str.end());
        do {
            cout<<str<<"\n";
        }while(next_permutation(str.begin(), str.end()));
    }

    return 0;
}