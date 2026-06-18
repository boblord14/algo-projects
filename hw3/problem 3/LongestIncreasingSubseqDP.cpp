//
// Created by false on 6/18/2026.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int get_longest_subsequence(const vector<int>& array) {
    vector<int> S(array.size());
    for (int j = 0; j < array.size(); j++) {
        S[j] = 1;
        for (int k = 0; k < j; k++) {
            if (array[k] < array[j] && S[j] < S[k] + 1) {
                S[j] = S[k]+1;
            }
        }
    }

    int max_val = 0;
    for (int val : S) {
        max_val = max(val, max_val);
    }
    return max_val;
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

    cout << get_longest_subsequence(subsequence) << endl;

    return 0;
}