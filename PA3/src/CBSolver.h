#ifndef _CBSOLVER_H
#define _CBSOLVER_H

#include <vector>
#include <utility>
using namespace std;

typedef size_t                      GNum;
typedef pair<GNum, int>             VWpair;
typedef vector<VWpair>              VList;     // <vertex, weight>
typedef pair<GNum, GNum>            Vertices;
typedef vector<short>               RecList;

const int NINF = -2147483647;

// Edge object for undirected graph (compute Kruskal MST)
class Edge {
    public:
        Edge(const GNum _v1, const GNum _v2, const int _w):
            v1(_v1), v2(_v2), weight(_w) {}
        inline Vertices      get_vertices() const { return Vertices(v1, v2); }
        inline GNum          get_vertex_1() const { return v1; }
        inline GNum          get_vertex_2() const { return v2; }
        inline int           get_weight() const { return weight; }
        const bool           operator < (const Edge& e) const { return weight < e.get_weight(); }

    private:
        GNum                 v1;
        GNum                 v2;
        int                  weight;
};

// Disjoint Set for computing Kruskal MST
class DisjointSet {
    public:
        DisjointSet(const GNum _N):
            N(_N) {
                par = vector<GNum>(N, 0); for(size_t i = 0; i < N; ++i) par[i] = i;
                rank = vector<GNum>(N, 0);
            }
        inline GNum         find(const GNum x) { return (x == par[x]) ? x : par[x] = find(par[x]); }
        inline void         join(GNum x, GNum y) { x = find(x); y = find(y); if (x == y) return;
                                                    if (rank[x] < rank[y]) par[x] = y; 
                                                    else { par[y] = x; if(rank[x] == rank[y]) rank[x]++; } }
        inline bool         same(const GNum x, const GNum y) { return find(x) == find(y); }

    private:
        GNum                N;
        vector<GNum>        par;
        vector<GNum>        rank;
};

// Cycle Breaking Solver
class CBSolver {
    public:
                            CBSolver();
                            CBSolver(char*);                   // constructor, including read files
                            ~CBSolver();
        void                Solve();                           // Solve problem
        void                Report(char*) const;               // Report answer
        
    private:
        GNum                N;                                 // Number of vertices
        GNum                M;                                 // Number of edges
        bool                directed;                          // Directed graph or not

        vector<VList>       Graph;                             // Adjacency list
        vector<Edge>        EdgeList;                          // List of edges

        vector<vector<int> >EdgeMatrix;                        // Adjacency matrix for directed graph
        // vector<vector<int>> EdgeMatrix_2;                      // Adjacency matrix for directed graph
        vector<VList>       inv_Graph;                         // Adjacency list
        vector<int>         deg_out;                           // Out degree
        vector<int>         deg_in;                            // In degree
        vector<int>         weight_out;                        // Out weight
        vector<int>         weight_in;                         // In weight

        int                 AnswerWeight;                      // Minimum cost for breaking cycles
        vector<Edge>        Answer;                            // Answer

        // Functions
        inline void         ReadFile(char*);                   // Read graph in
        inline bool         CheckCycle(GNum, GNum, RecList&);  // Check if there is any cycle in the graph
        void                Kruskal();                         // Kruskal's MST algorithm
        vector<GNum>        GRAlgorithm();                     // GR algorithm
        void                GRPostProcess(vector<GNum>&);      // Post processing of GR algorithm
        inline void         FindBackEdge(GNum, GNum, RecList&);// 
        void                Output(char*) const;               // Print answer
};

#endif