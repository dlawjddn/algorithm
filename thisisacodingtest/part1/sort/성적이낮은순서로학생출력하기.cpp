#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int cnt; cin>>cnt;
    vector<pair<int, string> > students;
    for(int i=0; i<cnt; i++) {
        string name; int score; cin>>name>>score;
        students.push_back({score, name});
    }
    sort(students.begin(), students.end());
    for(int i=0; i<cnt; i++) cout<<students[i].second<<" ";
}