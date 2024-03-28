#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
struct Point{
    int y, x, age;
    bool dead;

    Point(int y, int x, int age, bool dead) : y(y), x(x), age(age), dead(dead) {}
};
struct Compare{
    bool operator()(const Point& a, const Point& b) {
        return a.age > b.age;
    }
};

int farm[11][11], add[11][11], moveY[8]={0,1,0,-1,-1,1,1,-1}, moveX[8]={1,0,-1,0,1,1,-1,-1}, len = 0, tree=0, limit=0;
priority_queue<Point, vector<Point>, Compare> pq;
queue<Point> temp_q;
void printFarm(){
    for(int i=1; i<=len; i++){
        for(int j=1; j<=len; j++){
            cout<<farm[i][j]<<" ";
        }
        cout<<"\n";
    }
}
void init(){
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            farm[i][j] = 5;
        }
    }
}
void spring(){
    int period = pq.size();
    for(int i=0; i<period; i++){
        Point tree = pq.top(); pq.pop();
        if (farm[tree.y][tree.x] >= tree.age){
            farm[tree.y][tree.x] -= tree.age;
            tree.age += 1;
        } else tree.dead = true;
        temp_q.push(tree);
    }
}
void summer(){
    int period = temp_q.size();
    for(int i=0; i<period; i++){
        Point tree = temp_q.front(); temp_q.pop();
        if (tree.dead) {
            farm[tree.y][tree.x] += (tree.age / 2);
            continue;
        }
        temp_q.push(tree);
    }
}
void fall(){
    int period = temp_q.size();
    for(int i=0; i<period; i++){
        Point tree = temp_q.front(); temp_q.pop();
        if (tree.age % 5 == 0){
            for(int d=0; d<8; d++){
                if (tree.y+moveY[d] > 0 && tree.y+moveY[d] <= len && tree.x+moveX[d] > 0 && tree.x+moveX[d] <= len)
                    temp_q.push(Point(tree.y+moveY[d], tree.x+moveX[d], 1, false));
            }
        }
        temp_q.push(tree);
    }
}
void winter(){
    for(int i=1; i<=len; i++){
        for(int j=1; j<=len; j++){
            farm[i][j] += add[i][j];
        }
    }
    int period = temp_q.size();
    for(int i=0; i<period; i++){
        pq.push(temp_q.front());
        temp_q.pop();
    }
}
int main(){
    init();
    cin>>len>>tree>>limit;
    for(int i=1; i<=len; i++){
        for(int j=1; j<=len; j++){
            cin>>add[i][j];
        }
    }
    for(int i=0; i<tree; i++){
        int y, x, age;
        cin>>y>>x>>age;
        pq.push(Point(y,x,age, false));
    }
    for(int i=0; i<limit; i++){
        spring();
        summer();
        fall();
        winter();
        // printFarm();
        // cout<<"\n";
    }
    cout<<pq.size();
}