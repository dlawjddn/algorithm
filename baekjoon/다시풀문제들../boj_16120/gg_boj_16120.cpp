#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

string origin;

string change_ppap_to_p(){
    string changed = "";
    for(int i=0; i<origin.size(); i++) {
        if (origin[i] == 'P' && origin[i+1] == 'P' && origin[i+2] == 'A' && origin[i+3] == 'P') {
            changed += 'P';
            i+=3;
            continue;
        }
        changed += origin[i];
    }
    return changed;
}

void solution() {
    stack<char> s;
    for(int i=0; i<origin.size(); i++) {
        if (origin[i] == 'P') s.push(origin[i]);
        else {
            if (s.empty())  {// A 앞에 P가 존재하지 않는 경우
                cout<<"NP";
                return ;
            } else {
                if (s.size() < 2) { // A 앞에 P가 2개 미만인 경우
                    cout<<"NP";
                    return ;
                }
                s.pop(); s.pop();
            }
            if (origin[i+1] != 'P') { // A 뒤의 문자가 P가 아닌 경우
                cout<<"NP";
                return ;
            }
            else i++;
        }
    }
    cout<<"PPAP";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>origin;
    origin = change_ppap_to_p();
    solution();
}