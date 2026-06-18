//
// Created by false on 6/18/2026.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main () {

    int n;
    cin >> n;

    vector<int> squares(n);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        squares[i] = x;
    }


    cout << n << endl;

    return 0;
}