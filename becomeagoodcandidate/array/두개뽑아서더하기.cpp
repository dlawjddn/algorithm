#include <string>
#include <vector>
#include <set>

using namespace std;

set<int> result;

vector<int> solution(vector<int> numbers) {
    for(int i=0; i<numbers.size(); i++) {
        for(int j=i+1; j<numbers.size(); j++) {
            result.insert(numbers[i] + numbers[j]);
        }
    }
    return vector<int>(result.begin(), result.end());
}