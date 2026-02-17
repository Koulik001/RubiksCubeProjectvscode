#include "permIndexer.h"
#include "CornerPatternDB.h"
#include <cstddef>
#include <fstream>
using namespace std;

CornerPatternDB::CornerPatternDB() : database(100179840), size(100179840), numItems(0) {}

CornerPatternDB::CornerPatternDB(size_t sz) : database(sz, 0xff){
    size = sz;
    numItems = 0;
}

size_t CornerPatternDB::getNumItems(){
    return this->numItems;
}

uint32_t CornerPatternDB::getDBIndex(const RubiksCube& cube) const{
    //for corner position
    vector<uint8_t> build_perm;
    for(int ind = 0; ind < 8; ind++){
        build_perm.push_back(cube.getCornerPosition(ind));
    }
    permutationIndexer pidxer;
    uint32_t rnk = pidxer.rank(build_perm);
    //for corner orientation
    vector<uint8_t> build_ori;
    for(int ind = 0; ind < 7; ind++){
        build_ori.push_back(cube.getCornerOrientation(ind));
    }
    int exp = 729;
    uint32_t orientationNum = 0;
    for(int i = 0; i < 7; i++){
        orientationNum += build_ori[i] * exp;
        exp /= 3;
    }

    return rnk * 2187 + orientationNum;
}

bool CornerPatternDB::setNumMoves(uint32_t ind, uint8_t numMoves){
    int oldMoveCnt = this->database.get(ind);
    if(oldMoveCnt == 0xf){
        ++this->numItems;
    }
    if(oldMoveCnt > numMoves){
        this->database.set(ind, numMoves);
        return true;
    }else return false;
}

bool CornerPatternDB::setNumMoves(const RubiksCube& cube, uint8_t numMoves){
    return this->setNumMoves(this->getDBIndex(cube), numMoves);
}

uint8_t CornerPatternDB::getNumMoves(uint32_t ind){
    return this->database.get(ind);
}

uint8_t CornerPatternDB::getNumMoves(const RubiksCube& cube){
    return this->database.get(this->getDBIndex(cube));
}

void CornerPatternDB::toFile(const string& file_name) const{
    ofstream writer(file_name, ios::out | ios::binary | ios::trunc);
    if(!writer.is_open()){
        cout<<"Error occurred while writing to file!!!";
        return;
    }else{
        writer.write(reinterpret_cast<const char*>(this->database.data()), this->database.getStorageSize());
        writer.close();
    }
}

bool CornerPatternDB::fromFile(const string& file_name){
    ifstream reader(file_name, ios::in | ios::ate | ios::binary);
    size_t fileSize = reader.tellg();

    if(fileSize != this->database.getStorageSize()){
        reader.close();
        throw "Database corrupt! Failed to open Reader";
    }
    reader.seekg(0, ios::beg);
    if(!reader.is_open()){
        cout<<"Error occurred while reading from file!!!";
        return false;
    }else{
        reader.read(reinterpret_cast<char*> (this->database.data()), this->database.getStorageSize());
        reader.close();
        this->numItems = this->size;
        return true;
    }
}

void CornerPatternDB::patchUnreached(){
    for(size_t i = 0; i < size; i++){
        if(this->database.get(i) == 0xF){
            this->database.set(i, 9);
        }
    }
}