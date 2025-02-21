

#include "cleFlagExistingLabelsKernel.hpp"
#include "cleSetKernel.hpp"

namespace cle
{

FlagExistingLabelsKernel::FlagExistingLabelsKernel (std::shared_ptr<GPU> gpu) : 
    Kernel( gpu,
            "flag_existing_labels",
            {"dst" , "src"}
    )
{
    m_Sources.insert({this->m_KernelName + "", source});
}    

void FlagExistingLabelsKernel::SetInput(Buffer& x)
{
    this->AddObject(x, "src");
}

void FlagExistingLabelsKernel::SetOutput(Buffer& x)
{
    this->AddObject(x, "dst");
}

void FlagExistingLabelsKernel::Execute()
{
    std::shared_ptr<Buffer> dst = std::dynamic_pointer_cast<Buffer>(m_ParameterList.at("dst"));
    SetKernel set(this->m_gpu);
    set.SetInput(*dst);
    set.SetValue(0);
    set.Execute();

    this->BuildProgramKernel();
    this->SetArguments();
    this->EnqueueKernel();
}

} // namespace cle
