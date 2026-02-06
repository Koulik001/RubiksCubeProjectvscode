#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include "header.h"
#ifndef DFSSOLVER_H
#define DFSSOLVER_H
template<typename T, typename H>
class DFSSolver{
    private:
    int max_search_depth;
    vector<RubiksCube:: MOVE> moves;
    bool dfs(int dep){
        if(rubicube.isSolved()) return true;
        if(dep > max_search_depth) return false;
        for(int i = 0; i < 18; i++){
            moves.push_back(RubiksCube:: MOVE(i));
            rubicube.move(RubiksCube:: MOVE(i));
            if(dfs(dep + 1)) return true;
            moves.pop_back();
            rubicube.invert(RubiksCube:: MOVE(i));
        }
        return false;
    }
    public:
    T rubicube;
    DFSSolver(T _rubicube, int max_dep){
        rubicube = _rubicube;
        max_search_depth = max_dep;
    }

    vector<RubiksCube:: MOVE> solve(){
        dfs(1);
        return moves;
    }

};
#endif
