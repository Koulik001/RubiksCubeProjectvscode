#include "header.h"
#include<string.h>
char RubiksCube::getColorLetter(COLOR c){
    switch (c)
    {
    case COLOR::WHITE:
        /* code */
        return 'W';
    case COLOR::GREEN:
        return 'G';
    case COLOR::RED:
        return 'R';
    case COLOR::BLUE:
        return 'B';
    case COLOR::ORANGE:
        return 'O';
    default:
        return 'Y';
    }
}

string RubiksCube::getMove (MOVE m){
    switch (m)
    {
    case MOVE::U:
        /* code */
        return "U";
    case MOVE::UPRIME:
        return "U'";
    case MOVE::U2:
        return "U2";
    case MOVE::L:
        return "L";
    case MOVE::LPRIME:
        return "L'";
    case MOVE::L2:
        return "L2";
    case MOVE::F:
        return "F";
    case MOVE::FPRIME:
        return "F'";
    case MOVE::F2:
        return "F2";
    case MOVE::R:
        return "R";
    case MOVE::RPRIME:
        return "R'";
    case MOVE::R2:
        return "R2";
    case MOVE::B:
        return "B";
    case MOVE::BPRIME:
        return "B'";
    case MOVE::B2:
        return "B2";
    case MOVE::D:
        return "D";
    case MOVE::DPRIME:
        return "D'";
    case MOVE::D2:
        return "D2";
    }
}

RubiksCube& RubiksCube::move(MOVE m){
    switch (m)
    {
    case MOVE::U:
        /* code */
        return this->u();
    case MOVE::UPRIME:
        return this->uprime();
    case MOVE::U2:
        return this->u2();
    
    case MOVE::L:
        return this->l();
    case MOVE::LPRIME:
        return this->lprime();
    case MOVE::L2:
        return this->l2();
    
    case MOVE::F:
        return this->f();
    case MOVE::FPRIME:
        return this->fprime();
    case MOVE::F2:
        return this->f2();
    case MOVE::R:
        return this->r();
    case MOVE::RPRIME:
        return this->rprime();
    case MOVE::R2:
        return this->r2();
    case MOVE::B:
        return this->b();
    case MOVE::BPRIME:
        return this->bprime();
    case MOVE::B2:
        return this->b2();
    case MOVE::D:
        return this->d();
    case MOVE::DPRIME:
        return this->dprime();
    case MOVE::D2:
        return this->d2();
    }
}

//invert move
RubiksCube& RubiksCube::invert(MOVE m){
    switch (m)
    {
    case MOVE::L:
        return this->lprime();
    case MOVE::LPRIME:
        return this->l();
    case MOVE::L2:
        return this->l2();
    case MOVE::R:
        return this->r();
    case MOVE::RPRIME:
        return this->rprime();
    case MOVE::R2:
        return this->r2();
    case MOVE::U:
        return this->u();
    case MOVE::UPRIME:
        return this->uprime();
    case MOVE::U2:
        return this->u2();
    case MOVE::D:
        return this->d();
    case MOVE::DPRIME:
        return this->dprime();
    case MOVE::D2:
        return this->d2();
    case MOVE::F:
        return this->f();
    case MOVE::FPRIME:
        return this->fprime();
    case MOVE::F2:
        return this->f2();
    case MOVE::B:
        return this->b();
    case MOVE::B2:
        return this->b2();
    case MOVE::BPRIME:
        return this->bprime();
    default:
        break;
    }
}

void RubiksCube::print() const{
    cout<<"Rubiks cube: \n\n";
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 7; j++) cout<<" ";
        for(int k = 0; k < 3; k++)
        cout<<getColorLetter(getColor(FACE::UP,i,k))<<" ";
        cout<<endl;
    }
    cout<<endl;
    // for(int i = 0; i < 3; i++){
    //     for(int j = 0; j < 3; j++){
    //         cout<<getColorLetter(getColor(FACE::LEFT,i,j))<<" ";
    //     }
    //     cout<<endl;
    // }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout<<getColorLetter(getColor(FACE::LEFT, i, j))<<" ";
        }
        cout<<" ";
        for(int j = 0; j < 3; j++){
            cout<<getColorLetter(getColor(FACE::FRONT, i, j))<<" ";
        }
        cout<<" ";
        for(int j = 0; j < 3; j++){
            cout<<getColorLetter(getColor(FACE::RIGHT, i, j))<<" ";
        }
        cout<<" ";
        for(int j = 0; j < 3; j++){
            cout<<getColorLetter(getColor(FACE::BACK, i, j))<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 7; j++) cout<<" ";
        for(int k = 0; k < 3; k++){
            cout<<getColorLetter(getColor(FACE::DOWN, i, k))<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

vector<RubiksCube::MOVE> RubiksCube::randomShuffle(int times){
    vector<RubiksCube::MOVE> res;
    srand(time(0));
    for(int i = 0; i < times; i++){
        int random = (rand() % 18);
        res.push_back(static_cast<MOVE>(random));
        this->move(static_cast<MOVE>(random));
    }
    return res;
}
