#include "murmur3.h"
#include <bits/stdc++.h>
using namespace std;

#define HLL_HASH_SEED 1

class HyperLogLog
{
private:
    const double CONST = 0.79402;
    uint8_t b;
    uint8_t m;
    vector<uint8_t> buckets;

    uint32_t hashFunction(int value)
    {
        uint64_t hash_otpt[2] = {0};
        MurmurHash3_x86_32(&value, sizeof(value), HLL_HASH_SEED, hash_otpt);
        return *hash_otpt;
    }

    uint8_t GetTrailingZeroes(int32_t value)
    {
        return value == 0 ? 1 : __builtin_ctz(value) + 1;
    }

public:
    HyperLogLog(uint8_t number_of_buckets)
    {
        m = number_of_buckets;
        b = ceil(log2(b));
        buckets.resize(m, 0);
    }

    void AddElement(int value)
    {
        // cout << "hashed value of " << value << ": ";
        uint32_t hash = hashFunction(value);
        // cout << hash << endl;
        uint8_t bucketIndex = (hash & (m - 1));
        // cout << "Bucket Index: " << bucketIndex << endl;
        uint8_t trailingZeroes = GetTrailingZeroes(hash >> b);
        // cout << "Consecutive Zeros: " << trailingZeroes << endl;
        buckets[bucketIndex] = max(buckets[bucketIndex], trailingZeroes);
    }

    double EstimateCardinality()
    {
        cout << "Buckets: "<<endl;;
        for (uint8_t &x : buckets)
        {
            cout << static_cast<int>(x) << " ";
        }
        cout << endl;

        double sum = 0.0;
        for (uint8_t sequenceLength : buckets)
        {
            sum += pow(2.0, -sequenceLength);
        }
        double estimate = CONST * m * m / sum;
        return estimate;
    }
};
