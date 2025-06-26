#include "bits/stdc++.h"
#include "header.h"
#ifndef BFSSOLVER_H
#define BFSSOLVER_H
template<typename T, typename H>
class BFSSolver{
    private:
        vector<RubiksCube::MOVE> moves;
        unordered_map<T, bool, H> is_visited;
        unordered_map<T, RubiksCube::MOVE, H> move_done_to_reach;

        T bfs(){
            queue<T> q;
            q.push(rubicube);
            is_visited[rubicube] = true;

            while(!q.empty()){
                T cur_cube = q.front();
                q.pop();
                if(cur_cube.isSolved()){
                    return cur_cube;
                }
                for(int i = 0; i < 18; i++){
                    auto cur_move = RubiksCube::MOVE(i);
                    cur_cube.move(cur_move);
                    if(!is_visited[cur_cube]){
                        is_visited[cur_cube] = true;
                        move_done_to_reach[cur_cube] = cur_move;
                        q.push(cur_cube);
                    }
                    cur_cube.invert(cur_move);
                }
            }
            return rubicube;
        }

    public:
        T rubicube;
        BFSSolver(T _rubicube){
            rubicube = _rubicube;
        }

        vector<RubiksCube::MOVE> solve(){
            T solved_cube = bfs();
            assert(solved_cube.isSolved());

            T temp_cube = solved_cube;
            while(temp_cube != rubicube){
                RubiksCube::MOVE cur_move = move_done_to_reach[temp_cube];
                moves.push_back(cur_move);
                temp_cube.invert(cur_move);
            }
            rubicube = solved_cube;
            reverse(moves.begin(), moves.end());
            return moves;
        }
};

#endif