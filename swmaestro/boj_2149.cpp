#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    string key;
    string password;
    cin>>key>>password;
    string sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
    string divide[key.size()];
    int num[key.size()];
    for(int i=0; i<sortedKey.size(); i++){
        divide[i] += sortedKey[i];
        for(int j=0; j<(password.size() / sortedKey.size()); j++){
            divide[i] += password[i * (password.size() / sortedKey.size()) + j];
        }
    }
    for(int i=0; i<key.size(); i++){
        for(int j=0; j<sortedKey.size(); j++){
            if (key[i] == sortedKey[j]){
                num[i] = j;
                key[i] = '1';
                sortedKey[j] = '2';
                break;
            }
        }
    }
    for(int i=1; i<=password.size() / sortedKey.size(); i++){
        for(int j=0; j<key.size(); j++){
            cout<<divide[num[j]][i];
        }
    }

}