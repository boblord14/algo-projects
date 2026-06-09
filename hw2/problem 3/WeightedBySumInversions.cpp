//
// Created by false on 6/9/2026.
//

#include <iostream>
using namespace std;

struct sumInversion {
    int inversionCount;
    int* sumArray;
};

sumInversion* leftHalf(const sumInversion* array, const int size) {

    auto* halfPointInversion = new sumInversion{0, new int[size]};
    for (int i = 0; i < size; i++) {
        halfPointInversion->sumArray[i] = array->sumArray[i];
    }

    return halfPointInversion;
}

sumInversion* rightHalf(const sumInversion* array, const int size, const int leftSize) {
    auto* halfPointInversion = new sumInversion{0, new int[size]};
    for (int i = 0; i < size; i++) {
        halfPointInversion->sumArray[i] = array->sumArray[i + leftSize];
    }

    return halfPointInversion;
}

sumInversion* mergeAndCount(const sumInversion* b, const sumInversion* c, const int bSize, const int cSize) {
    int i = 0;
    int j = 0;
    const int totalSize = bSize + cSize;
    auto* mergedInversion = new sumInversion{0, new int[totalSize]};

    for (int k = 0; k < totalSize; k++) {
        if ( i < bSize && (j >= cSize || b->sumArray[i] <= c->sumArray[j])) {
            mergedInversion->sumArray[k] = b->sumArray[i];
            i++;
        } else {
            mergedInversion->sumArray[k] = c->sumArray[j];
            j++;
            for (int l = i; l < bSize; l++) {
                mergedInversion->inversionCount = b->sumArray[l] + mergedInversion->sumArray[k];
            }
        }
    }

    return mergedInversion;
}

sumInversion* sortAndCount(const sumInversion* array, const int size) {
    if (size == 1) {
        // separate array to prevent memory leaks or other shenanigans with dereferencing
        auto* copy = new sumInversion{0, new int[1]};
        copy->sumArray[0] = array->sumArray[0];
        return copy;
    }

    const int leftMod = (size % 2) == 1 ? 1 : 0;
    const int halfSize = size / 2;
    const int leftSize = halfSize + leftMod;

    const auto* leftInv = sortAndCount(leftHalf(array, leftSize), leftSize);
    const auto* rightInv = sortAndCount(rightHalf(array, halfSize, leftSize), halfSize);

    auto* xInv = mergeAndCount(leftInv, rightInv, leftSize, halfSize);

    const int inversionCount = leftInv->inversionCount + rightInv->inversionCount + xInv->inversionCount;
    xInv->inversionCount = inversionCount;

    delete[] leftInv;
    delete[] rightInv;
    return xInv;

}

int main () {

    int n;
    cin >> n;

    const auto* inputInversion = new sumInversion{0, new int[n]};

    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
        inputInversion->sumArray[i] = b;
    }

    auto* finalArray = sortAndCount(inputInversion, n);

    cout << finalArray->inversionCount << endl;

    delete inputInversion;

    return 0;
}