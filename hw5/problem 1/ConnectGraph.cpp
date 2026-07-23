//
// Created by ncabr on 7/23/26.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> adjacencyList(const int vertices, const int edges, const vector<vector<int>> &graph) {
    vector<vector<int>> list(vertices);
    vector<int> listSizes(vertices);

    //grab how many neighbors per edge
    for (int i = 0; i < edges; i++) {
        const int first = graph[i][0] - 1;
        const int second = graph[i][1] - 1;
        listSizes[first]++;
        listSizes[second]++;
    }

    //need to set sizes to adj list before can actually populate or risk n^2
    for (int i = 0; i < vertices; i++) {
        list[i] = vector<int>(listSizes[i]);
    }

    vector<int> listIndex(vertices);
    for (int i = 0; i < edges; i++) {
        const int first = graph[i][0] - 1;
        const int second = graph[i][1] - 1;
        list[first][listIndex[first]] = second + 1;
        listIndex[first]++;
        list[second][listIndex[second]] = first + 1;
        listIndex[second]++;
    }    return list;
}

vector<vector<int>> bfs(const int targetNode, const int vertices, int edges, const vector<vector<int>> &graph) {
    vector<int> queue(vertices);
    queue[0] = targetNode;
    int queueLength = 1;
    vector<int> visited(vertices);
    int visitCount = 1;
    visited[targetNode - 1] = 1;

    while (queueLength != 0) {
        const int activeVertex = queue[queueLength-1];
        queueLength -= 1;
        vector<int> adjVertex = graph[activeVertex - 1];
        for (const int neighbor : adjVertex) {
            if (neighbor > 0) {
                const bool didVisit = visited[neighbor - 1] == 1;
                if (!didVisit) {
                    visited[neighbor - 1] = 1;
                    queueLength++;
                    queue[queueLength - 1] = neighbor;
                    visitCount++;
                }
            }
        }
    }

    vector<vector<int>> visitedVertices(2);    int visitIndex = 0;
    visitedVertices[0] = vector<int>(1, visitCount);
    visitedVertices[1] = vector<int>(visitCount);
    for (int i = 0; i < vertices; i++) {
        if (visited[i] == 1) {
            visitedVertices[1][visitIndex] = i + 1;
            visitIndex++;
        }
    }
    return visitedVertices;
}

int edgesToAdd(const int vertices, const int edges, const vector<vector<int>> &graph) {
    vector<int> vertexTracker(vertices);
    int addedEdges = 0;
    int targetVertex = 1;
    while (targetVertex <= vertices) {
        if (vertexTracker[targetVertex - 1] == 1) {
            targetVertex++;
            continue;
        }

        vector<vector<int>> visit = bfs(targetVertex, vertices, edges, graph);
        addedEdges++;
        targetVertex++;
        for (int j = 0; j < visit[0][0]; j++) {
            vertexTracker[visit[1][j] - 1] = 1;
        }

    }
    return addedEdges - 1;
}

int main () {

    int vertices;
    int edges;
    cin >> vertices >> edges;

    vector<vector<int>> graph(edges, vector<int>(2));


    for (int i = 0; i < edges; i++) {
        cin >> graph[i][0] >> graph[i][1];
    }

    const vector<vector<int>> adjList = adjacencyList(vertices, edges, graph);

    cout << edgesToAdd(vertices, edges, adjList) << endl;

    return 0;
}