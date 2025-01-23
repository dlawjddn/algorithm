
#include <iostream>
#include <vector>
using namespace std;
string str, ppap = "PPAP";
vector<char> stack;
int cnt;
bool isPPAP()
{
    for (int i = 0; i < 4; ++i)
    {
        if (stack[i + stack.size() - 4] != ppap[i]) // 뒤부터 4자리 확인
        {
            return false;
        }
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> str;
    stack.reserve(str.size());
    for (int i = 0; i < str.size(); ++i)
    {
        stack.push_back(str[i]);

        if (stack.size() >= 4) // 4보다 크다면
        {
            if (isPPAP())
            {
                for (int i = 0; i < 3; ++i) // P만 남기기
                {
                    stack.pop_back();
                }
            }
        }
    }
    cout << (stack.size() == 1 && stack.front() == 'P' ? "PPAP" : "NP"); // P만 남았는지 확인
    return 0;
}