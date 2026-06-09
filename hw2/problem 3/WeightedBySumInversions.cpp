//
// Created by false on 6/9/2026.
//

#include <iostream>
using namespace std;

int main () {

    int n;
    cin >> n;

    const auto bVals = new int[n];

    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
        bVals[i] = b;
    }

    cout << n << endl;

    delete[] bVals;


    return 0;
}