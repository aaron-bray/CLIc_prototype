

#ifndef __cleMinimumZProjectionKernel_hpp
#define __cleMinimumZProjectionKernel_hpp

#include "cleKernel.hpp"

namespace cle
{
    
class MinimumZProjectionKernel : public Kernel
{

private:
    std::string source = 
        #include "cle_minimum_z_projection.h" 
        ;

public:
    MinimumZProjectionKernel (std::shared_ptr<GPU>);
    void SetInput(Buffer&);
    void SetOutput(Buffer&);
    void Execute();

};

} // namespace cle

#endif // __cleMinimumZProjectionKernel_hpp
