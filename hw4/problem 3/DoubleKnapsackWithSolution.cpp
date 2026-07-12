//
// Created by false on 7/11/2026.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int VALUE = 1;
const int WEIGHT = 0;

vector<vector<int>> knapsack(const int n, const int w1, const int w2, vector<vector<int>> &objects) {
    //i think this is the first time ive ever actually gone to 3 dimensions, i cannot visualize it for the life of me but pretending it's
    //params like [item][cap for bag 1][cap for bag 2] makes complete logical sense to me
    vector<vector<vector<int>>> bagData(n, vector<vector<int>>(w1 + 1, vector<int>(w2 + 1)));


    for (int item = 0; item < n; item++) { //loop over every item
        for (int bag1Capacity = 0; bag1Capacity <= w1; bag1Capacity++) { //loop over each possible capacity in bag 1 and dynamic programming to find the answer(traditional solution)
            for (int bag2Capacity = 0; bag2Capacity <= w2; bag2Capacity++) { // go over each possible capacity in bag 2, inside of bag 1's loop so we test every possible combination of capacities

                if (item == 0) {
                    bagData[item][bag1Capacity][bag2Capacity] = 0;
                    continue;
                }

                // this pretty much goes the same as traditional knapsack now, just with another direction to look
                // skip(look at previous for both bag1 and bag2), bag1(look at prev for bag2, add to bag1's prev), bag2(vice versa of bag1)

                const int bag1Value = objects[item][WEIGHT] <= bag1Capacity ? objects[item][VALUE] + bagData[item - 1][bag1Capacity - objects[item][WEIGHT]][bag2Capacity] : 0;
                const int bag2Value = objects[item][WEIGHT] <= bag2Capacity ? objects[item][VALUE] + bagData[item - 1][bag1Capacity][bag2Capacity - objects[item][WEIGHT]] : 0;

                if (bag1Value >= bag2Value && bag1Value > bagData[item - 1][bag1Capacity][bag2Capacity]) {
                    //bag1 acceptance scenario(equals lumped in here, had to pick somewhere)
                    bagData[item][bag1Capacity][bag2Capacity] =  bag1Value;
                } else if (bag2Value > bag1Value && bag2Value > bagData[item - 1][bag1Capacity][bag2Capacity]) {
                    //bag2 acceptance scenario
                    bagData[item][bag1Capacity][bag2Capacity] = bag2Value;
                } else {
                    //skip case
                    bagData[item][bag1Capacity][bag2Capacity] = bagData[item - 1][bag1Capacity][bag2Capacity];
                }
            }
        }
    }

    //solution found, build real answers by backtracking
    vector<int> bag1Contents(n);
    int bag1Length = 0;
    vector<int> bag2Contents(n);
    int bag2Length = 0;
    int currentItem = n - 1;
    int currentBag1Capacity = w1;
    int currentBag2Capacity = w2;
    int totalBagValue = bagData[currentItem][currentBag1Capacity][currentBag2Capacity];
    while (totalBagValue > 0) {

        if (totalBagValue != bagData[currentItem - 1][currentBag1Capacity][currentBag2Capacity]) {
            //this case means something changed, go find it
            const int newWeight = objects[currentItem][WEIGHT];
            totalBagValue -= objects[currentItem][VALUE];

            if (newWeight <= currentBag1Capacity && bagData[currentItem - 1][currentBag1Capacity - newWeight][currentBag2Capacity] == totalBagValue) {
                //sidenote: debugging segfaults in the autograder is absolutely obnoxious(segfaults normally are obnoxious to debug but consequences of my own actions for choosing cpp i suppose)
                //object went into bag 1
                currentBag1Capacity -= newWeight;
                bag1Contents[bag1Length] = currentItem;
                bag1Length += 1;
            }else {
                //object went into bag 2, no other scenario should be possible so im not checking all that
                currentBag2Capacity -= newWeight;
                bag2Contents[bag2Length] = currentItem;
                bag2Length += 1;
            }

        }
        // else nothing changed, keep moving
        currentItem -= 1;

    }

    vector<vector<int>> finalOutputVector(3);
    finalOutputVector[0] = vector<int>(1);
    finalOutputVector[1] = vector<int>(bag1Length);
    finalOutputVector[2] = vector<int>(bag2Length);

    finalOutputVector[0][0] = bagData[n - 1][w1][w2];
    //ok and now i need to flip those two arrays because i loaded them backwards and i cba to make it do otherwise
    for (int i = 0; i < bag1Length; i++) {
        finalOutputVector[1][i] = bag1Contents[bag1Length - (i + 1)];
    }
    for (int i = 0; i < bag2Length; i++) {
        finalOutputVector[2][i] = bag2Contents[bag2Length - (i + 1)];
    }

    return finalOutputVector;
}

int main () {

    int n;
    int w1;
    int w2;
    cin >> n >> w1 >> w2;

    vector<vector<int>> objects(n + 1, vector<int>(2));

    //pad the objects array with a dummy object at the start because the dp array needs zeroes along the top/left/whatever-the-last-one-is edges
    objects[0][0] = 0;
    objects[0][1] = 0;

    for (int i = 1; i <= n; i++) {
        cin >> objects[i][0] >> objects[i][1];
    }

    auto resultVector = knapsack(n + 1, w1, w2, objects);

    cout << resultVector[0][0] << endl;

    for (const int item : resultVector[1]) {
        cout << item << " ";
    }

    cout << endl;

    for (const int item : resultVector[2]) {
        cout << item << " ";
    }

    return 0;
}