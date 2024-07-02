#include <iostream>
#include <vector>

using namespace std; 
int n;
unsigned long long res;
bool vis[100000+1];
int main(){
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++) cin >> v[i];
	
	int start=0, end=0;
	for(int start = 0; start < n; start++) {
		while(end < n) {
			if(vis[v[end]]) break;
			vis[v[end]]=1;
			end++; 
		}
        //cout<<end<<" "<<start<<" "<<end-start<<"\n";
		res+=(end-start);
		vis[v[start]]=0;
	}
	cout << res << endl;
	return 0;
}