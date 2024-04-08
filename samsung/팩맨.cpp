#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

vector<vector<vector<int> > > monster(4, vector<vector<int> >(4, vector<int>(8, 0)));
vector<vector<vector<int> > > egg(4, vector<vector<int> >(4, vector<int>(8, 0)));
vector<vector<int> > dead(4, vector<int>(4, 0));
int moveY[8]={-1,-1,0,1,1,1,0,-1}, moveX[8]={0,-1,-1,-1,0,1,1,1};
int cnt = 0, trial=0, pacmanY=0, pacmanX=0;

void print_monster(){
    for(int d=0; d<8; d++){
        cout<<"d: "<<d<<"\n";
        for(int y=0; y<4; y++){
            for(int x=0; x<4; x++){
                cout<<monster[y][x][d]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
}
void print_cnt(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cout<<accumulate(monster[i][j].begin(), monster[i][j].end(), 0)<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
bool check_bound(int y, int x){
    return y >= 0 && y < 4 && x >=0 && x < 4;
}
void copy_monster(){
    vector<vector<vector<int> > > temp(4, vector<vector<int> >(4, vector<int>(8, 0)));
    temp = monster;
    egg = temp;
}
void move_monster(int t){
    vector<vector<vector<int> > > temp(4, vector<vector<int> >(4, vector<int>(8, 0)));
    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            for(int d=0; d<8; d++){
                if (!monster[y][x][d]) continue;
                bool flag = false;
                for(int c=0; c<8; c++){
                    int nd = d + c;
                    if (nd > 7) nd -= 8;
                    int ny = y + moveY[nd];
                    int nx = x + moveX[nd];
                    if (check_bound(ny, nx) && dead[ny][nx] < t+1 && !(ny == pacmanY && nx == pacmanX)){
                        // if (t == 4){
                        //     cout<<"y: "<<ny<<" x: "<<nx<<" d: "<<nd<<"\n";
                        // }
                        flag = true;
                        temp[ny][nx][nd] += monster[y][x][d];
                        monster[y][x][d] = 0;
                        break;
                    }
                }
                if (!flag) {
                    temp[y][x][d] += monster[y][x][d];
                    monster[y][x][d] = 0;
                }
            }
        }
    }
    monster = temp;
}
void move_pacman(int t){
    int firstY=0, firstX=0, secondY=0, secondX=0, thirdY=0, thirdX=0, fcnt=0, scnt=0, tcnt=0, eat=-1;
    // cout<<"start: "<<pacmanY<<" "<<pacmanX<<"\n";
    for(int f=0; f<8; f+=2){
        int fy = pacmanY + moveY[f];
        int fx = pacmanX + moveX[f];
        if (!check_bound(fy, fx)) continue;
        for(int s=0; s<8; s+=2){
            int sy = fy + moveY[s];
            int sx = fx + moveX[s];
            if (!check_bound(sy, sx)) continue;
            for(int t=0; t<8; t+=2){
                int ty = sy + moveY[t];
                int tx = sx + moveX[t];
                if (!check_bound(ty, tx)) continue;
                vector<vector<vector<int> > > temp(4, vector<vector<int> >(4, vector<int>(8, 0)));
                temp = monster;
                int temp_fcnt = accumulate(temp[fy][fx].begin(), temp[fy][fx].end(), 0);
                fill(temp[fy][fx].begin(), temp[fy][fx].end(), 0);

                int temp_scnt = accumulate(temp[sy][sx].begin(), temp[sy][sx].end(), 0);
                fill(temp[sy][sx].begin(), temp[sy][sx].end(), 0);

                int temp_tcnt = accumulate(temp[ty][tx].begin(), temp[ty][tx].end(), 0);
                int temp_eat =  temp_fcnt + temp_scnt + temp_tcnt; 
                if (temp_eat > eat){
                    eat = temp_eat;
                    firstY = fy; firstX = fx; fcnt = temp_fcnt;
                    secondY = sy; secondX = sx; scnt = temp_scnt;
                    thirdY = ty; thirdX = tx; tcnt = temp_tcnt;
                }
            }
        }
    }
    if (fcnt != 0) {
        dead[firstY][firstX] = t+3;
        fill(monster[firstY][firstX].begin(), monster[firstY][firstX].end(), 0);
    }
    if (scnt != 0) {
        dead[secondY][secondX] = t+3;
        fill(monster[secondY][secondX].begin(), monster[secondY][secondX].end(), 0);
    }
    if (tcnt != 0) {
        dead[thirdY][thirdX] = t+3;
        fill(monster[thirdY][thirdX].begin(), monster[thirdY][thirdX].end(), 0);
    }
    pacmanY = thirdY;
    pacmanX = thirdX;
    
    // cout<<"eat: "<<eat<<"\n";
    // cout<<"first: "<<firstY<<" "<<firstX<<"\n";
    // cout<<"second: "<<secondY<<" "<<secondX<<"\n";
    // cout<<"third: "<<thirdY<<" "<<thirdX<<"\n";
    // cout<<"after eat\n";
    // print_cnt();
}
void birth_monster(){
    for(int d=0; d<8; d++){
        for(int y=0; y<4; y++){
            for(int x=0; x<4; x++){
                monster[y][x][d] += egg[y][x][d];
                egg[y][x][d] = 0;
            }
        }
    }
}
void print_dead(){
    cout<<"dead: \n";
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cout<<dead[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
int main(){
    cin>>cnt>>trial;
    cin>>pacmanY>>pacmanX;
    pacmanY-=1;
    pacmanX-=1;
    for(int i=0; i<cnt; i++){
        int tempY=0, tempX=0, tempD=0;
        cin>>tempY>>tempX>>tempD;
        monster[tempY-1][tempX-1][tempD-1]++;
    }
    for(int i=0; i<trial; i++){
        // cout<<"trial: "<<i<<"\n";
        copy_monster();
        // cout<<"before move\n";
        // print_cnt();
        // print_dead();
        move_monster(i);
        // cout<<"after move\n";
        // print_cnt();
        move_pacman(i);
        birth_monster();
        // print_cnt();
    }
    int ans = 0;
    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            ans += accumulate(monster[y][x].begin(), monster[y][x].end(), 0);
        }
    }
    cout<<ans;
}