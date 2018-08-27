# gtf

Example graph is set inside the files. 
```
double graph[V][V] = {{0, 0,  16, 13, 0,  0},
                        {0, 0,  0,  0,  0,  0},
                        {0, 0,  0,  3, 3, 0},
                        {0, 0,  3,  0,  0,  3},
                        {0, 20, 0,  3,  0,  0},
                        {0, 4,  0,  0,  3,  0}};
                        
source  is node 0, and sink is node 1. 
```

#### Usage

```
# Compile
make

# run maxflow with Ford-Fulkerson Algorithm:
./bin/ffa

# run maxflow with parametric maxflow:
./bin/gtf
```