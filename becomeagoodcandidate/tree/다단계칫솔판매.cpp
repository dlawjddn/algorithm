#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<string> parents;
unordered_map<string, int> earn;
unordered_map<string, int> idx_converter;

void div_money(string name, int money) {
    if (name == "-" || money == 0) return ;
    int my_money = money - (money / 10);
    int your_money = money - my_money;
    earn[name] += my_money;
    div_money(parents[idx_converter[name]], your_money);
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer(enroll.size(), 0);
    
    for(int i=0; i<enroll.size(); i++) idx_converter[enroll[i]] = i;
    parents = referral;
    
    for(int i=0; i<seller.size(); i++) div_money(seller[i], amount[i] * 100);
    
    for(auto p : earn) answer[idx_converter[p.first]] = p.second;
    return answer;
}