#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> goal;
vector<int> measure;
int main(int argc, char** argv){
    int origin = 0, real = 0;
    cin>>origin>>real;
    for(int i=0; i<origin; i++){
        int part = 0, limit = 0;
        cin>>part>>limit;
        for(int j=0; j<part; j++){
            goal.push_back(limit);
        }
    }
    for(int i=0; i<real; i++){
        int part = 0, speed = 0;
        cin>>part>>speed;
        for(int j=0; j<part; j++){
            measure.push_back(speed);
        }
    }
    int answer = 0;
    for(int i=0; i<100; i++){
        answer = max(answer, measure[i] - goal[i]);
    }
    cout<<answer;
}