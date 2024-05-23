#include<iostream>
#include<cmath>
using namespace std;

int process = 0;

int main(int argc, char** argv){
    cin>>process;
    int num = 2;
    for(int i=0; i<process; i++){
        num = 2 * num - 1;
    }
    cout<<num * num;
}