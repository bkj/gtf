// C++ program for finding minimum cut using Ford-Fulkerson
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

// Number of vertices in given graph
#define V 6
typedef double captype;
/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
int bfs(double rGraph[V][V], int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

// A DFS based function to find all reachable vertices from s.  The function
// marks visited[i] as true if i is reachable from s.  The initial values in
// visited[] must be false. We can also use BFS to find reachable vertices
void dfs(double rGraph[V][V], int s, bool visited[])
{
    visited[s] = true;
    for (int i = 0; i < V; i++)
       if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited);
}

// Prints the minimum s-t cut
void minCut(double graph[V][V], int s, int t)
{
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    double rGraph[V][V]; // rGraph[i][j] indicates residual capacity of edge i-j
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];

    int parent[V];  // This array is filled by BFS and to store path

    // Augment the flow while there is a path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edhes along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        double path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        printf("residual graph printout\n");
        for (u = 0; u < V; u++){
            for (v = 0; v < V; v++)
                 printf("%5.2f ", graph[u][v]);
            printf("\n");
        }
        printf("\n");
    }

    // Flow is maximum now, find vertices reachable from s
    bool visited[V];
    memset(visited, false, sizeof(visited));
    dfs(rGraph, s, visited);

    // Print all edges that are from a reachable vertex to
    // non-reachable vertex in the original graph
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++){
         if (visited[i] && !visited[j] && graph[i][j])
              cout << i << " - " << j << endl;
      }
    return;
}

// Driver program to test above functions
int main()
{

    double lambda1 = 3;

    int n = V-2;
    int e1[] = {0, 0, 1, 1, 2, 3};
    int e2[] = {1, 2, 0, 3, 1, 2};
    int m = 6;

    double tr_cap[V-2];
    double label[V-2];

    double graph[V][V] = {0};
    for(int i = 0; i < m; i++){
      graph[e1[i]+2][e2[i]+2] = lambda1;
    }

    // normalization as did in parametric maxflow
    graph[0][2] = 16-1.25;
    graph[0][3] = 13-1.25;
    graph[4][1] = 20+1.25;
    graph[5][1] = 4+1.25;

    for (int i = 0; i < V; i++){
      for (int j = 0; j < V; j++){
        printf("%5.2f ", graph[i][j]);
      }
      printf("\n");
    }
    printf("\n");

    /* graph I used in this toy test, source node is 0, and sink node is 1
    double graph[V][V] = {{0, 0,  16, 13, 0,  0},
                        {0, 0,  0,  0,  0,  0},
                        {0, 0,  0,  3, 3, 0},
                        {0, 0,  3,  0,  0,  3},
                        {0, 20, 0,  3,  0,  0},
                        {0, 4,  0,  0,  3,  0}};
    */
    minCut(graph, 0, 1);

    return 0;
}
