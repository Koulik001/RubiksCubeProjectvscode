#ifndef CORNERDBMAKER_H
#define CORNERDBMAKER_H

#include "CornerPatternDB.h"
#include "../RubiksCube3dArray.cpp"

class CornerDBMaker{
    string file_name;
    CornerPatternDB cdb;

public:
    CornerDBMaker(const string& fname);
    bool bfsAndStore();
};

#endif