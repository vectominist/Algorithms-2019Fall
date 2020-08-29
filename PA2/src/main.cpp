#include <iostream>

#include "MPSSolver.h"
#include "../lib/tm_usage.h"

using namespace std;

inline void help_msg(){
    cerr << "usage: mps <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[]){
    ios::sync_with_stdio(false);
    cin.tie(0);

    if(argc != 3){
        help_msg();
        return 0;
    }

    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    tmusg.periodStart();
    
    MPSSolver MySolver(argv[1]);
    MySolver.SolveMPS();
    MySolver.Report(argv[2]);

    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    return 0;
}