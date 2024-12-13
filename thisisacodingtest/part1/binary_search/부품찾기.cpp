#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int product_cnt, order_cnt;
vector<int> products;

bool binary_search(int target, int left, int right) {
    if (left > right) return false;
    int mid = (left + right) / 2;
    if (products[mid] == target) return true;
    else if (products[mid] < target) return binary_search(target, mid + 1, right);
    else return binary_search(target, left, mid - 1);
}

int main() {
    cin>>product_cnt;
    products.resize(product_cnt, 0);
    for(int i=0; i<product_cnt; i++) {
        cin>>products[i];
    }
    sort(products.begin(), products.end());
    cin>>order_cnt;
    for(int i=0; i<order_cnt; i++) {
        int product; cin>>product;
        cout<<(binary_search(product, 0, product_cnt - 1) ? "yes" : "no")<<' ';
    }

}