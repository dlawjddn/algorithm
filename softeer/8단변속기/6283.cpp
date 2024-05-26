#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    vector<int> numbers(8);
    vector<int> asc = {1,2,3,4,5,6,7,8};
    vector<int> desc = {8,7,6,5,4,3,2,1};
    for(int i=0; i<8; i++){
        cin>>numbers[i];
    }
    if (numbers == asc){
        cout<<"ascending";
    }
    else if (numbers == desc){
        cout<<"descending";
    }
    else {
        cout<<"mixed";
    }
}