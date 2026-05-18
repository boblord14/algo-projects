//
// Created by false on 5/17/2026.
//

#include <iostream>
using namespace std;

int main () {

    int n;
    cin >> n;

    // specs say i cant use a vector, absolutely crazy work to do me like that lmao
    // give me liberty, give me fire, give me real data structures or i retire
    // anyhow i just decided to not store the actual input at all and just rip the calculation during input

    int smallest = 2147483647; // integer limit, presumably our input values are smaller than this
    int secondSmallest = 2147483647;
    int testVal;

    for (int i = 0; i < n; i++) {
        cin >> testVal;
        if (testVal < smallest) {
            secondSmallest = smallest;
            smallest = testVal;
        } else if (testVal < secondSmallest && testVal != smallest) {
            secondSmallest = testVal;
        }
    }

    cout << smallest << endl;
    cout << secondSmallest << endl;

    return 0;
}