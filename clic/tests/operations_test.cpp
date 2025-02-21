
#include <random>
#include <vector>
#include <iostream>

#include "clesperanto.hpp"
#include "cleOperations.hpp"


/**
 * Main test function
 *
 */
int main(int argc, char **argv)
{
    unsigned int width (10), height (10), depth (10);
    std::vector<float> input_data (width*height*depth);
    std::vector<float> valid_data (width*height*depth);
    std::vector<float> ouput_data (width*height*depth);

    std::default_random_engine generator;
    std::normal_distribution<float> distribution(5.0,2.0);
    for (size_t i = 0; i < input_data.size(); i++)
    {
        input_data[i] = distribution(generator);
        valid_data[i] = input_data[i];
    }

    cle::Clesperanto cle;
    cl::Buffer input_buffer = cle::CreateBuffer<float>(input_data.size(), cle.GetGPU());
    cl::Buffer copy_buffer = cle::CreateBuffer<float>(input_data.size(), cle.GetGPU());
    cle::WriteBuffer<float>(input_buffer, input_data.data(), input_data.size(), cle.GetGPU());  
    cle::CopyBuffer<float>(input_buffer, copy_buffer, input_data.size(), cle.GetGPU()); 
    cle::ReadBuffer<float>(copy_buffer, ouput_data.data(), input_data.size(), cle.GetGPU());

    float difference = 0;
    for (size_t i = 0; i < width*height*depth; i++)
    {
        difference += std::abs(valid_data[i] - ouput_data[i]);
    }
return difference > std::numeric_limits<float>::epsilon();
}