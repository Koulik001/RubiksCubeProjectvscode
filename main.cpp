#include "bits/stdc++.h"
#include "BFSSolver.h"
#include "header.h"
#include "RubiksCube.cpp"
#include "RubiksCube3dArray.cpp"

int main(){
    RubiksCube3dArray obj3d;
    vector<RubiksCube::MOVE> shuffle_moves =  obj3d.randomShuffle(3);
    for(auto s: shuffle_moves){
        cout<<obj3d.getMove(s)<<" ";
    }
    cout<<"\n";
    obj3d.print();
    
    if(obj3d.isSolved()) cout<<"YES SOLVED....\n";
    else cout<<"NOT SOLVED\n";

    BFSSolver<RubiksCube3dArray, Hash3d> cubesolver(obj3d);
    vector<RubiksCube::MOVE> solved_moves = cubesolver.solve();
    for(auto a: solved_moves){
        cout<<obj3d.getMove(a)<<" ";
    }
    cout<<"\n";
    cubesolver.rubicube.print();
}
