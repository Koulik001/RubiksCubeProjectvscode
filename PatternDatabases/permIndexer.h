#ifndef PERMINDEXER_H
#define PERMINDEXER_H
#include "math.h"
#include <cstddef>
#include <vector>
#include <assert.h>

using namespace std;
class permutationIndexer{
    public:
        uint32_t rank(const vector<uint8_t>& perm) const{
            assert(perm.size() == 8);
            vector<uint8_t> lehmer;
            for(int i = 0; i < 8; i++){
                uint8_t a = perm[i];
                uint8_t cnt_smaller = 0;
                for(int j = i + 1; j < 8; j++){
                    if(perm[j] < a) cnt_smaller++;
                }
                lehmer.push_back(cnt_smaller);
            }

            uint32_t res = 0;
            for(int i = 0; i < 8; i++){
                res += (lehmer[i] * factorial(7 - i));
            }
            return res;
        }
};

#endif