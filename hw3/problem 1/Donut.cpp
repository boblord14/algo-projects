//
// Created by ncabr on 6/16/26.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void insertion_sort(vector<int>& array) {
    for (int i = 1; i < array.size(); i++) {
        const int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int getMedian(vector<int> &array) {
    insertion_sort(array);
    return array[floor(static_cast<double>(array.size())/2.0)];
}

int select(vector<int> &input, int k) {
    if (input.size() <= 5) {
        insertion_sort(input);
        return input[k];
    }

    vector<vector<int>> groups(ceil(static_cast<double>(input.size())/5.0));

    int i = 0;
    int j = 0;
    groups[0] = vector<int>(5);
    for (const int value : input) {
        if (j > 4) {
            j = 0;
            i++;
            groups[i] = vector<int>((i + 1) * 5 > input.size() ? input.size() - i*5 : 5);
        }
        groups[i][j++] = value;
    }

    vector<int> medians(groups.size());
    for (int l = 0; l < groups.size(); l++) {
        medians[l] = getMedian(groups[l]);
    }
    const int med = select(medians, floor(input.size()/10));

    vector<int> leftArray(input.size());
    vector<int> rightArray(input.size());

    i = 0;
    j = 0;
    for (const int l : input) {
        if (l <= med) {
            leftArray[i] = l;
            i++;
        }else {
            rightArray[j] = l;
            j++;
        }
    }

    vector<int> realLeftArray(i);
    vector<int> realRightArray(j);

    for (int l = 0; l < realLeftArray.size(); l++) {
        realLeftArray[l] = leftArray[l];
    }
    for (int l = 0; l < realRightArray.size(); l++) {
        realRightArray[l] = rightArray[l];
    }

    if (k < i) {
        return select(realLeftArray, k);
    }
    if (k == i) {
        return med;
    }
    //if k > j
    return select(realRightArray, k-i);


}


int main () {

    int n;
    cin >> n;

    vector<int> xCoords(n);
    vector<int> yCoords(n);

    for (int i = 0; i < n; i++) {
        int x;
        int y;
        cin >> x >> y;
        xCoords[i] = x;
        yCoords[i] = y;
    }

    const int xMed = select(xCoords, floor(n/2));
    const int yMed = select(yCoords, floor(n/2));

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += abs(xMed - xCoords[i]) + abs(yMed - yCoords[i]);
    }

    cout << sum << endl;

    return 0;
}
