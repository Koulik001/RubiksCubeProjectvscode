#include "bits/stdc++.h"
#include "BFSSolver.h"
#include "DFSSolver.h"
#include "header.h"
#include "RubiksCube.cpp"
#include "RubiksCube3dArray.cpp"

int main(){
    RubiksCube3dArray obj3d;
    vector<RubiksCube::MOVE> shuffle_moves =  obj3d.randomShuffle(6);
    for(auto s: shuffle_moves){
        cout<<obj3d.getMove(s)<<" ";
    }
    cout<<"\n";
    obj3d.print();
    
    if(obj3d.isSolved()) cout<<"YES SOLVED....\n";
    else cout<<"NOT SOLVED\n";
/*-------------------BFS SOLVER------------------ */
    // BFSSolver<RubiksCube3dArray, Hash3d> cubesolver(obj3d);
    // vector<RubiksCube::MOVE> solved_moves = cubesolver.solve();
    // for(auto a: solved_moves){
    //     cout<<obj3d.getMove(a)<<" ";
    // }
    // cout<<"\n";
    // cubesolver.rubicube.print();

/*-------------------DFS SOLVER------------------ */
    DFSSolver<RubiksCube3dArray, Hash3d> dfs_cubesolver(obj3d, 8);
    vector<RubiksCube::MOVE> solved_moves_dfs = dfs_cubesolver.solve();
    for(auto a: solved_moves_dfs){
        cout<<obj3d.getMove(a)<<" ";
    }
    cout<<"\n";
    dfs_cubesolver.rubicube.print();

/*-------------- Basic Testing-------------*/
    // obj3d.move(RubiksCube:: MOVE:: L);
    // obj3d.move(RubiksCube:: MOVE:: U2);
    // obj3d.move(RubiksCube:: MOVE:: D2);

    // obj3d.print();
    // cout<<"\n";
    // obj3d.move(RubiksCube:: MOVE:: D2);
    // obj3d.move(RubiksCube:: MOVE:: U);
    // obj3d.move(RubiksCube:: MOVE:: U);
    // obj3d.move(RubiksCube:: MOVE:: LPRIME);
    // obj3d.print();
    // cout<<"\n";
}
