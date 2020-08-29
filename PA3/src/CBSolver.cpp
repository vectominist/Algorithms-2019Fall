#include <iostream>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <queue>
using namespace std;

#include "CBSolver.h"

// ===========================================
// ============ Utility Functions ============
// ===========================================

const bool cmp_1(const VWpair& a, const VWpair& b){
    return a.second < b.second;
}
const bool cmp_2(const VWpair& a, const VWpair& b){
    return a.second > b.second;
}

// ===========================================
// ============ Public  Functions ============
// ===========================================

CBSolver::CBSolver(){
    cerr << "Please use the other constructor" << endl;
    assert(false);
}

CBSolver::CBSolver(char* filename){
    ReadFile(filename);
}

CBSolver::~CBSolver(){
    Graph.clear();
    EdgeList.clear();
    EdgeMatrix.clear();
    inv_Graph.clear();
    deg_out.clear();
    deg_in.clear();
    weight_out.clear();
    weight_in.clear();
    AnswerWeight = 0;
    Answer.clear();
}

void 
CBSolver::Solve(){
    // Check if there is any cycle in the graph
    // RecList visited(N, 0);
    // bool solve = false;
    // for(GNum v = 0; v < N; ++v){
    //     if(visited[v] == 0){
    //         bool check = CheckCycle(v, -1, visited);
    //         if(check)
    //             solve = true;
    //     }
    // }

    // if(!solve)
    //     return;

    // Cycle breaking algorithm
    if(directed){
        vector<GNum> s = GRAlgorithm();
        GRPostProcess(s);
    } else {
        Kruskal();
    }
}

void 
CBSolver::Report(char* filename) const {
    Output(filename);
}

// ===========================================
// ============ Private Functions ============
// ===========================================

inline void 
CBSolver::ReadFile(char* filename){
    fstream fin(filename);

    char check_type[3];
    fin >> check_type;
    fin >> N >> M;

    if(check_type[0] == 'd'){
        directed = true;
        // EdgeMatrix.clear();
        // EdgeMatrix_2.clear();
        // for(size_t i = 0; i < N; ++i){
        //     EdgeMatrix.push_back(vector<int>(N, NINF));
        //     EdgeMatrix_2.push_back(vector<int>(N, NINF));
        // }
        deg_in     = vector<int>(N,0);
        deg_out    = vector<int>(N,0);
        weight_in  = vector<int>(N,0);
        weight_out = vector<int>(N,0);
    } else {
        directed = false;
        // EdgeList.clear();
        // inv_Graph.clear();
    }

    if(directed){
        Graph.clear();
        for(size_t i = 0; i < N; ++i){
            Graph.push_back(VList());
            if(directed)
                inv_Graph.push_back(VList());
        }
    }
    

    GNum v1, v2;
    int weight;
    for(size_t i = 0; i < M; ++i){
        fin >> v1 >> v2 >> weight;
        if(directed){
            // EdgeMatrix[v1][v2] = weight;
            // EdgeMatrix_2[v1][v2] = weight;
            Graph[v1].push_back(VWpair(v2, weight));
            inv_Graph[v2].push_back(VWpair(v1, weight));
            deg_out[v1]    += 1;
            deg_in[v2]     += 1;
            weight_out[v1] += weight;
            weight_in[v2]  += weight;
        } else {
            EdgeList.push_back(Edge(v1, v2, weight));
            // Graph[v1].push_back(VWpair(v2, weight));
            // Graph[v2].push_back(VWpair(v1, weight));
        }
    }

    // if(directed){
    //     for(size_t i = 0; i < N; ++i){
    //         sort(Graph[i].begin(), Graph[i].end(), cmp_1);
    //         sort(inv_Graph[i].begin(), inv_Graph[i].end(), cmp_1);
    //     }
    // }
    fin.close();
    Answer.clear();
    AnswerWeight = 0;
}

inline bool 
CBSolver::CheckCycle(GNum v, GNum parent, RecList& visited){
    if(visited[v] ==  1) return false; // Already Traversed
    if(visited[v] == -1) return true;  // Still in DFS tree
    visited[v] = -1;
    for(size_t i = 0; i < Graph[v].size(); ++i){
        if(Graph[v][i].first == parent && !directed)
            continue;
        if(CheckCycle(Graph[v][i].first, v, visited)){
            return true;
        }
    }
    visited[v] = 1;
    return false;
}

void 
CBSolver::Kruskal(){
    DisjointSet edge_union(N);

    sort(EdgeList.begin(), EdgeList.end());
    vector<bool> used(M, false);

    for(int i = M - 1; i >= 0; --i){
        if(edge_union.same(EdgeList[i].get_vertex_1(), EdgeList[i].get_vertex_2()) == false){
            // cerr << EdgeList[i].get_vertex_1() << " " << EdgeList[i].get_vertex_2() << " " << EdgeList[i].get_weight() << endl;
            used[i] = true;
            edge_union.join(EdgeList[i].get_vertex_1(), EdgeList[i].get_vertex_2());
        }
    }
    
    for(int i = 0; i < M; ++i){
        if(used[i] == false){
            Answer.push_back(EdgeList[i]);
            AnswerWeight += EdgeList[i].get_weight();
        }
    }
}

