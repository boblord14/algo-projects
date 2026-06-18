//
// Created by false on 6/18/2026.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int get_longest_subsequence(vector<int> &array, const int index) {
    vector<int> subseqLength(index);
    for (int i = index-2; i >= 0; i--) {
        const int val1 = array[index - 1];
        const int val2 = array[i];
        if (val2 < val1) {
            subseqLength [i] = get_longest_subsequence(array, i + 1) + 1;
        }
    }
    int largestSubseq = 1;
    for (const int length : subseqLength) {
        if (length > largestSubseq) {
            largestSubseq = length;
        }
    }
    return largestSubseq;
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

    const int subSequenceLength = get_longest_subsequence(subsequence, n);

    cout << subSequenceLength << endl;

    return 0;
}