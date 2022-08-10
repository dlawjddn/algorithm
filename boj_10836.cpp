#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int M, N, cnt[700 * 700 - 1] = { 0, }, num[3];
pair<int, int> dir[3] = { { 0, -1 }, { -1, -1 }, { -1, 0 } };
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> M >> N;
	for (int i = 0; i < N; i++){
		cin >> num[0] >> num[1] >> num[2];

		for (int j = num[0]; j < num[0] + num[1]; j++)
			cnt[j]++;
            
		for (int j = num[0] + num[1]; j < num[0] + num[1] + num[2]; j++)
			cnt[j] += 2;
	}
	for (int i = 0; i < M; i++){
		for (int j = 0; j < M; j++){
			if (j == 0){
				cout << 1 + cnt[(M - 1) - i] << " ";
			}
			else{
				cout << 1 + cnt[(M - 1) + j] << " ";
			}
		}
		cout << "\n";
	}
	cout << "\n";
	return 0;
}