#include <iostream>
#include <fstream>
using namespace std;

#include "CBSolver.h"
#include "tm_usage.h"

inline void help_message() {
    cerr << "usage: ./cb <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    if(argc != 3) {
       help_message();
       return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    tmusg.periodStart();

    CBSolver cbsolver(argv[1]);
    cbsolver.Solve();
    cbsolver.Report(argv[2]);

    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    return 0;
}
