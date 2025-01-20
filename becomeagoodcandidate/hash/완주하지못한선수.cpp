#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, int> map;

string solution(vector<string> participant, vector<string> completion) {
    //string answer = "";
    for(int i=0; i<participant.size(); i++) {
        map[participant[i]]++;
    }
    for(int i=0; i<completion.size(); i++) {
        map[completion[i]]--;
    }
    for(int i=0; i<participant.size(); i++) {
        if (map[participant[i]] > 0 ) return participant[i];
    }
    //return answer;
}