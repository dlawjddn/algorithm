#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Info {
    string name;
    int korean, english, math;
    bool operator<(Info other) const {
        if (korean == other.korean) {
            if (english == other.english) {
                if (math == other.math) return name < other.name;
                return math > other.math;
            }
            return english < other.english;
        }
        return korean > other.korean;
    }
};
vector<Info> students;

int main() {
    int student_cnt; cin>>student_cnt;
    for(int i=0; i<student_cnt; i++) {
        string name;
        int korean, english, math;
        cin>>name>>korean>>english>>math;
        students.push_back({name, korean, english, math});
    }
    sort(students.begin(), students.end());
    for(int i=0; i<student_cnt; i++) cout<<students[i].name<<"\n";
}