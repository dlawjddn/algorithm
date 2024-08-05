#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, int> cache;

string lower_case(string name) {
    string new_name = "";
    for(int i=0; i<name.size(); i++) {
        if (name[i] >= 'A' && name[i] <= 'Z') new_name += (name[i] - 'A' + 'a');
        else new_name += name[i];
    }
    return new_name;
}

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;
    if (cacheSize == 0) {
        return cities.size() * 5;
    }
    for(auto city : cities) {
        city = lower_case(city);
        if (cache.find(city) != cache.end()) { // 캐시에 존재하는 경우
            answer += 1;
            cache[city] = answer;
        } else { // 캐시에 존재하지 않는 경우
            answer += 5;
            if (cache.size() < cacheSize) { // 캐시에 여유 공간이 있는 경우
                cache.insert({city, answer});
            } else {
                string oldest_city;
                int oldest_time = 987654321;
                for(auto info : cache) {
                    string city_name = info.first;
                    int insert_time = info.second;
                    if (insert_time < oldest_time) {
                        oldest_time = insert_time;
                        oldest_city = city_name;
                    }
                }
                cache.erase(oldest_city);
                cache.insert({city, answer});
            }
        }
    }
    return answer;
}