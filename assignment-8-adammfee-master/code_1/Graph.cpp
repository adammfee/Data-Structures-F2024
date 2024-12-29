#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;


void Graph::addVertex(string name){
    //TODO
    int size = vertices.size();
    for (int i = 0; i < size; i++) {
        if (vertices[i]->name == name) {
            cout << vertices[i]->name << " found." << endl;
            return;
        }
    }

    vertex* newVert = new vertex;
    newVert->name = name;
    vertices.push_back(newVert);
}

void Graph::addEdge(string v1, string v2){
    //TODO
    int size = vertices.size();
    bool vOne = false;
    bool vTwo = false;
    vertex *start, *end;

    if (v1 == v2) {
        return;
    }

    for (int i = 0; i < size; i++) {
        if (vertices[i]->name == v1) {
            start = vertices[i];
            vOne = true;
        }

        if (vertices[i]->name == v2) {
            end = vertices[i];
            vTwo = true;
        }
    }

    if (vOne && vTwo) {
        adjVertex* newEdge = new adjVertex;
        newEdge->v = end;
        start->adj.push_back(*newEdge);

        adjVertex* endEdge = new adjVertex;
        endEdge->v = start;
        end->adj.push_back(*endEdge);
    }
}

void Graph::displayEdges(){
    //TODO
    int vSize = vertices.size();
    int eSize;
    for (int i = 0; i < vSize; i++) {
        cout << vertices[i]->name << " --> ";
        eSize = vertices[i]->adj.size();
        for (int j = 0; j < eSize; j++) {
            cout << vertices[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    //TODO
    vertex* source;
    int size = vertices.size();
    for (int i = 0; i < size; i++) {
        if (vertices[i]->name == sourceVertex) {
            source = vertices[i];
        }
    }

    source->visited = true;
    source->distance = 0;

    queue<vertex*> q;
    q.push(source);

    cout << "Starting vertex (root): " << source->name << "-> ";

    while (!q.empty()) {
        vertex* n = q.front();
        q.pop();

        int nSize = n->adj.size();

        for (int i = 0; i < nSize; i++) {
            vertex* neighbor = n->adj[i].v;
            if (!neighbor->visited) {
                neighbor->visited = true;
                neighbor->distance = n->distance + 1;
                neighbor->previous = n;
                
                cout << neighbor->name << "(" << neighbor->distance << ")" << " ";
                q.push(neighbor);
            }
        }
    }
    cout << endl << endl;
}

int Graph::findShortestPathBetweenBuildings(string source, string dest) {
    //TODO
    vertex* src;
    vertex* target;
    int size = vertices.size();

    for (int i = 0; i < size; i++) {
        if (vertices[i]->name == source) {
            src = vertices[i];
        }

        if (vertices[i]->name == dest) {
            target = vertices[i];
        }
    }

    src->distance = 0;
    src->visited = true;

    queue<vertex*> q;
    q.push(src);

    while (!q.empty()) {
        vertex* dQ = q.front();
        q.pop();

        if (dQ == target) {
            break;
        }

        int adjSize = dQ->adj.size();
        for (int i = 0; i < adjSize; i++) {
            vertex* v = dQ->adj[i].v;

            if (!v->visited) {
                v->distance = dQ->distance + 1;
                v->previous = dQ;
                v->visited = true;
                q.push(v);
            }
        }
    }

    vector<string> path;
    for (vertex* v = target; v != NULL; v = v->previous) {
        path.push_back(v->name);
    }

    int pSize = path.size();
    for (int i = 0; i < pSize; i++) {
        cout << path[i] << endl;
    }

    cout << "Shortest Path Distance: " << pSize - 1 << endl;

    return target->distance;
}

