//
// Created by false on 5/31/2026.
//

#include <iostream>
using namespace std;

int leftChild(int i) {
    return 2 * i + 1;
}

int rightChild(int i) {
    return 2 * i + 2;
}

int parent(int i) {
    return (i - 1) / 2;
}

void heapifyDown(int* heap, int pos, int size) {
    // array indices conversion of doom and despair
    int i = pos;
    while ((leftChild(i) < size && heap[i] < heap[leftChild(i)]) || (rightChild(i) < size && heap[i] < heap[rightChild(i)])) {
        int j;
        if (rightChild(i) >= size || heap[leftChild(i)] > heap[rightChild(i)]) {
            j = leftChild(i);
        } else {
            j = rightChild(i);
        }

        const int temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;

        i = j;
    }
}

int extractMax(int* heap, int size) {

    int max = heap[0];
    heap[0] = heap[size-1];
    heapifyDown(heap, 0, size-1);
    return max;
}

void heapifyUp(int* heap, int pos) {
    int i = pos;
    while ((i > 0) && (heap[i] > heap[parent(i)])) {
        const int temp = heap[i];
        heap[i] = heap[parent(i)];
        heap[parent(i)] = temp;
        i = parent(i);
    }
}

void add(int* heap, int key, int size) {
    heap[size] = key;
    heapifyUp(heap, size);
}

bool movePlanter(int p, int plants[], int r, int planters[]) {

    // potential segfault catcher
    if (r == 0) return false;

    for (int i = p; i > 0; i--) {
        int plantBiggest = extractMax(plants, i);
        int planterBiggest = extractMax(planters, r);

        // no planters of sufficient size remaining(job failed)
        if (planterBiggest <= plantBiggest) {
            return false;
        }

        // otherwise, perform the move
        add(planters, plantBiggest, r-1); // free up the pot the plant used to be in
    }
    // no plants to move(job done)
    return true;

}

int main () {

    int p;
    int r;
    cin >> p >> r;

    auto plants   = new int[p];
    auto planters = new int[r];


    for (int i = 0; i < p; i++) {
        int plant;
        cin >> plant;
        add(plants, plant, i);
    }

    for (int i = 0; i < r; i++) {
        int planter;
        cin >> planter;
        add(planters, planter, i);
    }

    if (movePlanter(p, plants, r, planters)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    delete[] plants;
    delete[] planters;

    return 0;
}