

#include "clesperanto.hpp"


template<class T>
bool ApplyFilter(cle::Clesperanto* cle, int dims[3], float scalar)
{
    std::vector<T> input_data (dims[0]*dims[1]*dims[2]);
    std::vector<T> valid_data (dims[0]*dims[1]*dims[2]);
    std::fill(input_data.begin(), input_data.end(), 5);
    std::fill(valid_data.begin(), valid_data.end(), 5 + scalar);

    cle::Buffer Buffer_A = cle->Push<T>(input_data, dims);
    cle::Buffer Buffer_B = cle->Create<T>(dims);

    cle->AddImageAndScalar(Buffer_A, Buffer_B, scalar);

    std::vector<T> output_data = cle->Pull<T>(Buffer_B);

    float difference = 0;
    for (size_t i = 0; i < output_data.size(); i++)
    {
        difference += std::abs((float)valid_data[i] - output_data[i]);
    }
    return difference > std::numeric_limits<float>::epsilon();
}

/**
 * Main test function
 *
 */
int main(int argc, char **argv)
{
    int width (10), height (10), depth (10);
    int dims[3] = {width, height, depth};

    cle::Clesperanto* cle = new cle::Clesperanto();

    ApplyFilter<float>(cle, dims, 5);
    // ApplyFilter<double>(cle, dims, 5);
    // ApplyFilter<int>(cle, dims, 5);
    // ApplyFilter<unsigned int>(cle, dims, 5);
    ApplyFilter<char>(cle, dims, 5);
    ApplyFilter<unsigned char>(cle, dims, 5);
    // ApplyFilter<short>(cle, dims, 5);
    // ApplyFilter<unsigned short>(cle, dims, 5);

    return EXIT_SUCCESS;
}