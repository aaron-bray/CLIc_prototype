#include <string>
#include <vector>
#include <iostream>

#include "clesperanto.hpp"

#include <benchmark_base.cpp>

using std::string;
using std::vector;
using std::cout;

class MeanBenchmark : public BenchmarkBase
{
protected:
    cle::Clesperanto cle;
    cle::Buffer gpuInput, gpuOutput;

    virtual void Setup()
    {
        vector<float> inputData(dataWidth * dataWidth);
        vector<int> dim{{dataWidth, dataWidth, 1}};
        
        // Initialise device memory and push from host
        gpuInput = cle.Push<float>(inputData, dim.data());
        gpuOutput = cle.Create<float>(dim.data());
    }

    virtual void Iteration()
    {
        cle.MeanBox(gpuInput, gpuOutput, 4, 4);
    }

    virtual void Teardown() {}

public:
    int dataWidth;
    MeanBenchmark() : cle(cle::Clesperanto()){}
    virtual ~MeanBenchmark(){}
};

int main(int argc, char** argv) {
    MeanBenchmark d;
    d.dataWidth = 1 << 10;

    d.iterationWarmupCount = 18;

    if (argc >= 2) {
        d.dataWidth = std::stoi(argv[1]);
        cout << "using " << d.dataWidth * d.dataWidth * sizeof(float) << " bytes memory" << endl;
    }

    d.Run();

    return 0;
}
