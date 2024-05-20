#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
    int size = 0, reach = 0, answer = 0;
    string line;
    cin>>size>>reach;
    cin>>line;
    for(int i=0; i<line.size(); i++){
        if (line[i] != 'P') continue;
        for(int a = i-reach; a<= i+reach; a++){
            if (a < 0 || a >= size || line[a] == 'P') continue;
            if (line[a] == 'H'){
                line[a] = 'X';
                answer++;
                break;
            }
        }
    }
    cout<<answer;
}