#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string origin, alpha;
    int number = 0;
    cin>>origin;
    for(int i=0; i<origin.size(); i++) {
        if (origin[i] >= '0' && origin[i] <='9') number += (origin[i] - '0');
        else alpha += origin[i];
    }
    sort(alpha.begin(), alpha.end());
    cout<<alpha<<number;
}