#include "hyperloglog.h"
using namespace std;
#define endl '\n'

const uint32_t SIZE = 1000000;
const uint32_t LOWER_BOUND = 0;
const uint32_t UPPER_BOUND = 1000000;

vector<uint64_t> generateRandomData(int8_t seed)
{
    vector<uint64_t> data(SIZE);
    mt19937 generator(seed);
    uniform_int_distribution<int> distribution(LOWER_BOUND, UPPER_BOUND - 1);
    for (uint64_t &value : data)
    {
        value = distribution(generator);
    }
    return data;
}

int main()
{
    HyperLogLog hll(64);
    int8_t seed = 17;
    vector<uint64_t> inputData = generateRandomData(seed);
    unordered_set<uint64_t> distinctElements(inputData.begin(), inputData.end());
    for (int x : inputData)
    {
        hll.AddElement(x);
    }
    int actualCardinality = distinctElements.size();
    cout << "Actual Cardinality: " << actualCardinality << endl;
    double estimatedCardinality = hll.EstimateCardinality();
    cout << "Estimated Cardinality: " << estimatedCardinality << endl;
    double percentageMissed = 100.0 - (estimatedCardinality / actualCardinality) * 100.0;
    cout << "Percentage Missed: " << percentageMissed << endl;
    return 0;
}