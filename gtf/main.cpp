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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "graph.h"
#include <time.h>

using namespace std;

void graph_tv(double *Y,// value of nodes
        int n, //number of nodes
        int m, // number of edges
        int* edges1,
        int* edges2,
//an array of edges of size m. There is an edge edges1[i] -> edges2[i]
        double lambda,
        float erreur)
{
        int i;
    double dval,dr,drd;

    dr=lambda;

    Graph::node_id * nodes, no;

    if (n <=2 || m <= 2)
        { fprintf(stderr,"error: bad size\n"); exit(0); }

    nodes = (Graph::node_id *) malloc(n*sizeof(Graph::node_id));
    Graph *BKG = new Graph();
    for (i=0;i<n;i++) {
        no=nodes[i]=BKG->add_node();
        BKG->set_tweights(no,Y[i],0.);
    }
    for (i=0;i<m;i++) {
        BKG->add_edge(nodes[edges1[i]],nodes[edges2[i]],dr,dr);
    }
    BKG->dyadicparametricTV(erreur);
    for (i=0;i<n;i++) Y[i]=BKG->what_value(nodes[i]);
         delete BKG; free(nodes);
}

int main(){

    double lambda1 = 3;

    int n = 4;
    int e1[] = {0, 0, 1, 1, 2, 3};
    int e2[] = {1, 2, 0, 3, 1, 2};
    int m = 6;

    double *Y = new double[n];
    Y[0] = 16;
    Y[1] = 13;
    Y[2] = -20;
    Y[3] = -4;

	  graph_tv(Y, n, m, e1, e2, lambda1, 0.0);

    cout << endl << "gtf results are (not tr_cap)" << endl;
    for(int i = 0; i < n; i++){
        cout << Y[i] << endl;
    }
    return 0;
}
