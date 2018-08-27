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

void graph_tv(
        double *flow_from_source,  // value of nodes
        double *flow_to_sink,  // value of nodes
        
        int num_nodes,    // number of nodes
        int num_edges,    // number of edges
        int* edge_src,
        int* edge_trg,
        double lambda,
        float error,
        
        int* assignments
    ) {

    // Graph::node_id nodes[2];
    // Graph *g = new Graph();

    // nodes[0] = g -> add_node();
    // nodes[1] = g -> add_node();
    // g -> set_tweights(nodes[0], 1, 5);
    // g -> set_tweights(nodes[1], 2, 6);
    // g -> add_edge(nodes[0], nodes[1], 3, 4);

    // Graph::flowtype flow = g -> maxflow();

    // printf("Flow = %f\n", flow);

        
    double dval, dr, drd;

    dr = lambda;

    Graph::node_id* nodes, no;

    if (num_nodes <= 2 || num_edges <= 2) {
        fprintf(stderr,"error: bad size\n");
        exit(0);
    }

    nodes = (Graph::node_id *) malloc(num_nodes * sizeof(Graph::node_id));
    Graph *G = new Graph();
    
    // Initialize nodes
    for (int i = 0; i < num_nodes; i++) {
        no = nodes[i] = G->add_node();
        G->set_tweights(no, flow_from_source[i], flow_to_sink[i]);
    }
    printf("node flow: %f\n", G->flow);
    
    // Initialize edges
    for (int i = 0; i < num_edges; i++) {
        G->add_edge(nodes[edge_src[i]], nodes[edge_trg[i]], dr, 0.0);
    }
    printf("edge flow: %f\n", G->flow);
    
    // // Run dyadicparametricTV
    // // G->dyadicparametricTV(error);
    double x = G->maxflow();
    cout << "flow=" << x << endl;
    
    // Export values
    for (int i = 0; i < num_nodes; i++) {
        assignments[i] = G->what_segment(nodes[i]);
    }
    
    delete G;
    free(nodes);
}

int main(){

    double lambda             = 3;                    // default edge weight
    int edge_src[]            = {0, 0, 1, 1, 2, 3};   // edgelist
    int edge_trg[]            = {1, 2, 0, 3, 1, 2};   // ^^
    double flow_from_source[] = {16, 13, 0, 0};       // edge weight from source to node
    double flow_to_sink[]     = {0, 0, 20, 4};        // edge weight from node to sink

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
    
    int *assignments = new int[num_nodes];
    graph_tv(flow_from_source, flow_to_sink, num_nodes, num_edges, edge_src, edge_trg, lambda, 0.0, assignments);

    cout << endl << "MinCut:" << endl;
    for(int i = 0; i < num_edges; i++){
        int src_partition = assignments[edge_src[i]];
        int trg_partition = assignments[edge_trg[i]];
        if((src_partition == Graph::SOURCE) && (trg_partition == Graph::SINK)) {
            cout << edge_src[i] << " -> " << edge_trg[i] << endl;
        }
    }
    
    return 0;
}
