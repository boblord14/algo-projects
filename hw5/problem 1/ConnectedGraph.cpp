//
// Created by ncabr on 7/23/26.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int main () {

    int vertices;
    int edges;
    cin >> vertices >> edges;

    vector<vector<int>> graph(edges, vector<int>(2));


    for (int i = 0; i < edges; i++) {
        cin >> graph[i][0] >> graph[i][1];
    }

    cout << edges << endl;

    return 0;
}