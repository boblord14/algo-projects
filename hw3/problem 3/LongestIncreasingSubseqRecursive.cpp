//
// Created by false on 6/18/2026.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int lisEndingAt(vector<int>& array, int j)
{
    if (j == 0) {
        return 1;
    }

    int best = 1;

    for (int i = 0; i < j; i++) {
        if (array[i] < array[j]) {
            best = max(best,lisEndingAt(array, i) + 1);
        }
    }

    return best;
}

int main () {

    int n;
    cin >> n;

    vector<int> subsequence(n);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        subsequence[i] = x;
    }

    int longest = 1;

    for (int j = 0; j < subsequence.size(); j++) {
        longest = max(longest, lisEndingAt(subsequence, j));
    }

    cout << longest << endl;

    return 0;
}