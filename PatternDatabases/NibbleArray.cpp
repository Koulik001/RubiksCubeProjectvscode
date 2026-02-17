#include "NibbleArray.h"

NibbleArray::NibbleArray(size_t sz, const uint8_t val){  // FIXED: Removed default value (should only be in header)
    size = sz;
    arr.assign(sz / 2 + 1, val);
}

uint8_t NibbleArray::get(const size_t posi) const{
    //if even posi then extract the 4 msbs else 4 lsbs
    if(posi % 2 == 0){
        return (arr[posi/2] >> 4);
    }else return (arr[posi/2] & 0x0f);
}

void NibbleArray::set(const size_t posi, uint8_t val){
    if(posi % 2 == 0){
        arr[posi/2] = (arr[posi/2] & 0x0f) | (val << 4);
    }else{
        arr[posi/2] = (arr[posi/2] & 0xf0) | (val & 0x0f);
    }
}

uint8_t* NibbleArray::data() {
    return this->arr.data();
}

const uint8_t* NibbleArray::data() const {
    return this->arr.data();
}

size_t NibbleArray::getStorageSize() const{
    return this->arr.size();
}