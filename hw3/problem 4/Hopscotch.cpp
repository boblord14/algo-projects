//
// Created by false on 6/18/2026.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int hopscotch(const vector<int> &numbers, const int len) {
    int sum_3 = 0;
    int sum_2 = 0;
    int sum_skip = 0;
    for (int i = 0; i < len; i++) {
        int sum_current = sum_3 > sum_2 ? sum_3 + numbers[i] : sum_2 + numbers[i];
        if (i == 1) {
            sum_current = 0; // impossible to reach
        }
        sum_3 = sum_2;
        sum_2 = sum_skip;
        sum_skip = sum_current;
    }
    return max(sum_skip, sum_2);
}

int main () {

    int n;
    cin >> n;

    vector<int> squares(n);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        squares[i] = x;
    }

    const int sum = hopscotch(squares, n);

    cout << sum << endl;

    return 0;
}