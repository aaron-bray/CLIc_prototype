
#include <random>

#include "clesperanto.hpp"

/**
 * Main test function
 *
 */
int main(int argc, char **argv)
{
    // Initialise random input and valid output.
    int width (4), height (4), depth (1);
    int dims[3] = {width, height, depth};
    
    std::vector<float> input_data = {
                0, 0, 0, 1,
                0, 0, 3, 1,
                0, 0, 3, 1,
                1, 1, 1, 1
    };

    std::vector<float> valid_data = {
                0, 0, 0, 13,
                0, 0, 10, 14,
                0, 0, 11, 15,
                4, 8, 12, 16
    };

    // Initialise GPU information.
    cle::Clesperanto cle;

    // Initialise device memory and push from host to device
    cle::Buffer Buffer_A = cle.Push<float>(input_data, dims);
    cle::Buffer Buffer_B = cle.Create<float>(dims);

    // Call kernel
    cle.SetNonzeroPixelsToPixelindex(Buffer_A, Buffer_B);

    // pull device memory to host
    std::vector<float> output_data = cle.Pull<float>(Buffer_B);    

    // Verify output
    float difference = 0;
    for (size_t i = 0; i < output_data.size(); i++)
    {
        difference += std::abs(valid_data[i] - output_data[i]);
    }
    return difference > std::numeric_limits<float>::epsilon();
}