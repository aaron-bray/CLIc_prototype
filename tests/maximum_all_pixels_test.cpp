
#include <random>
#include <iostream>

#include "clesperanto.hpp"

/**
 * Main test function
 *
 */
int main(int argc, char **argv)
{
    // Initialise random input and valid output.
    int width (10), height (10), depth (10);
    int dim[3] = {width, height, depth};

    std::vector<float> input_data (width*height*depth);
    std::vector<float> valid_data (1);
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(5.0,2.0);
    for (size_t i = 0; i < width*height*depth; i++)
    {
        input_data[i] = distribution(generator);
    }
    input_data[50] = 1000;
    valid_data[0] = 1000;

    // Initialise GPU information.
    cle::Clesperanto cle;

    cle::Buffer Buffer_A = cle.Push<float>(input_data, dim);
    cle::Buffer Buffer_B = cle.Create<float>(dim);

    // Call kernel
    cle.MaximumOfAllPixels(Buffer_A, Buffer_B);   

    // pull device memory to host
    std::vector<float> ouput_data = cle.Pull<float>(Buffer_B);

    // Verify output
    float difference = std::abs(valid_data[0] - ouput_data[0]); 
    return difference > std::numeric_limits<float>::epsilon();
}
