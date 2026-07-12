//
// Created by false on 7/10/2026.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void mod_insertion_sort(vector<vector<int>>& array) {
    for (int i = 1; i < array.size(); i++) {
        vector<int> key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j][0] > key[0]) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int findLeastTravelTimes(vector<vector<int>> &courseTimes, const vector<vector<int>> &travelTimes, const int n) {

    //needs to be sorted because in order to trick the longest increasing subsequence solution into working we need to
    //make it actually "increasing" with start times
    mod_insertion_sort(courseTimes);

    vector<int> subseqList(n);
    int longestSubseq = 0;

    for (int i = 0; i < n; i++) {
        subseqList[i] = 1;

        for (int j = 0; j < i; j++) {
            //we're going from j to i here, j comes before i FOR SURE
            const int jFinTravelTime = travelTimes[courseTimes[j][2]][courseTimes[i][2]] + courseTimes[j][1];

            if (jFinTravelTime <= courseTimes[i][0] && subseqList[i] < subseqList[j] + 1) {
                subseqList[i] = subseqList[j] + 1;

                if (subseqList[i] > longestSubseq) {
                    longestSubseq = subseqList[i];
                }
            }
        }
    }
    return longestSubseq;
}

int main () {

    int n;
    cin >> n;

    vector<vector<int>> courseTimes(n, vector<int>(3));


    for (int i = 0; i < n; i++) {
        cin >> courseTimes[i][0] >> courseTimes[i][1];
        courseTimes[i][2] = i;
    }

    vector<vector<int>> travelTimes(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> travelTimes[i][j];
        }
    }


    cout << findLeastTravelTimes(courseTimes, travelTimes, n) << endl;

    return 0;
}