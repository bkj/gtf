#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <map>
#include <set>
#include <sstream>

#include "graph.h"

using namespace std;

void graph_tv(double *node_values,  // value of nodes
        int num_nodes,    // number of nodes
        int num_edges,    // number of edges
        int* edge_src,
        int* edge_trg,
        double lambda,
        float error) {
    
    double dval, dr, drd;

    dr = lambda;

    Graph::node_id * nodes, no;

    if (num_nodes <= 2 || num_edges <= 2) {
        fprintf(stderr,"error: bad size\n");
        exit(0);
    }

    nodes = (Graph::node_id *) malloc(num_nodes * sizeof(Graph::node_id));
    Graph *G = new Graph();
    
    // Initialize nodes
    for (int i = 0; i < num_nodes; i++) {
        no = nodes[i] = G->add_node();
        G->set_tweights(no, node_values[i], 0.);
    }
    
    // Initialize edges
    for (int i = 0; i < num_edges; i++) {
        G->add_edge(nodes[edge_src[i]], nodes[edge_trg[i]], dr, dr);
    }
    
    // Run dyadicparametricTV
    G->dyadicparametricTV(error);
    
    // Export values
    for (int i = 0; i < num_nodes; i++) {
        node_values[i] = G->what_value(nodes[i]);
    }
    
    delete G;
    free(nodes);
}

int main(){

    double lambda = 3;
    int edge_src[] = {0, 0, 1, 1, 2, 3};
    int edge_trg[] = {1, 2, 0, 3, 1, 2};
    
    // Compute number of edges
    int num_edges = sizeof(edge_src) / sizeof(edge_src[0]);
    
    // Compute number of nodes
    int num_nodes = 0;
    for (int i = 0; i < num_edges; i++) {
        if (edge_src[i] > num_nodes) {
            num_nodes = edge_src[i];
        }
        if (edge_trg[i] > num_nodes) {
            num_nodes = edge_trg[i];
        }        
    }
    num_nodes++;
    
    cout << "num_nodes: " << num_nodes << endl;
    cout << "num_edges: " << num_edges << endl;

    // Initial node values
    double *node_values = new double[num_nodes];
    node_values[0] = 16;
    node_values[1] = 13;
    node_values[2] = -20;
    node_values[3] = -4;

    graph_tv(node_values, num_nodes, num_edges, edge_src, edge_trg, lambda, 0.0);

    cout << endl << "Results:" << endl;
    for(int i = 0; i < num_nodes; i++){
        cout << node_values[i] << endl;
    }
    
    return 0;
}
