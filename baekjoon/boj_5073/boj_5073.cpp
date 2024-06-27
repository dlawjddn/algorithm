/**
 * @file boj_5073.cpp
 * @brief 백준 bronze3 삼각형과 세 변
 * @version 0.1
 * @date 2024-06-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> 
using namespace std;

vector<int> triangle(3);

int main(){
    int s1 = 0, s2 = 0, s3 = 0;
    while(1) {
        cin>>triangle[0]>>triangle[1]>>triangle[2];
        if (accumulate(triangle.begin(), triangle.end(), 0) == 0) break;
        sort(triangle.begin(), triangle.end());
        if (triangle[0] + triangle[1] <= triangle[2]) {
            cout<<"Invalid\n";
        }
        else {
            if (triangle[0] == triangle[1] && triangle[1] == triangle[2]) {
                cout<<"Equilateral\n";
            }
            else if (triangle[0] == triangle[1] || triangle[1] == triangle[2] || triangle[0] == triangle[2]) {
                cout<<"Isosceles\n";
            }
            else {
                cout<<"Scalene\n";
            }
        }
    }
}