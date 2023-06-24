#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int amp=0, len=0, diagonal=1, y=1, x=1;
string cmd;
long long checkNum(){
    if (diagonal % 2 == 0){
        if (diagonal > amp) return ((diagonal * (diagonal - 1) / 2) + y - pow(diagonal - amp, 2));
        else return ((diagonal * (diagonal - 1) / 2) + y);
    }
    else{
        if (diagonal > amp) return ((diagonal * (diagonal + 1) / 2) - (y-1) - pow(diagonal - amp, 2));
        else return ((diagonal * (diagonal + 1) / 2) - (y-1));
    }
}
int main(){
    long long ans=1;
    cin>>amp>>len>>cmd;
    for(int i=0; i<cmd.size(); i++){
        if (cmd[i] == 'U'){ //  위로 올라가면 대각선 -1,
            diagonal -= 1;
            y -= 1;
        }
        else if (cmd[i] == 'D'){
            diagonal += 1;
            y+=1;
        }
        else if (cmd[i] == 'R'){
            diagonal += 1;
            x += 1;
        }
        else{
            diagonal -= 1;;
            x -= 1;
        }
        ans += checkNum();
    }
    cout<<ans;
}