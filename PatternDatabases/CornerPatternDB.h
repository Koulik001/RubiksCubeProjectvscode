#ifndef CORNERPATTERNDB_H
#define CORNERPATTERNDB_H
#include "NibbleArray.h"
#include "../header.h"
class CornerPatternDB{
    NibbleArray database;
    size_t size;
    size_t numItems;

    
    public:
        CornerPatternDB();
        CornerPatternDB(size_t sz);
        uint32_t getDBIndex(const RubiksCube& cube) const;
        void patchUnreached();
        size_t getNumItems();

        bool setNumMoves(uint32_t ind, uint8_t numMoves);
        bool setNumMoves(const RubiksCube& cube, uint8_t numMoves);

        uint8_t getNumMoves(uint32_t ind);
        uint8_t getNumMoves(const RubiksCube& cube);

        void toFile(const string& file_name) const;
        bool fromFile(const string& file_name);
};

#endif