vector<GNum>
CBSolver::GRAlgorithm(){
    vector<GNum> s1;
    vector<GNum> s2;
    vector<bool> removed(N,false);
    int removed_count = 0;
    queue<GNum>  sink;     // Sinks   <=> deg_out == 0
    queue<GNum>  source;   // Sources <=> deg_in == 0

    for(GNum i = 0; i < N; ++i){
        if(deg_out[i] == 0){
            sink.push(i);
            removed[i] = true;
        }
        else if(deg_in[i] == 0){
            source.push(i);
            removed[i] = true;
        }
    }
    while(removed_count < N){
        // Remove sinks
        while(!sink.empty()){
            GNum u = sink.front(); sink.pop();
            for(size_t v = 0; v < inv_Graph[u].size(); ++v){
                if(!removed[inv_Graph[u][v].first]){
                    if((--deg_out[inv_Graph[u][v].first]) == 0){
                        sink.push(inv_Graph[u][v].first);
                        removed[inv_Graph[u][v].first] = true;
                    }
                    weight_out[inv_Graph[u][v].first] -= inv_Graph[u][v].second;
                }
            }
            removed_count++;
            s2.push_back(u);
            // cerr << "sink   " << u << endl;
        }
        // Remove sources
        while(!source.empty()){
            GNum u = source.front(); source.pop();
            for(size_t v = 0; v < Graph[u].size(); ++v){
                if(!removed[Graph[u][v].first]){
                    if((--deg_in[Graph[u][v].first]) == 0){
                        source.push(Graph[u][v].first);
                        removed[Graph[u][v].first] = true;
                    }
                    weight_in[Graph[u][v].first] -= Graph[u][v].second;
                }
            }
            removed_count++;
            s1.push_back(u);
            // cerr << "source " << u << endl;
        }
        if(removed_count == N)
            break;
        // Remove max delta(u) = d+(u) - d-(u)
        GNum max_u = 0;
        int max_w = NINF;
        for(GNum u = 0; u < N; ++u){
            if(!removed[u]){
                if(weight_out[u] - weight_in[u] > max_w){
                    max_w = weight_out[u] - weight_in[u];
                    max_u = u;
                }
            }
        }
        removed[max_u] = true;
        for(size_t v = 0; v < inv_Graph[max_u].size(); ++v){
            if(!removed[inv_Graph[max_u][v].first]){
                if((--deg_out[inv_Graph[max_u][v].first]) == 0){
                    sink.push(inv_Graph[max_u][v].first);
                    removed[inv_Graph[max_u][v].first] = true;
                }
                weight_out[inv_Graph[max_u][v].first] -= inv_Graph[max_u][v].second;
            }
        }
        for(size_t v = 0; v < Graph[max_u].size(); ++v){
            if(!removed[Graph[max_u][v].first]){
                if((--deg_in[Graph[max_u][v].first]) == 0){
                    source.push(Graph[max_u][v].first);
                    removed[Graph[max_u][v].first] = true;
                }
                weight_out[Graph[max_u][v].first] -= Graph[max_u][v].second;
            }
        }
        removed_count++;
        s1.push_back(max_u);
        // cerr << "max    " << max_u << endl;
    }
    
    // assert(removed_count == N);
    // cerr << removed_count << endl;
    // cerr << s1.size() << " " << s2.size() << endl;
    vector<GNum> final_s(s1);
    for(int i = s2.size() - 1; i >= 0; --i){
        final_s.push_back(s2[i]);
    }

    // for(int i = 0; i < final_s.size(); ++i){
    //     cerr << final_s[i] << " ";
    // }
    // cerr << endl;

    return final_s;
}

void
CBSolver::GRPostProcess(vector<GNum>& s){
    assert(s.size() == N);
    vector<GNum> Vrank(N, 0);
    RecList visited(N, 0);
    for(size_t i = 0; i < N; ++i){
        Vrank[s[i]] = i;
    }
    for(size_t i = 0; i < N; ++i){
        // if(visited[i] == 0){
        //     FindBackEdge(s[i], -1, visited);
        // }
        for(size_t j = 0; j < Graph[i].size(); ++j){
            if(Vrank[Graph[i][j].first] < Vrank[i]){
                AnswerWeight += Graph[i][j].second;
                Answer.push_back(Edge(i, Graph[i][j].first, Graph[i][j].second));
            }
        }
    }
}

inline void
CBSolver::FindBackEdge(GNum v, GNum parent, RecList& visited){
    if(visited[v] ==  1) return; // Already Traversed
    if(visited[v] == -1){ // Still in DFS tree
        AnswerWeight += EdgeMatrix[parent][v];
        Answer.push_back(Edge(parent, v, EdgeMatrix[parent][v]));
        return;
    }
    visited[v] = -1;
    for(size_t i = 0; i < Graph[v].size(); ++i){
        FindBackEdge(Graph[v][i].first, v, visited);
    }
    visited[v] = 1;
}

void 
CBSolver::Output(char* filename) const {
    fstream fout;
    fout.open(filename,ios::out);
    
    fout << AnswerWeight << endl;
    for(size_t i = 0; i < Answer.size(); ++i){
        fout << Answer[i].get_vertex_1() << " " << Answer[i].get_vertex_2() << " " << Answer[i].get_weight() << '\n';
    }

    fout.close();
}