/**
 * @file 6277_answer.cpp
 * @brief 소프티어 역량평가 기출: 사물인식 최소 면적 산출 프로그램
 * @version 0.1
 * @date 2024-05-16
 * 
 * @copyright Copyright (c) 2024
 * 
 * 항상 어려운 문제는 시간을 빡빡하게 준다...
 * 
 * 시간을 줄여야 한다고 생각할 때, 가장 먼저 생각하는 부분은 for문을 삭제하는 것이다.
 * 처음에 시간초과가 발생했을 때 cal_area()의 for문이 문제가 되는 줄 알고 이를 삭제하여 진행했다.
 * 하지만 시간 차이가 별로 나지 않았고.. for문도 필수적인 것만 들어간 것 같은데 어디서 문제가 되는지 파악이 안됐다..
 * 
 * 다른 방식으로 생각을 해줘야한다. 아직 다 점을 세지도 않았는데 넓이가 넓은 녀석들은 애초에 글러먹은 녀석이라는 말이다..
 * 따라서 모든 색의 점을 하나씩 고르지 않은 상태에서도 이미 넓이의 최소값보다 크다면, 더 계산할 필요도 없이 다른 점들을 골라야한다는 점이다.
 * 이렇게 되다보니, dfs를 통과할 때 점을 선택한 점들에 대한 목록을 넘기지 않고 그냥 최대, 최소 좌표만 넘기면 되는 것이다..
 * 훨씬 로직도 깔끔하고 짧아져서 새로운 느낌이었다..
 * 
 * 따라서, 이제 시간 초과가 발생하는 경우에는 
 * 1. 당연히 for문은 봐야하는 것이다. 가장 직관적이고 줄이기 제일 쉽다
 * 2. 애초에 글러먹은 녀석을 제외해야한다... (새롭게 배운 부분)
 *  - 중간과정에서 이미 최소 혹은 최대(문제에서 제시한 조건)과 맞지 않은 경우, 설령 아직 문제 조건을 다 만족하지 않더라도..
 * 
 *  ** 꼭 vector를 넘기는 방식처럼 기록을 넘겨야 하는가? 
 *      -> 당연히 아니다.. 이번 문제가 가장 대표적인 예시인 듯 하다.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int point_cnt = 0, color_cnt = 0, answer = 987654321;
vector<vector<pair<int, int> > > colors(21);

// int cal_area(vector<pair<int, int> > points){
//     int min_y = 2000, max_y = -2000, min_x = 2000, max_x = -2000;
//     int len_y = 0, len_x = 0;
//     for(auto point : points){
//         min_y = min(min_y, point.first);
//         min_x = min(min_x, point.second);
//         max_y = max(max_y, point.first);
//         max_x = max(max_x, point.second);
//     }
//     len_y = max_y - min_y;
//     len_x = max_x - min_x;
    
//     return len_y * len_x;
// }

void choose_points(int step, int max_y, int min_y, int max_x, int min_x){
    // 색마다 하나의 점들을 고른 상태
    if (step == color_cnt + 1){
        int len_y = max_y - min_y;
        int len_x = max_x - min_x;
        answer = min(answer, len_y * len_x);
        return ;
    }
    for(int i=0; i<colors[step].size(); i++){
        //selected.push_back(i);
        //selected.push_back(make_pair(colors[step][i].first, colors[step][i].second));
        int next_maxY = max(max_y, colors[step][i].first);
        int next_minY = min(min_y, colors[step][i].first);
        int next_maxX = max(max_x, colors[step][i].second);
        int next_minX = min(min_x, colors[step][i].second);
        int area = (next_maxY - next_minY) * (next_maxX - next_minX);
        if (area < answer || step == 1)
            choose_points(step+1, next_maxY, next_minY, next_maxX, next_minX);
        //selected.erase(selected.end()-1);
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
    choose_points(1, -2000, 2000, -2000, 2000);
    cout<<answer;
}