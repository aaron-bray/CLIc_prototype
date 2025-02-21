
#include <random>

#include "clesperanto.hpp"
#include "cleCustomKernel.hpp"


/**
 * Main test function
 *
 */
int main(int argc, char **argv)
{
    int width (10), height (10), depth (10);
    int dims[3] = {width, height, depth};
    std::vector<float> input_data (width*height*depth);
    std::vector<float> valid_data (width*height*depth);
    float scalar = 100;
    std::fill(input_data.begin(), input_data.end(), 5);
    std::fill(valid_data.begin(), valid_data.end(), 5 + scalar);

    // Initialise GPU information.
    cle::Clesperanto cle;
    
    // Initialise device memory and push from host
    cle::Buffer Buffer_A = cle.Push<float>(input_data, dims);
    cle::Buffer Buffer_B = cle.Create<float>(dims);

    // Call kernel
    cle::CustomKernel kernel(cle.GetGPU(), "add_image_and_scalar_3d", {"src", "dst", "scalar"});  

    std::string dirpath = argv[1];
    std::string path = dirpath + "/add_image_and_scalar_3d_x.cl";
    kernel.SetSource(path.c_str());
    kernel.SetParameter(Buffer_A, "src");
    kernel.SetParameter(Buffer_B, "dst");
    kernel.SetParameter(scalar, "scalar");
    kernel.Execute();

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