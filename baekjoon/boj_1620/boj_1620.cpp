/**
 * @file boj_1620.cpp
 * @brief 백준 silver4 나는야 포켓몬 마스터 이다솜
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<int, string> num_pokemons;
map<string, int> str_pokemons;
int pokemon_cnt, question_cnt;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>pokemon_cnt>>question_cnt;
    for(int i=1; i<=pokemon_cnt; i++) {
        string name; cin>>name;
        num_pokemons.insert({i, name});
        str_pokemons.insert({name, i});
    }
    for(int i=0; i<question_cnt; i++) {
        string question; cin>>question;
        if (question[0] >= 'A' && question[0] <= 'Z') {
            cout<<str_pokemons[question]<<"\n";
        }else {
            cout<<num_pokemons[stoi(question)]<<"\n";
        }
    }
}