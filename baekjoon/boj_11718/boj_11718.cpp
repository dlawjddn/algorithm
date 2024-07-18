/**
 * @file boj_11718.cpp
 * @brief 백준 bronze3 그대로 출력하기
 * @version 0.1
 * @date 2024-07-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

int main() {

	string s;

	while(true) {
		getline(cin, s);
		if(s == "") break;

		cout << s << '\n';
	}

	return 0;
}