//
// Created by false on 6/9/2026.
//

#include <iostream>
using namespace std;

struct pointValue {
    int yCoord;
    int delta;
};

pointValue* leftHalf(const pointValue* array, const int size) {

    const auto halfPointObjs = new pointValue[size];
    for (int i = 0; i < size; i++) {
        halfPointObjs[i] = array[i];
    }

    return halfPointObjs;
}

pointValue* rightHalf(const pointValue* array, const int size, const int leftSize) {
    const auto halfPointObjs = new pointValue[size];
    for (int i = 0; i < size; i++) {
        halfPointObjs[i] = array[i + leftSize];
    }

    return halfPointObjs;
}

pointValue* merge(const pointValue* b, const pointValue* c, const int bSize, const int cSize) {
    int i = 0;
    int j = 0;
    const int totalSize = bSize + cSize;
    const auto fullPointObjs = new pointValue[totalSize];
    for (int k = 0; k < totalSize; k++) {
        if ( i < bSize && (j >= cSize || b[i].yCoord <= c[j].yCoord )) {
            fullPointObjs[k] = b[i];
            i++;
        } else {
            fullPointObjs[k] = c[j];
            j++;
        }
    }
    return fullPointObjs;
}

pointValue* mergeSort(const pointValue* array, const int size) {
    if (size == 1) {
        // separate array to prevent memory leaks or other shenanigans with dereferencing
        const auto arrayCopy = new pointValue[1];
        arrayCopy[0] = array[0];
        return arrayCopy;
    }

    const int leftMod = (size % 2) == 1 ? 1 : 0;
    const int halfSize = size / 2;
    const int leftSize = halfSize + leftMod;

    const pointValue* leftHalfArr = leftHalf(array, leftSize);
    const pointValue* rightHalfArr = rightHalf(array, halfSize, leftSize);

    const pointValue* b = mergeSort(leftHalfArr, leftSize);
    const pointValue* c = mergeSort(rightHalfArr, halfSize);

    delete[] leftHalfArr;
    delete[] rightHalfArr;

    pointValue* merged = merge(b, c, leftSize, halfSize);

    delete[] b;
    delete[] c;

    return merged;
}

int main () {

    int n;
    cin >> n;

    const auto yVals = new int[n];
    const int pointSize = 2 * n;
    const auto pointObjs = new pointValue[pointSize];

    for (int i = 0; i < n; i++) {
        int x;
        int y;
        cin >> x >> y;
        yVals[i] = y;
    }

    for (int i = 0; i < (n-1); i++) {
        pointValue y1{};
        y1.yCoord = yVals[i];

        pointValue y2{};
        y2.yCoord = i == n-2 ? yVals[0] : yVals[i+1];

        const bool y1High = y1.yCoord > y2.yCoord;
        y1.delta = y1High ? 1 : -1;
        y2.delta = y1High ? -1 : 1;

        pointObjs[2 * i] = y1;
        pointObjs[2 * i + 1] = y2;
    }

    const pointValue* sortedPoints = mergeSort(pointObjs, pointSize);
    const int minY = sortedPoints[0].yCoord;
    const int maxY = sortedPoints[pointSize - 1].yCoord;

    int current = 0;
    int best = 0;

    for (int i = minY; i <= maxY; i++) {
        current += sorted
    }

    cout << n << endl;

    delete[] yVals;
    delete[] pointObjs;
    delete[] sortedPoints;

    return 0;
}