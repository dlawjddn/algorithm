#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

vector<int> snows;
int answer = INF;

int main() {
    int cnt; cin>>cnt;
    for(int i=0; i<cnt; i++) {
        int size; cin>>size;
        snows.push_back(size);
    }
    sort(snows.begin(), snows.end());

    for(int i=0; i<snows.size() - 3; i++) {
        for(int j=i+3; j<snows.size(); j++) {
            int left = i + 1, right = j - 1;
            while(left < right) {
                int snowman1 = snows[i] + snows[j];
                int snowman2 = snows[left] + snows[right];
                answer = min(answer, abs(snowman1 - snowman2));

                if (snowman1 > snowman2) left++;
                else right--;
            }
        }
    }
    cout<<answer;
}