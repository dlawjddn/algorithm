// 왜 안되는지 모르겠는 코드

#include <iostream>
#include <queue>
using namespace std;

int main(){
    string str1, str2;
    while(cin>>str1>>str2){
        queue<char> q;
        for(int i = 0; i<str1.size(); i++){
            q.push(str1[i]);
        }
        for(int i=0; i<str2.size(); i++){
            if (q.front() == str2[i]) q.pop();
        }
        if (q.empty()) cout<<"Yes\n";
        else cout<<"No\n";
        
    }
    
}

// 이거랑 같은 로직 아닌가?

#include <iostream>
#include <string>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string a, b;
	while (cin >> a >> b) {
		int aIdx = 0;
		bool isTrue = false;
		for (int i = 0; i < b.length(); i++) {
			if (a[aIdx] == b[i]) {
				aIdx++;
			}
			if (aIdx == a.length()) {
				isTrue = true;
				break;
			}
		}
		if (isTrue) {
			cout << "Yes\n";
		}
		else {
			cout << "No\n";
		}
	}


	return 0;
}
