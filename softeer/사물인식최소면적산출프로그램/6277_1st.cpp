// 시간초과
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int point_cnt = 0, color_cnt = 0, answer = 987654321;
vector<vector<pair<int, int> > > colors(21);

int cal_area(vector<pair<int, int> > points){
    int min_y = 2000, max_y = -2000, min_x = 2000, max_x = -2000;
    int len_y = 0, len_x = 0;
    for(auto point : points){
        min_y = min(min_y, point.first);
        min_x = min(min_x, point.second);
        max_y = max(max_y, point.first);
        max_x = max(max_x, point.second);
    }
    len_y = max_y - min_y;
    len_x = max_x - min_x;
    
    return len_y * len_x;
}

void choose_points(int step, vector<pair<int, int> > selected){
    // 색마다 하나의 점들을 고른 상태
    if (step == color_cnt + 1){
        answer = min(answer, cal_area(selected));
        return ;
    }
    for(int i=0; i<colors[step].size(); i++){
        //selected.push_back(i);
        selected.push_back(make_pair(colors[step][i].first, colors[step][i].second));
        choose_points(step+1, selected);
        selected.erase(selected.end()-1);
    }
}

int main(int argc, char** argv)
{
    cin>>point_cnt>>color_cnt;
    for(int i=0; i<point_cnt; i++){
        int x = 0, y = 0, color = 0;
        cin>>x>>y>>color;
        colors[color].push_back(make_pair(y, x));
    }
    vector<pair<int, int> > selected;
    choose_points(1, selected);
    cout<<answer;
}