#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    int back = 0, front = 0, dist = 0, move1 = 0, move2 = 0, time1 = 0, time2 = 0;
    cin>>back>>front>>dist;
    bool stop = false;
    while(1){
        time1 += 1;
        int div = time1 % (back + front);
        if (!(div >= 1 && div <= back))
            stop = true;
        else 
            stop = false;
        if (!stop){
            move1 += 1;
            if (move1 == dist) break;
        }
    }
    //cout<<time1<<" "<<move1<<"\n";
    stop = false;
    while(1){
        time2 += 1;
        int div = time2 % (back + front);
        if (div >= 1 && div <= front)
            stop = false;
        else 
            stop = true;
        if (!stop){
            move2 += 1;
            if (move2 == dist) break;
        }
    }
    cout<<time1+time2;
   return 0;
}