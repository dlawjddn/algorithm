#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(){
    int t; cin >> t;
    for(int test_case = 1; test_case<=t; test_case++){
        int n; cin >> n;
        string str;
        vector<string> vecStr;
        for(int i = 0; i<n; i++){
            cin >> str;
            vecStr.push_back(str);
        }
        sort(vecStr.begin(), vecStr.end());
        bool flag = true;
        for(int i = 0; i<vecStr.size()-1; i++){
            
            string cur = vecStr[i];
            string next = vecStr[i+1];
            flag = true;
            if(cur.length() > next.length()) continue;
            if(cur == next.substr(0, cur.length())){
                flag = false;
                break;
            }
        }
        if(!flag) cout << "NO\n";
        else cout << "YES\n";
    }
 
    return 0;
}