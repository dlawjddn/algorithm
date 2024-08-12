/**
 * @file 두원사이에정수쌍_181187.cpp
 * @brief 프로그래머스 lv.2 두 원 사이에 정수 쌍
 * @version 0.1
 * @date 2024-08-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <math.h>

using namespace std;

long long solution(int r1, int r2) {
	long long answer = 0;

	for (int i = 1; i <= r2; i++) {
		int minY = ceil(sqrt((long long)r1 * r1 - (long long)i * i));
		int maxY = floor(sqrt((long long)r2 * r2 - (long long)i * i));

		if (r1 < i)
			minY = 0;

		answer += (maxY - minY + 1);
	}

	return answer * 4;
}