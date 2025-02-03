#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> prime;

void find_prime(int target) {
    vector<bool> isprime(target + 1, true);
    isprime[0] = isprime[1] = false;
    for(int i=2; i*i<=target; i++) {
        if (isprime[i]) {
            for(int j=i*i; j<=target; j += i) {
                isprime[j] = false;
            }
        }
    }

    for(int i=2; i<=target; i++) {
        if (isprime[i]) prime.push_back(i);
    }
}

int main() {
    int target; cin>>target;
    if (target == 1) {
        cout<<0;
        return 0;
    }
    find_prime(target);
    int left = 0, right = 0, sum = 0, answer = 0;
    while (right <= prime.size()) {
        if (sum < target) {
            sum += prime[right];
            right++;
        } else if (sum > target) {
            sum -= prime[left];
            left++;
        } else {  // sum == target
            answer++;
            sum -= prime[left];
            left++;
        }
    }
    cout<<answer;
}