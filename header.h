#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

class RubiksCube{
    public:
        enum class FACE{
            UP,
            LEFT,
            FRONT,
            RIGHT,
            BACK,
            DOWN
        };

        enum class COLOR{
            WHITE,
            GREEN,
            RED,
            BLUE,
            ORANGE,
            YELLOW
        };

        enum class MOVE{
            U, UPRIME, U2,
            L, LPRIME, L2,
            F, FPRIME, F2,
            R, RPRIME, R2,
            B, BPRIME, B2,
            D, DPRIME, D2
        };
    public:
        virtual COLOR getColor(FACE f, int row, int col) const = 0;
        static char getColorLetter(COLOR c);

        string getMove(MOVE m);

        virtual bool isSolved() const = 0;
        void print() const;

        vector<MOVE> randomShuffle(int times);
        RubiksCube& move(MOVE m);
        RubiksCube& invert(MOVE m);

        virtual RubiksCube& u() = 0;
        virtual RubiksCube& uprime() = 0;
        virtual RubiksCube& u2() = 0;

        virtual RubiksCube& l() = 0;
        virtual RubiksCube& lprime() = 0;
        virtual RubiksCube& l2() = 0;
        
        virtual RubiksCube& f() = 0;
        virtual RubiksCube& fprime() = 0;
        virtual RubiksCube& f2() = 0;

        virtual RubiksCube& r() = 0;
        virtual RubiksCube& rprime() = 0;
        virtual RubiksCube& r2() = 0;

        virtual RubiksCube& b() = 0;
        virtual RubiksCube& bprime() = 0;
        virtual RubiksCube& b2() = 0;

        virtual RubiksCube& d() = 0;
        virtual RubiksCube& dprime() = 0;
        virtual RubiksCube& d2() = 0;
};

#endif