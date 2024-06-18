#include <iostream>
#include <vector>

using namespace std;

const int MAX = 100001;
int parent[MAX];

int Find(int a)
{
	if (a == parent[a])
		return a;
	return parent[a] = Find(parent[a]);
}

void Union(int a, int b)
{
	int pa = Find(a), pb = Find(b);
	parent[pa] = pb;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		parent[i] = i;

	for (int i = 0; i < m; i++)
	{
		int b1, b2;
		cin >> b1 >> b2;
		Union(b1, b2);
	}

	vector<int> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];

	int cnt = 0;
	for (int i = 0; i < n - 1; i++)
		if (Find(v[i]) != Find(v[i + 1]))
			cnt++;

	cout << cnt << '\n';
	return 0;
}