/**
 * @file boj_23971.cpp
 * @brief 백준 bronze3 ZOAC 4
 * @version 0.1
 * @date 2024-06-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

int sizeY = 0, sizeX = 0, diff_y = 0, diff_x = 0;

int main(){
    cin>>sizeY>>sizeX>>diff_y>>diff_x;
    diff_y += 1;
    diff_x += 1;
    int y = sizeY / diff_y;
    if (sizeY % diff_y != 0) y += 1;
    int x = sizeX / diff_x;
    if (sizeX % diff_x != 0) x += 1;

    cout<<y*x;
}