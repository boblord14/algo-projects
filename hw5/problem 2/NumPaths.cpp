//
// Created by false on 7/23/2026.
//
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

constexpr int MAX_ENTRIES = 1000;

typedef struct {
    int entries[MAX_ENTRIES];
    int head;
    int tail;
} queue_t;

// Function to check if the queue is empty
static int is_queue_empty(const queue_t *q) {
    return q->head == q->tail;
}

// Function to check if the queue is full
static int is_queue_full(const queue_t *q) {
    return ((q->tail + 1) % MAX_ENTRIES) == q->head;
}

// Function to add an element to the queue (Enqueue operation)
static void enqueue(queue_t *q, const int e) {
    if (is_queue_full(q)) {
        return;
    }
    q->entries[q->tail] = e;
    q->tail = (q->tail + 1) % MAX_ENTRIES;
}

// Function to remove an element from the queue (Dequeue operation)
static int dequeue(queue_t *q) {
    if (is_queue_empty(q)) {
        return 0;
    }

    const int e = q->entries[q->head];
    q->head = (q->head + 1) % MAX_ENTRIES;
    return e;
}

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

vector<int> bfs(const int targetNode, const int vertices, const vector<vector<int>> &graph) {

    queue_t queue{};
    enqueue(&queue, targetNode);

    vector<int> visited(vertices, -1); // still just O(vertices), could write out the for but same time complexity
    int visitCount = 1;
    visited[targetNode - 1] = 0;

    while (!is_queue_empty(&queue)) {
        const int activeVertex = dequeue(&queue);
        vector<int> adjVertex = graph[activeVertex - 1];
        for (const int neighbor : adjVertex) {
            if (neighbor > 0) {
                const bool didVisit = visited[neighbor - 1] != -1;
                if (!didVisit) {
                    visited[neighbor - 1] = visited[activeVertex - 1] + 1;
                    enqueue(&queue, neighbor);
                    visitCount++;
                }
            }
        }
    }

    vector<int> visitedVertices(vertices);

    for (int i = 0; i < vertices; i++) {
        if (visited[i] != -1) {
            visitedVertices[i] = visited[i];
        }
    }
    return visitedVertices;
}

int getMaxPaths(const int vertices, const int edges, const int s, const int t, const vector<vector<int>> &graph) {
    const vector<vector<int>> adjList = adjacencyList(vertices, edges, graph);
    const vector<int> sBFS = bfs(s, vertices, adjList);
    const vector<int> tBFS = bfs(t, vertices, adjList);
    const int shortestPathToT = sBFS[t-1];

    if (shortestPathToT == -1) {
        return 0;
    }

    queue_t queue{};
    enqueue(&queue, t);

    vector<int> pathCount(vertices);
    pathCount[t-1] = 1;

    vector<int> visited(vertices);
    visited[t-1] = 1;

    while (!is_queue_empty(&queue)) {
        const int activeVertex = dequeue(&queue);
        for (const int adjValue : adjList[activeVertex - 1]) {
            if (sBFS[adjValue - 1] != -1 && sBFS[adjValue - 1] + tBFS[adjValue - 1] == shortestPathToT && sBFS[adjValue - 1] == sBFS[activeVertex - 1] - 1) {
                pathCount[adjValue - 1] += pathCount[activeVertex - 1];
                if (visited[adjValue - 1] != 1) {
                    enqueue(&queue, adjValue);
                    visited[adjValue - 1] = 1;
                }
            }
        }
    }

    return pathCount[s - 1];
}

int main () {

    int vertices;
    int edges;
    cin >> vertices >> edges;

    int s;
    int t;
    cin >> s >> t;

    vector<vector<int>> graph(edges, vector<int>(2));


    for (int i = 0; i < edges; i++) {
        cin >> graph[i][0] >> graph[i][1];
    }

    cout << getMaxPaths(vertices, edges, s, t, graph) << endl;

    return 0;
}