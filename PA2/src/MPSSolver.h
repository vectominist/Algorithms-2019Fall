#ifndef _MPSSOLVER_H
#define _MPSSOLVER_H

#include <vector>
using namespace std;

const size_t MAX_N =     40000 + 5;
typedef unsigned short   CordNum;
typedef vector<CordNum>  CordList;
typedef vector<bool>     BoolList;

const bool APPLY_TOP_DOWN = true;
const CordNum LIMIT =      65535;

class MPSSolver {
    public:
                            MPSSolver();
                            MPSSolver(char*);            // constructor, including read files
        void                SolveMPS();                  // sort data using insertion sort
        void                Report(char*);               // Report answer
    private:
        CordNum             N;                           // N=2n, total number of vertices on circle
        vector<CordList>    M;                           // MPS
        CordList            C;                           // Cord: C[i] = j and C[j] = i
        vector<BoolList>    Record_C;                    // Record

        inline void         Backward(CordNum, CordNum, CordList&); // Backward to get selected cords
        inline CordNum      TopDownDP(CordNum, CordNum);
};

#endif
