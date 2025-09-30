#include "bits/stdc++.h"
#include "DFSSolver.h"
#include "header.h"
#ifndef IDDFSSOLVER_H
#define IDDFSSOLVER_H
template<typename T, typename H>
class IDDFSSolver{
    private:
        int max_search_dep;
        vector<RubiksCube::MOVE> moves;
    public:
        T rubikscube;
        IDDFSSolver(T rubicube, int max_allowed_moves = 7){
            rubikscube = rubicube;
            max_search_dep = max_allowed_moves;
        }
        
        vector<RubiksCube:: MOVE> solve(){
            for(int i = 1; i <= max_search_dep; i++){
                DFSSolver<T, H> dfssolver(rubikscube, i);
                moves = dfssolver.solve();
                if(dfssolver.rubicube.isSolved()){
                    rubikscube = dfssolver.rubicube;
                    break;
                }
            }
            return moves;
        }
};

#endif
