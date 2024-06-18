#include <iostream>
#include <cmath>
using namespace std;
long long max_hp=0, cur_hp=0, total_room=0, atk=0;
int main(){
    long long check_flag=0, num1=0, num2=0;
    cin>>total_room>>atk;
    for(int i=0; i<total_room; i++){
        cin>>check_flag>>num1>>num2;
        if (check_flag==1){
            long long damage = num1 *(ceil((double)num2/atk)-1);
            if (damage > cur_hp) max_hp+=damage-cur_hp, cur_hp=0;
            else cur_hp-=damage;
        }
        else{
            atk+=num1;
            cur_hp+=num2;
            if (cur_hp>max_hp) cur_hp=max_hp;
        }
    }
    cout<<max_hp+1;
}