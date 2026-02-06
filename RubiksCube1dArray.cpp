#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include "header.h"

class RubiksCube1dArray: public RubiksCube{
    private:
        static inline int getIndex(int f, int r, int c){
            return f * 9 + r * 3 + c;
        }
        void rotateFace(int ind){
            char temp[9];
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    int idx = getIndex(ind, i, j);
                    temp[i * 3 + j] = cube[idx];
                }
            }

            for(int i = 0; i < 3; i++){
                cube[getIndex(ind, 0, i)] = temp[getIndex(0, 2 - i, 0)];
            }
            for(int i = 0; i < 3; i++){
                cube[getIndex(ind, i, 2)] = temp[getIndex(0, 0, i)];
            }
            for(int i = 0; i < 3; i++){
                cube[getIndex(ind, 2, 2 - i)] = temp[getIndex(0, i, 2)];
            }
            for(int i = 0; i < 3; i++){
                cube[getIndex(ind, 2 - i, 0)] = temp[getIndex(0, 2, 2 - i)];
            }
        }
    public:
        char cube[54];
        RubiksCube1dArray(){
            for(int i = 0; i < 6; i++){
                char col = RubiksCube::getColorLetter(COLOR(i));
                for(int j = 0; j < 3; j++){
                    for(int k = 0; k < 3; k++){
                        int idx = i * 9 + j * 3 + k;
                        cube[idx] = col;
                    }
                }
            }
        }

        COLOR getColor(FACE f, int row, int col) const override{
            int idx = getIndex((int)f, row, col);
            char colour = cube[idx];
            switch (colour)
            {
            case 'B':
                return COLOR::BLUE;
            case 'R':
                return COLOR::RED;
            case 'G':
                return COLOR::GREEN;
            case 'O':
                return COLOR::ORANGE;
            case 'Y':
                return COLOR::YELLOW;
            default:
                return COLOR::WHITE;
            }
        }

        bool isSolved() const override{
            for(int i = 0; i < 6; i++){
                char solved_col = getColorLetter(COLOR(i));
                for(int j = 0; j < 3; j++){
                    for(int k = 0; k < 3; k++){
                        int idx = i * 9 + j * 3 + k;
                        if(this->cube[idx] == solved_col) continue;
                        return false;
                    }
                }
            }
            return true;
        }

        RubiksCube &u() override{
            this->rotateFace(0);
            char temp[3];
            for(int i = 0; i < 3; i++) temp[i] = cube[getIndex(4, 0, 2 - i)];
            
            for(int i = 0; i < 3; i++) cube[getIndex(4, 0, 2 - i)] = cube[getIndex(1, 0, 2 - i)];
            for(int i = 0; i < 3; i++) cube[getIndex(1, 0, 2 - i)] = cube[getIndex(2, 0, 2 - i)];
            for(int i = 0; i < 3; i++) cube[getIndex(2, 0, 2 - i)] = cube[getIndex(3, 0, 2 - i)];
            for(int i = 0; i < 3; i++) cube[getIndex(3, 0, 2 - i)] = temp[i];
    
            return (*this);
        }

        RubiksCube &uprime() override{
            this->u();
            this->u();
            this->u();

            return *this;
        }

        RubiksCube& u2() override{
            this->u();
            this->u();

            return *this;
        }

        RubiksCube &l() override {
            this->rotateFace(1);

            char temp_arr[3];
            for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(0, i, 0)];
            for (int i = 0; i < 3; i++) cube[getIndex(0, i, 0)] = cube[getIndex(4, 2 - i, 2)];
            for (int i = 0; i < 3; i++) cube[getIndex(4, 2 - i, 2)] = cube[getIndex(5, i, 0)];
            for (int i = 0; i < 3; i++) cube[getIndex(5, i, 0)] = cube[getIndex(2, i, 0)];
            for (int i = 0; i < 3; i++) cube[getIndex(2, i, 0)] = temp_arr[i];

            return *this;
        }

        RubiksCube &lprime() override {
            this->l();
            this->l();
            this->l();

            return *this;
        }

        RubiksCube &l2() override {
            this->l();
            this->l();

            return *this;
        }

        RubiksCube &f() override {
            this->rotateFace(2);

            char temp_arr[3] = {};
            for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(0, 2, i)];
            for (int i = 0; i < 3; i++) cube[getIndex(0, 2, i)] = cube[getIndex(1, 2 - i, 2)];
            for (int i = 0; i < 3; i++) cube[getIndex(1, 2 - i, 2)] = cube[getIndex(5, 0, 2 - i)];
            for (int i = 0; i < 3; i++) cube[getIndex(5, 0, 2 - i)] = cube[getIndex(3, i, 0)];
            for (int i = 0; i < 3; i++) cube[getIndex(3, i, 0)] = temp_arr[i];

            return *this;
        }

        RubiksCube &fprime() override {
            this->f();
            this->f();
            this->f();

            return *this;
        }

        RubiksCube &f2() override {
            this->f();
            this->f();

            return *this;
        }
        
        RubiksCube &r() override {
            this->rotateFace(3);

            char temp_arr[3] = {};
            for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(0, 2 - i, 2)];
            for (int i = 0; i < 3; i++) cube[getIndex(0, 2 - i, 2)] = cube[getIndex(2, 2 - i, 2)];
            for (int i = 0; i < 3; i++) cube[getIndex(2, 2 - i, 2)] = cube[getIndex(5, 2 - i, 2)];
            for (int i = 0; i < 3; i++) cube[getIndex(5, 2 - i, 2)] = cube[getIndex(4, i, 0)];
            for (int i = 0; i < 3; i++) cube[getIndex(4, i, 0)] = temp_arr[i];

            return *this;
        }

        RubiksCube &rprime() override {
            this->r();
            this->r();
            this->r();

            return *this;
        }

        RubiksCube &r2() override {
            this->r();
            this->r();

            return *this;
        }

        RubiksCube &b() override {
            this->rotateFace(4);

            char temp_arr[3] = {};
            for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(0, 0, 2 - i)];
            for (int i = 0; i < 3; i++) cube[getIndex(0, 0, 2 - i)] = cube[getIndex(3, 2 - i, 2)];
            for (int i = 0; i < 3; i++) cube[getIndex(3, 2 - i, 2)] = cube[getIndex(5, 2, i)];
            for (int i = 0; i < 3; i++) cube[getIndex(5, 2, i)] = cube[getIndex(1, i, 0)];
            for (int i = 0; i < 3; i++) cube[getIndex(1, i, 0)] = temp_arr[i];

            return *this;
        }

        RubiksCube &bprime() override {
            this->b();
            this->b();
            this->b();

            return *this;
        }

        RubiksCube &b2() override {
            this->b();
            this->b();

            return *this;
        }

        RubiksCube &d() override {
            this->rotateFace(5);

            char temp_arr[3] = {};
            for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(2, 2, i)];
            for (int i = 0; i < 3; i++) cube[getIndex(2, 2, i)] = cube[getIndex(1, 2, i)];
            for (int i = 0; i < 3; i++) cube[getIndex(1, 2, i)] = cube[getIndex(4, 2, i)];
            for (int i = 0; i < 3; i++) cube[getIndex(4, 2, i)] = cube[getIndex(3, 2, i)];
            for (int i = 0; i < 3; i++) cube[getIndex(3, 2, i)] = temp_arr[i];

            return *this;
        }

        RubiksCube &dprime() override {
            this->d();
            this->d();
            this->d();

            return *this;
        }

        RubiksCube &d2() override {
            this->d();
            this->d();

            return *this;
        }

        bool operator==(const RubiksCube1dArray& r_cube) const{
            for(int i = 0; i < 54; i++){
                if(r_cube.cube[i] != cube[i]) return false;
            }
            return true;
        }

        RubiksCube1dArray& operator=(const RubiksCube1dArray& r_cube){
            for(int i = 0; i < 54; i++){
                cube[i] = r_cube.cube[i];
            }
            return *this;
        }
};

struct Hash1d{
    size_t operator()(const RubiksCube1dArray& r1) const{
        string str = "";
        for(int i = 0; i < 54; i++) str += r1.cube[i];

        return hash<string>()(str);
    }
};