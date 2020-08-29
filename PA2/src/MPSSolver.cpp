#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <assert.h>

#include "MPSSolver.h"

using namespace std;

MPSSolver::MPSSolver(){
    cerr << "Wrong usage of MPSSolver" << endl;
    assert(true);
}

MPSSolver::MPSSolver(char* s){
    // Read data
    fstream fin(s);
    fin >> N;
    assert(N < MAX_N);
    C = CordList(N, 0);

    size_t i, j;
    for(size_t l = 0; l < (N >> 1); ++l){
        fin >> i >> j;
        C[j] = i;
        C[i] = j;
    }
    fin.close();
    CordNum store_num = APPLY_TOP_DOWN ? LIMIT : 0;
    for(size_t i = 0; i < N; ++i){
        M.push_back(CordList(N, store_num));
        Record_C.push_back(BoolList(N, false));
    }
}

void MPSSolver::SolveMPS(){
    if(APPLY_TOP_DOWN){
        TopDownDP(0, N - 1);
        return;
    }
    for(int i = N - 2; i >= 0; --i){
        for(int j = i + 1; j < N; ++j){
            // Solve for M[i][j]
            CordNum k = C[j];
            if(k > j || k < i){          // Case 1
                M[i][j] = M[i][j - 1];
                // Record_C[i][j] = false;
            }
            else if(k < j && k > i){    // Case 2
                CordNum case2A = 1 + M[i][k - 1] + M[k + 1][j - 1];
                CordNum case2B = M[i][j - 1];
                if(case2A >= case2B){
                    M[i][j] = case2A;
                    Record_C[i][j] = true;
                } else {
                    M[i][j] = case2B;
                    // Record_C[i][j] = false;
                }
            }
            else if(k == i){           // Case 3
                M[i][j] = 1 + M[i + 1][j - 1];
                Record_C[i][j] = true;
            }
        }
    }
}

inline CordNum MPSSolver::TopDownDP(CordNum i, CordNum j){
    if(i >= j) return 0;
    if(M[i][j] < LIMIT) return M[i][j];

    CordNum k = C[j];
    if(k > j || k < i){         // Case 1
        return M[i][j] = TopDownDP(i, j - 1);
    }
    else if(k < j && k > i){    // Case 2
        CordNum case2A = 1 + TopDownDP(i, k - 1) + TopDownDP(k + 1, j - 1);
        CordNum case2B = TopDownDP(i, j - 1);
        if(case2A >= case2B){
            Record_C[i][j] = true;
            return M[i][j] = case2A;
        } else {
            return M[i][j] = case2B;
        }
    }
    else if(k == i){            // Case 3
        Record_C[i][j] = true;
        return M[i][j] = 1 + TopDownDP(i + 1, j - 1);
    }
}

void MPSSolver::Report(char* s){
    // Backward to find chosen cords
    CordList output; output.clear();
    Backward(0, N - 1, output);
    sort(output.begin(), output.end());

    fstream fout;
    fout.open(s,ios::out);
    fout << M[0][N - 1] << endl;
    for(size_t i = 0; i < output.size(); ++i){
        fout << output[i] << " " << C[output[i]] << endl;
    }
    fout.close();
}


inline void MPSSolver::Backward(CordNum i, CordNum j, CordList& recList){
    if(i >= j) return;

    CordNum k = C[j];
    if(k > j || k < i){                  // Case 1
        Backward(i, j - 1, recList);
    }
    else if(k < j && k > i){    // Case 2
        if(Record_C[i][j]){ // Case 2B 
            recList.push_back(k);
            Backward(i,     k - 1, recList);
            Backward(k + 1, j - 1, recList);
        } else {
            Backward(i, j - 1, recList);
        }
    }
    else if(k == i){            // Case 3
        recList.push_back(k);
        Backward(i + 1, j - 1, recList);
    }
}

