#include "header.h"

class RubiksCube3dArray: public RubiksCube{
    public:
        char cube[6][3][3];
        void rotateFace(int ind){
            char temp[3][3];
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    temp[i][j] = cube[ind][i][j];
                }
            }

            for(int i = 0; i < 3; i++){
                cube[ind][i][2] = temp[0][i];  
            }

            for(int i = 0; i < 3; i++){
                cube[ind][2][i] = temp[2 - i][2];
            }

            for(int i = 0; i < 3; i++){
                cube[ind][i][0] = temp[2][i];
            }

            for(int i = 0; i < 3; i++){
                cube[ind][0][i] = temp[2 - i][0];
            }
        }

        //constructor
        RubiksCube3dArray(){
            for(int i = 0; i < 6; i++){
                for(int j = 0; j < 3; j++){
                    for(int k = 0; k < 3; k++){
                        cube[i][j][k] = getColorLetter(COLOR(i));
                    }
                }
            }
        }
        COLOR getColor(FACE f, int row, int col) const override{
            char colour = cube[int(f)][row][col];
            switch(colour){
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
                for(int j = 0; j < 3; j++){
                    for(int k = 0; k < 3; k++){
                        if(cube[i][j][k] == getColorLetter(COLOR(i))) continue;
                        else return false;
                    }
                }
            }
            return true;
        }

        RubiksCube& u() override{
            this->rotateFace(0);
            char temp[3] = {};
            for(int i = 0; i < 3; i++){
                temp[i] = cube[4][0][2 - i];
            }
            for(int i = 0; i < 3; i++) cube[4][0][2 - i] = cube[1][0][2 - i];
            for(int i = 0; i < 3; i++) cube[1][0][2 - i] = cube[2][0][2 - i];
            for(int i = 0; i < 3; i++) cube[2][0][2 - i] = cube[3][0][2 - i];
            for(int i = 0; i < 3; i++) cube[3][0][2 - i] = temp[i];
            return *this;
        }

        RubiksCube& uprime() override{
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

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][i][0];
        for (int i = 0; i < 3; i++) cube[0][i][0] = cube[4][2 - i][2];
        for (int i = 0; i < 3; i++) cube[4][2 - i][2] = cube[5][i][0];
        for (int i = 0; i < 3; i++) cube[5][i][0] = cube[2][i][0];
        for (int i = 0; i < 3; i++) cube[2][i][0] = temp_arr[i];

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
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][2][i];
        for (int i = 0; i < 3; i++) cube[0][2][i] = cube[1][2 - i][2];
        for (int i = 0; i < 3; i++) cube[1][2 - i][2] = cube[5][0][2 - i];
        for (int i = 0; i < 3; i++) cube[5][0][2 - i] = cube[3][i][0];
        for (int i = 0; i < 3; i++) cube[3][i][0] = temp_arr[i];

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
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][2 - i][2];
        for (int i = 0; i < 3; i++) cube[0][2 - i][2] = cube[2][2 - i][2];
        for (int i = 0; i < 3; i++) cube[2][2 - i][2] = cube[5][2 - i][2];
        for (int i = 0; i < 3; i++) cube[5][2 - i][2] = cube[4][i][0];
        for (int i = 0; i < 3; i++) cube[4][i][0] = temp_arr[i];

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
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[0][0][2 - i];
        for (int i = 0; i < 3; i++) cube[0][0][2 - i] = cube[3][2 - i][2];
        for (int i = 0; i < 3; i++) cube[3][2 - i][2] = cube[5][2][i];
        for (int i = 0; i < 3; i++) cube[5][2][i] = cube[1][i][0];
        for (int i = 0; i < 3; i++) cube[1][i][0] = temp_arr[i];

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
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[2][2][i];
        for (int i = 0; i < 3; i++) cube[2][2][i] = cube[1][2][i];
        for (int i = 0; i < 3; i++) cube[1][2][i] = cube[4][2][i];
        for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i];
        for (int i = 0; i < 3; i++) cube[3][2][i] = temp_arr[i];

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

        bool operator==(const RubiksCube3dArray& r) const{
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    for(int k = 0; k < 3; k++){
                        if(this->cube[i][j][k] != r.cube[i][j][k]){
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        RubiksCube3dArray& operator=(const RubiksCube3dArray& r){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    for(int k = 0; k < 3; k++){
                        cube[i][j][k] = r.cube[i][j][k];
                    }
                }
            }
            return *this; 
        }

};

struct  Hash3d
{
    size_t operator()(const RubiksCube3dArray& r) const{
        string s = "";
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    s += r.cube[i][j][k];
                }
            }
        }
        return hash<string>()(s);
    }
};
