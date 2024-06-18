#include <iostream>
#include <algorithm>
using namespace std;
int change=0;
long long xSize=1, ySize=1, y=1, x=1, dx=0, dy=0;


int main(){
    string origin, result;
    cin>>change>>origin>>dx>>dy;
    for(int i=0; i<change; i++){
        int num = origin[i] - '0';
        xSize *= 2;
        ySize *= 2;
        //cout<<num<<"\n";
        if (num == 1){
            y = y*2 -1;
            x *= 2;
        }else if (num == 2){
            y = y*2 -1;
            x = x*2 -1;
        }else if (num == 3){
            y *= 2;
            x = x*2 -1;
        }else {
            y *= 2;
            x *= 2;
        }
        //cout<<y<<x<<"\n";
    }
    y -= dy;
    x += dx;
    //cout<<y<<x<<"\n";
    if (y>0 && y<=ySize && x>0 && x<=xSize){
        for(int j=0; j<change; j++){
            bool xJudge = x % 2; // 홀수면 참
            bool yJudge = y % 2;
            if (xJudge && yJudge){ //  둘 다 홀수인 경우 2사분면
                result += '2';
                y = (y + 1) / 2;
                x = (x + 1) / 2;
            } else if (xJudge && !yJudge){
                result += '3';
                y /= 2;
                x = (x + 1) / 2;
            } else if (!xJudge && yJudge){
                result += '1';
                y = (y + 1) / 2;
                x /= 2;
            } else {
                result += '4';
                y /= 2;
                x /= 2;
            }
        }
        reverse(result.begin(), result.end());
        cout<<result;
    }else cout<<"-1";
}