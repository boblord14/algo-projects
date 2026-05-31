//
// Created by false on 5/31/2026.
//

#include <iostream>
using namespace std;

int leftChild(const int i) {
    return 2 * i + 1;
}

int rightChild(const int i) {
    return 2 * i + 2;
}

int parent(const int i) {
    return (i - 1) / 2;
}

void heapifyDown(double* heap, const int pos, const int size) {
    // array indices conversion of doom and despair
    int i = pos;
    while ((leftChild(i) < size && heap[i] < heap[leftChild(i)]) || (rightChild(i) < size && heap[i] < heap[rightChild(i)])) {
        int j;
        if (rightChild(i) >= size || heap[leftChild(i)] > heap[rightChild(i)]) {
            j = leftChild(i);
        } else {
            j = rightChild(i);
        }

        const double temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;

        i = j;
    }
}

double extractMax(double* heap, const int size) {

    const double max = heap[0];
    heap[0] = heap[size-1];
    heapifyDown(heap, 0, size-1);
    return max;
}

void heapifyUp(double* heap, const int pos) {
    int i = pos;
    while ((i > 0) && (heap[i] > heap[parent(i)])) {
        const double temp = heap[i];
        heap[i] = heap[parent(i)];
        heap[parent(i)] = temp;
        i = parent(i);
    }
}

void add(double* heap, const double key, const int size) {
    heap[size] = key;
    heapifyUp(heap, size);
}

int main () {

    int n;
    cin >> n;

    const auto numbers = new double[n];

    for (int i = 0; i < n; i++) {
        double number;
        cin >> number;
        numbers[i] = number;
    }

    auto sumHeap = new double[n*n];
    int heapSize = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            add(sumHeap, (double)numbers[i] + numbers[j], heapSize);
            heapSize++;
        }
    }

    int bestCount = 1;
    double bestValue = extractMax(sumHeap, heapSize);
    heapSize--;

    int currentCount = 1;
    double previousValue = bestValue;

    for (int i = heapSize; i > 0; i--) {

        double currentValue = extractMax(sumHeap, i);

        if (currentValue == previousValue) {
            currentCount++;
        } else {
            if (currentCount >= bestCount) {
                bestCount = currentCount;
                bestValue = previousValue;
            }

            currentCount = 1;
            previousValue = currentValue;
        }
    }

    cout.precision(6);
    cout << bestCount << " " << fixed << bestValue << endl;
    delete[] numbers;
    delete[] sumHeap;

    return 0;
}