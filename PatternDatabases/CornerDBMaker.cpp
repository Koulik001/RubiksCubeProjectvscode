#include "CornerDBMaker.h"
using namespace std;

CornerDBMaker::CornerDBMaker(const string& fname) : cdb(100179840){
    this->file_name = fname;
}

bool CornerDBMaker::bfsAndStore(){
    RubiksCube3dArray r3cube;
    queue<RubiksCube3dArray> q;
    q.push(r3cube);
    cdb.setNumMoves(r3cube, 0);
    int cur_depth = 0;
    while(!q.empty()){
        cur_depth++;
        if(cur_depth == 9) break;
        int sz = q.size();
        while(sz--){
            auto cur_cube = q.front();
            q.pop();
            for(int i = 0; i < 18; i++){
                auto cur_move = RubiksCube::MOVE(i);
                cur_cube.move(cur_move);
                if(cdb.getNumMoves(cur_cube) > cur_depth){
                    cdb.setNumMoves(cur_cube, cur_depth);
                    q.push(cur_cube);
                }
                cur_cube.invert(cur_move);
            }
        }
    }

    cdb.patchUnreached();

    cdb.toFile(file_name);
    return true;
}