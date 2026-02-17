#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include "BFSSolver.h"
#include "DFSSolver.h"
#include "IDDFSSolver.h"
#include "IDASTARSolver.h"
#include "header.h"
#include <assert.h>

// Include all implementation files
#include "RubiksCube.cpp"
#include "RubiksCube3dArray.cpp" 
#include "RubiksCube1dArray.cpp"

// Include Pattern Database implementations
#include "PatternDatabases/math.cpp"
#include "PatternDatabases/NibbleArray.cpp"
#include "PatternDatabases/CornerPatternDB.cpp"
#include "PatternDatabases/CornerDBMaker.cpp"

int main(){
    RubiksCube3dArray obj3d;
    //obj3d.move(RubiksCube::MOVE::U2);
    vector<RubiksCube::MOVE> shuffle_moves =  obj3d.randomShuffle(13);
    for(auto s: shuffle_moves){
        cout<<obj3d.getMove(s)<<" ";
    }
    cout<<"\n";
    obj3d.print();
    
    // if(obj3d.isSolved()) cout<<"YES SOLVED....\n";
    // else cout<<"NOT SOLVED\n";
/*-------------------BFS SOLVER------------------ */
    // BFSSolver<RubiksCube3dArray, Hash3d> cubesolver(obj3d);
    // vector<RubiksCube::MOVE> solved_moves = cubesolver.solve();
    // for(auto a: solved_moves){
    //     cout<<obj3d.getMove(a)<<" ";
    // }
    // cout<<"\n";
    // cubesolver.rubicube.print();

/*-------------------DFS SOLVER------------------ */
    // DFSSolver<RubiksCube3dArray, Hash3d> dfs_cubesolver(obj3d, 8);
    // vector<RubiksCube::MOVE> solved_moves_dfs = dfs_cubesolver.solve();
    // for(auto a: solved_moves_dfs){
    //     cout<<obj3d.getMove(a)<<" ";
    // }
    // cout<<"\n";
    // dfs_cubesolver.rubicube.print();

/*--------------- IDDFS SOLVER -------------------*/

    // IDDFSSolver<RubiksCube3dArray, Hash3d> iddfsSolver(obj3d);
    // vector<RubiksCube:: MOVE> solved_moves_iddfs = iddfsSolver.solve();
    // for(auto a: solved_moves_iddfs){
    //     cout<<obj3d.getMove(a)<<" ";
    // }
    // cout<<"\n";
    // iddfsSolver.rubikscube.print();

/*-------------- Basic Testing-------------*/
    // obj3d.move(RubiksCube:: MOVE:: BPRIME);
    // obj3d.move(RubiksCube:: MOVE:: BPRIME);
    // obj3d.move(RubiksCube:: MOVE:: LPRIME);
    // obj3d.move(RubiksCube:: MOVE:: F);
    // obj3d.move(RubiksCube:: MOVE:: L2);
    // obj3d.move(RubiksCube:: MOVE:: R);

    // obj3d.print();
    // cout<<"\n";
    // obj3d.move(RubiksCube:: MOVE:: L2);
    // obj3d.move(RubiksCube:: MOVE:: RPRIME);
    // obj3d.move(RubiksCube:: MOVE:: FPRIME);
    // obj3d.move(RubiksCube:: MOVE:: L);
    // obj3d.move(RubiksCube:: MOVE:: B2);
    // obj3d.print();
    // cout<<"\n";
/*------Test for 1d Array rep of cube*/
    // RubiksCube1dArray obj1d;
    // vector<RubiksCube::MOVE> shuffle_moves = obj1d.randomShuffle(8);
    // for(auto m: shuffle_moves){
    //     cout<<obj1d.getMove(m)<<" ";
    // } 
    // cout<<"\n";
    // obj1d.print();
    // if(!obj1d.isSolved()) cout<<"Not solved\n";

    // DFSSolver<RubiksCube1dArray, Hash1d> dfs_cubesolver(obj1d, 8);
    // vector<RubiksCube::MOVE> solved_moves_dfs = dfs_cubesolver.solve();
    // for(auto a: solved_moves_dfs){
    //     cout<<obj1d.getMove(a)<<" ";
    // }
    // cout<<"\n";
    // dfs_cubesolver.rubicube.print();

    // IDDFSSolver<RubiksCube1dArray, Hash1d> iddfsSolver(obj1d);
    // vector<RubiksCube:: MOVE> solved_moves_iddfs = iddfsSolver.solve();
    // for(auto a: solved_moves_iddfs){
    //     cout<<obj1d.getMove(a)<<" ";
    // }
    // cout<<"\n";
    // iddfsSolver.rubikscube.print();


    //SETTING UP CORNER PATTERN DATABASE...(Only 1 time)
    string fname = "cornerDatabase.txt";
    // CornerDBMaker cdbmaker(fname);
    // bool ret = cdbmaker.bfsAndStore();
    // assert(ret == true);
    // cout<<"done!!!\n";
    //FOR IDASTAR SOLVER
    IDASTARSolver<RubiksCube3dArray, Hash3d> idastarSolver(obj3d, fname);
    auto moves = idastarSolver.solve();
    for(auto mv: moves){
        cout<<obj3d.getMove(mv)<<" ";
    }
    // cout<<"\n";
    // CornerPatternDB cpdb;
    // bool res = cpdb.fromFile(fname);
    // cout<<cpdb.getNumItems()<<endl;
    // if(!res){
    //     cout<<"db error!\n";
    //     return 0;
    // }
    // cout<<cpdb.getDBIndex(obj3d)<<endl;;
    // cout<<(int)cpdb.getNumMoves(obj3d)<<endl;
    return 0;
}