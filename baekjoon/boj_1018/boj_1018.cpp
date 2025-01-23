#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sizeY, sizeX;
vector<string> maps;

int calculate_changes(int startY, int startX, char startColor) {
    int changes = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            char expectedColor = ((y + x) % 2 == 0) ? startColor : (startColor == 'B' ? 'W' : 'B');
            if (maps[startY + y][startX + x] != expectedColor) {
                changes++;
            }
        }
    }
    return changes;
}

int main() {
    cin >> sizeY >> sizeX;
    maps.resize(sizeY);
    for (int y = 0; y < sizeY; y++) {
        cin >> maps[y];
    }

    int min_changes = 64; // 8x8 보드에서 최대 변경은 64
    for (int y = 0; y <= sizeY - 8; y++) {
        for (int x = 0; x <= sizeX - 8; x++) {
            int changesB = calculate_changes(y, x, 'B'); // 시작을 B로
            int changesW = calculate_changes(y, x, 'W'); // 시작을 W로
            min_changes = min(min_changes, min(changesB, changesW));
        }
    }
    cout << min_changes;
}