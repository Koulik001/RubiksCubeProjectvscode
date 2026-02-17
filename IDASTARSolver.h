#ifndef IDASTARSOLVER_H
#define IDASTARSOLVER_H
#include "header.h"
#include "PatternDatabases/CornerPatternDB.h"
#include "assert.h"
template<typename T, typename H>
class IDASTARSolver{
    CornerPatternDB cpdb;
    vector<RubiksCube::MOVE> moves;
    unordered_map<T, RubiksCube::MOVE, H> moves_done_to_reach;
    unordered_map<T, bool, H> visited;
    // Node represents a search state in the state space
    struct Node{
        T cube;
        int depth;
        int heuristic;

        Node(T _cube, int _depth, int _h) : cube(_cube), depth(_depth), heuristic(_h) {};
    };

    struct compareCube{
        bool operator()(const pair<Node, int>& a, const pair<Node, int>& b) const{
            int f1 = a.first.depth + a.first.heuristic;
            int f2 = b.first.depth + b.first.heuristic;

            if(f1 != f2) return f1 > f2;
            else return a.first.heuristic > b.first.heuristic;
        }
    };
    

    pair<T, int> IDASTAR(int bound){
        priority_queue<pair<Node, int>, vector<pair<Node, int>>, compareCube> pq;
        Node init_state(rubikscube, 0, cpdb.getNumMoves(rubikscube));
        pq.push({init_state, 0});
        int next_bound = 100;
        while(!pq.empty()){
            auto p = pq.top();
            pq.pop();
            Node cur_st = p.first;
            //auto cur_move = p.second;
            if(visited[cur_st.cube]) continue;
            
            visited[cur_st.cube] = 1;           
            moves_done_to_reach[cur_st.cube] = RubiksCube::MOVE(p.second);

            if(cur_st.cube.isSolved()){
                return {cur_st.cube, bound};
            }
            cur_st.depth++;

            for(int i = 0; i < 18; i++){
                auto cur_move = RubiksCube::MOVE(i);
                cur_st.cube.move(cur_move);
                if(!visited[cur_st.cube]){
                    cur_st.heuristic =  cpdb.getNumMoves(cur_st.cube);
                    if(cur_st.depth + cur_st.heuristic > bound){
                        next_bound = min(next_bound, cur_st.depth + cur_st.heuristic);
                    }else{
                        pq.push({cur_st, i});
                    }
                }
                cur_st.cube.invert(cur_move);
            }
        }
        return {rubikscube, next_bound};
    }

    void reset(){
        visited.clear();
        moves.clear();
        moves_done_to_reach.clear();
    }

public:
    T rubikscube;
    
    IDASTARSolver(T _cube, string file_name){
        rubikscube = _cube;
        cpdb.fromFile(file_name);
        // cout<<cpdb.getNumItems()<<endl;

        // T solved;
        // cout << "h(solved) = " << (int)cpdb.getNumMoves(solved) << endl;

        // cout << "h(initial) = " << (int)cpdb.getNumMoves(rubikscube) << endl;
        // T one_move;
        // one_move.move(RubiksCube::MOVE::U);
        // cout << "h(U) = " << (int)cpdb.getNumMoves(one_move) << " [expect 1]" << endl;

        // // Test 3: inverting that move must bring us back to 0
        // one_move.invert(RubiksCube::MOVE::U);
        // cout << "h(U then U') = " << (int)cpdb.getNumMoves(one_move) << " [expect 0]" << endl;
        
        // T two_moves;
        // two_moves.move(RubiksCube::MOVE::U);
        // two_moves.move(RubiksCube::MOVE::R);
        // cout << "h(U,R) = " << (int)cpdb.getNumMoves(two_moves) << " [expect 2]" << endl;

        // T test;
        // bool consistent = true;
        // srand(42);
        // for (int trial = 0; trial < 1000; trial++) {
        //     auto mv = RubiksCube::MOVE(rand() % 18);
        //     test.move(mv);
        //     int h_before = (int)cpdb.getNumMoves(test);
            
        //     for (int i = 0; i < 18; i++) {
        //         auto mv2 = RubiksCube::MOVE(i);
        //         test.move(mv2);
        //         int h_after = (int)cpdb.getNumMoves(test);
        //         if (h_before > h_after + 1) {
        //             cout << "INCONSISTENCY at trial " << trial 
        //                 << ": h=" << h_before << " but neighbor h=" << h_after << endl;
        //             consistent = false;
        //         }
        //         test.invert(mv2);
        //     }
        // }
        // if (consistent) cout << "Consistency check: PASSED" << endl;

        // cout << "h(scrambled) = " << (int)cpdb.getNumMoves(rubikscube) << endl;
        // cout << "=====================" << endl;

    }

    vector<RubiksCube::MOVE> solve(){
        int bound = 1;
        auto a = IDASTAR(bound);

        while(a.second != bound){
            reset();
            bound = a.second;
            a = IDASTAR(bound);
        }

        T solved_cube = a.first;
        assert(solved_cube.isSolved());
        while(!(solved_cube == rubikscube)){
            auto mv = moves_done_to_reach[solved_cube];
            solved_cube.invert(mv);
            moves.push_back(mv);
        }
        rubikscube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};

#endif