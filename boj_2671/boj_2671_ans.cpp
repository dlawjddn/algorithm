#include <iostream>
#include <string>
using namespace std;
bool checkAns(string str){
    int index=0, len = str.length();
    while(index < len){
        if (str[index] == '0'){
            if (index+1 >= len) return false;
            if (str[index+1] != '1') return false;
            index += 2;
        }
        else{
            if (index + 3 >= len) return false;
            if (str[index+1] != '0' || str[index+2] != '0') return false;
            index++;
            while(index < len && str[index] == '0') index++;
            if (index >= len) return false;
            index++;
            while(index < len && str[index] == '1'){
                if (index + 2 < len && str[index+1] == '0' && str[index+2] == '1') break;
                index++;
            }
        }
    }
    return true;
}

int main(){
    string str;
    cin>>str;
    if (checkAns(str)) cout<<"SUBMARINE";
    else cout<<"NOISE";
}