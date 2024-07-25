#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int alpha_cnt, height_cnt, change_pos;
bool stop = false;
string destination;
string answer;
vector<string> origin;
vector<vector<int> > maps;

void print_maps() {
    for(int y=0; y<height_cnt; y++) {
        for(int x=0; x<alpha_cnt; x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
}


bool solve(string line) {
    for (int x = 0; x < alpha_cnt; x++) {
        int ypos = 0;
        int xpos = x;
        while (ypos < height_cnt) {
            if (maps[ypos][xpos] == 0) ypos++;
            else if (maps[ypos][xpos] == 1) {
                xpos++;
                ypos++;
            }
            else if (maps[ypos][xpos] == -1) {
                xpos--;
                ypos++;
            }
        }
        if (destination[xpos] != 'A' + x) return false;
    }
    answer = line;
    return true;
}



void dfs(string line) {
    if (stop) return ;
    if (line.size() > alpha_cnt) return ;
    if (line.size() == alpha_cnt) {
        //cout<<line<<"\n";
        vector<int> temp(alpha_cnt, 0);
        for(int i=0; i<line.size(); i++) {
            if (line[i] == '-') {
                temp[i] = 1;
                temp[i+1] = -1;
                i++;
            }else continue;
        }
        maps[change_pos] = temp;
        if (solve(line)) stop = true;
        return ;
    }
    dfs(line + '*');
    dfs(line + "-*");
}


int main(){
    cin>>alpha_cnt>>height_cnt>>destination;
    origin.resize(height_cnt);
    maps.resize(height_cnt, vector<int>(alpha_cnt, 0));
    for(int i=0; i<height_cnt; i++) {
        cin>>origin[i];
        for(int j=0; j<origin[i].size(); j++) {
            if (origin[i][j] == '?') {
                change_pos = i;
                break;
            }
            if (origin[i][j] == '-') {
                maps[i][j] = 1;
                maps[i][j+1] = -1;
                j++;
            }else continue;

        }
    }
    dfs("");
    if (answer.empty()) {
        cout << string(alpha_cnt-1, 'x');
    } else {
        cout << answer;
    }
}