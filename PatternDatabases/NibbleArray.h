#ifndef NIBBLEARRAY_H
#define NIBBLEARRAY_H
#include <cstddef>
#include <vector>
#include <cstdint>
using namespace std;

class NibbleArray{
    size_t size;
    vector<uint8_t> arr;
public:
    NibbleArray(size_t sz, const uint8_t val = 0xff);
    uint8_t get(const size_t posi) const;
    void set(const size_t pos, uint8_t val);
    uint8_t* data();
    const uint8_t* data() const;
    size_t getStorageSize() const;
};

#endif