#include <string>

using namespace std;

int solution(int num) {
    int answer = 0;
    int r;

    while(num > 0){    
        r = num % 10;
        num = num / 10;
        if(r > 5 || (r == 5 && num % 10 >= 5)){
            answer += 10 - r;
            num++;
        }else{
            answer += r;
        }
    }

    return answer;
}