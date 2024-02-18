#include <iostream>
using namespace std;
int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
string week[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

int main(){
    int mon=0, day=0, sum=0;
    cin>>mon>>day;
    for(int i = 1; i<=mon; i++){
        if (i == mon){
            sum += day - 1;
        } else {
            sum += days[i];
        }
    }
    cout<<week[sum%7];
}