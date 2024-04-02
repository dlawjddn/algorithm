#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Favorite{
    int me, friends[4];
};

Favorite favorite[400];
int map[20][20], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, size = 0;
void printMap(){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
}
void choose_best_place(int idx){
    int final_y = -1, final_x = -1, empty_cnt=-1, friend_cnt=-1;
    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            int temp_empty = 0;
            int temp_friend = 0;
            if (map[y][x] == 0){
                for(int d=0; d<4; d++){
                    int ny = y + moveY[d];
                    int nx = x + moveX[d];
                    if (ny >=0 && ny< size && nx >=0 && nx < size){
                        // 비어있는 경우
                        if (map[ny][nx] == 0){
                            temp_empty++;
                        } 
                        // 값이 있는 경우
                        else {
                            // 친한 친구의 옆인지 확인해야함!
                            for(int c=0; c<4; c++){
                                // 옆 자리에 내가 좋아하는 친구인 경우
                                if (map[ny][nx] == favorite[idx].friends[c]){
                                    temp_friend++;
                                    break;
                                }
                            }
                        }
                    }
                }
            } else {
                temp_empty = -1;
                temp_empty = -1;
            }
            if (temp_friend >= friend_cnt){
                if (temp_friend > friend_cnt){
                    final_y = y;
                    final_x = x;
                    friend_cnt = temp_friend;
                    empty_cnt = temp_empty;
                } else {
                    if (temp_empty > empty_cnt){
                        final_y = y;
                        final_x = x;
                        friend_cnt = temp_friend;
                        empty_cnt = temp_empty;
                    }
                }
            }
        }
    }
    map[final_y][final_x] = favorite[idx].me;
}
int find_idx(int num){
    for(int i=0; i<size*size; i++){
        if (num == favorite[i].me){
            return i;
        }
    }
}
int cal_score(){
    int ans = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            int idx = find_idx(map[i][j]);
            int cnt = 0;
            for(int d=0; d<4; d++){
                int ny = i + moveY[d];
                int nx = j + moveX[d];
                if (ny >=0 && ny <size && nx >=0 && nx < size){
                    for(int c=0; c<4; c++){
                        if(map[ny][nx] == favorite[idx].friends[c]) cnt++;
                    }
                }
            }
            if (cnt == 1) ans += 1;
            else if (cnt == 2) ans += 10;
            else if (cnt == 3) ans += 100;
            else if (cnt == 4) ans += 1000;
        }
    }
    return ans;
}
int main() {
    cin>>size;
    for(int i=0; i<size*size; i++){
        int me, friend1, friend2, friend3, friend4;
        cin>>me>>friend1>>friend2>>friend3>>friend4;
        favorite[i].me = me;
        favorite[i].friends[0] = friend1;
        favorite[i].friends[1] = friend2;
        favorite[i].friends[2] = friend3;
        favorite[i].friends[3] = friend4;
    }
    for(int i=0; i<size*size; i++){
        choose_best_place(i);
        // printMap();
        // cout<<"\n";
    }
    cout<<cal_score();
    
    return 0;
}