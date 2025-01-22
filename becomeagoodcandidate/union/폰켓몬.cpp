#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int solution(vector<int> nums){
    set<int> unique_nums(nums.begin(), nums.end());
    return min(unique_nums.size(), nums.size() / 2);
}