#include <iostream>
#include <string>
using namespace std;

int main(){
    string origin;
    string checks[20];
    int check = 0;
    
    cin>>origin>>check;
    for(int i=0; i<check; i++){
        cin>>checks[i];
    }
    for(int i=0; i<26; i++){
        char change[origin.size()];
        for(int j=0; j<origin.size(); j++){
            change[j] = (origin[j] - 'a' + i) % 26 + 'a';
        }
        string result(change);
        for(int k=0; k<check; k++){
            if (result.find(checks[k]) != string::npos){
                cout<<result;
                return ;
            }
        }
    }
}