#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

int passPoint = 0;
bool tempfail = false, realfail = false;

int firstCondition(int index, string signal){
    bool option1 = false, option2 = false;;
    int zeroCount = 0;
    int oneCount = 0;
    int returnIndex=index;
    for (int i = 0; i < signal.size(); i++){
        if (signal[returnIndex+zeroCount] == '1') break;
        zeroCount++;
    }
    if (zeroCount < 2) return -1;
    else option1 = true;
    returnIndex += zeroCount;
    for (int i = 0; i < signal.size(); i++){
        if (signal[returnIndex + oneCount] == '0') break;
        if (oneCount >= 1 && tempfail) passPoint = returnIndex + oneCount;
        oneCount++;
    }
    if (oneCount < 1) return -1;
    else option2 = true;
    returnIndex += oneCount;
    if (option1 && option2) return returnIndex;
}

int secondCondition(int index, string signal){
    if (signal[index] == '1'){
        if (index+1 >= signal.size()) return -1;
        else return index+1;
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int index=0;
    string signal;
    cin>>signal;
    for(int i = index; i<signal.size();){
        if (realfail) break;
        if (signal[i] == '1'){
            i = firstCondition(i+1, signal);
            if (i == -1) {
                realfail = true;
                break;
            }
        }
        else {
            i = secondCondition(i+1, signal);
            if (i == -1 && !tempfail){
                i = firstCondition(passPoint+1, signal);
                if (i == -1) {
                    realfail = true;
                    break;
                }
                else tempfail = false;
            } 
        }
    }
    if (realfail) cout<<"NOISE";
    else cout<<"SUBMARINE";
}