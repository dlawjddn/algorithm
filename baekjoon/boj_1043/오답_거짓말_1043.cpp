#include <iostream>
#include <vector>
#include <set>

using namespace std;

int people_cnt = 0, party_cnt = 0, know_cnt = 0;
set<int> knows;
vector<vector<bool> > info(51, vector<bool>(51, false));

void print_info(){
    for(int y=1; y<=people_cnt; y++) {
        for(int x=1; x<=party_cnt; x++) {
            cout<<info[y][x]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    cin>>people_cnt>>party_cnt>>know_cnt;
    for(int i=0; i<know_cnt; i++) {
        int person = 0;
        cin>>person;
        knows.insert(person);
    }
    for(int i=1; i<=party_cnt; i++) {
        int participate_cnt;
        cin>>participate_cnt;
        for(int j=0; j<participate_cnt; j++) {
            int person = 0;
            cin>>person;
            info[person][i] = true;
        }
    }
    //print_info();
    for(auto know : knows) {
        for(int party = 1; party <= party_cnt; party++) {
            for(int person = 1; person <= people_cnt; person++) {
                if (info[know][party] && info[person][party]) 
                    knows.insert(person);
            }
        }
    }
    vector<bool> lie(party_cnt, true);
    int cant_lie = 0;
    for(auto know : knows) {
        for(int p=1; p<=party_cnt; p++) {
            if (lie[p-1] && info[know][p]) {
                lie[p-1] = false;
                cant_lie += 1;
            }
        }
    }
    cout<<party_cnt-cant_lie;
}
