#pragma once
#include<iostream>
#include<vector>
using namespace std;
#ifndef _LIB_H_
#define _LIB_H_


int leading(char *input);
void dij(int number,int mode,char *name);   //Dijkstra algorithm
void floyd(int number,int mode,char *name);      //floyd algorithm

class Edge {
public:
    int source, destination, weight;

    Edge(int s = 0, int d = 0, int w = 0) :source(s), destination(d), weight(w) {}
};

class Graph {
public:
    int num_of_vertice;   // Edge.source/destination : 0, 1,  ..., num_of_vertice - 1
    vector<Edge> edges;

    Graph(int n = 0) :num_of_vertice(n) {}
};

void BellmanFord(Graph* graph, int source);

#endif // lib.h

