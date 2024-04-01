#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
vector<int> numbers;
int map[25][25], visited[25][25], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, size=0, round=0, ans = 0;
void process1(int d, int time){
    int y = size / 2;
    int x = size / 2;
    int temp_cnt = 0;
    for(int i=0; i<time; i++){
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        temp_cnt += map[ny][nx];
        map[ny][nx] = 0;
        y = ny;
        x = nx;
    }
    ans += temp_cnt;
}
void make_list(){
    int y1 = 0;
    int x1 = 0;
    int y2 = 0;
    int x2 = size - 1;
    int y3 = size - 1;
    int x3 = size - 1;
    int y4 = size - 1;
    int x4 = 0;
    for(int i=0; i<size/2; i++){
        // 맨 윗줄 파악
        for(int x = x1; x<x2; x++){
            if (map[y1][x] != 0){
                numbers.push_back(map[y1][x]);
            }
            
        }
        // 맨 오른쪽
        for(int y = y2; y<y3; y++){
            if (map[y][x2] != 0){
                numbers.push_back(map[y][x2]);
            }
            
        }
        // 맨 아랫쪽
        for(int x = x3; x>x4; x--){
            if (map[y3][x] != 0){
                numbers.push_back(map[y3][x]);
            }
            
        }
        for(int y = y4; y>y1; y--){
            if (map[y][x4] != 0){
                numbers.push_back(map[y][x4]);
            }
        }


        y1 += 1;
        x1 += 1;
        y2 += 1;
        x2 -= 1;
        y3 -= 1;
        x3 -= 1;
        y4 -= 1;
        x4 += 1;

    }   
}
void delete_seq(){
    int con = 0, num = numbers[0];
    bool again = false;
    for(int i=0; i<numbers.size(); i++){
        if (numbers[i] == num){
            con++;
        } else {
            if (con >= 4){
                ans += (num * con);
                for(int j = 1; j <= con; j++){
                    numbers.erase(numbers.begin() + i - j);
                }
                // vector.erase 하면서 인덱스 변화 인지..!! 정말 중요한 부분!
                i -= con;
                num = numbers[i];
                con = 1;
                again = true;
            }
            else{
                con = 1;
                num = numbers[i];
            }
        }
        if (i == numbers.size() - 1){
            if (con >= 4){
                ans += (num * con);
                for(int j = 1; j <= con; j++){ 
                    // 인덱스 실수 했던 부분 이거 유념하기
                    numbers.erase(numbers.end() - 1);
                }
                con = 0;
                again = true;
            }
        }
    }
    if (again) delete_seq();
}
void remake(){
    vector<int> new_numbers;
    reverse(numbers.begin(), numbers.end());
    int con = 0, num = numbers[0];
    for(int i=0; i<numbers.size(); i++){
        if (numbers[i] == num){
            con++;
        } else {
            new_numbers.push_back(con);
            new_numbers.push_back(num);
            con = 1;
            num = numbers[i];
        }
        if (numbers.size() - 1 == i){
            new_numbers.push_back(con);
            new_numbers.push_back(num);
        }
    }
    numbers = new_numbers;
}
void make_map(){
    memset(map, 0, sizeof(map));
    int max_size = size * size - 1; 
    if (numbers.size() < max_size){
        int need = (size * size) - numbers.size();
        for(int i=0; i<need-1; i++){
            numbers.push_back(0);
        }
    } else {
        int over = numbers.size() - max_size;
        for(int i=0; i<over; i++){
            numbers.pop_back();
        }
    }
    
    int y1 = 0;
    int x1 = 0;
    int y2 = 0;
    int x2 = size - 1;
    int y3 = size - 1;
    int x3 = size - 1;
    int y4 = size - 1;
    int x4 = 0;
    for(int i=0; i<size/2; i++){
        // 맨 윗줄 파악
        for(int x = x1; x<x2; x++){
            map[y1][x] = numbers[numbers.size() - 1];
            numbers.pop_back();
        }
        // 맨 오른쪽
        for(int y = y2; y<y3; y++){
            map[y][x2] = numbers[numbers.size() - 1];
            numbers.pop_back();
            
        }
        // 맨 아랫쪽
        for(int x = x3; x>x4; x--){
            map[y3][x] = numbers[numbers.size() - 1];
            numbers.pop_back();
            
        }
        for(int y = y4; y>y1; y--){
            map[y][x4] = numbers[numbers.size() - 1];
            numbers.pop_back();
        }
        y1 += 1;
        x1 += 1;
        y2 += 1;
        x2 -= 1;
        y3 -= 1;
        x3 -= 1;
        y4 -= 1;
        x4 += 1;
    }
}
int main() {
    int attack_d=0, attack_t=0;
    cin>>size>>round;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cin>>map[i][j];
        }
    }
    for(int i=0; i<round; i++){
        cin>>attack_d>>attack_t;
        process1(attack_d, attack_t);
        make_list();
        delete_seq();
        remake();
        make_map();
    }
    cout<<ans;
    return 0;
}