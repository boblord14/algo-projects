//
// Created by false on 5/17/2026.
//

#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;

    for (int i = 2; i <= n; i++) {

        int divisorCount = 0;
        for (int j = 1; j <= i; j++) {

            if (i % j == 0) {

                divisorCount++;
                if (divisorCount > 2) {
                    break;
                }
            }
        }

        if (divisorCount <= 2) {
            cout << i << endl;
        }
    }
    return 0;
}
