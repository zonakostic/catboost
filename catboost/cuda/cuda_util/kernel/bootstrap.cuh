#pragma once

#include <catboost/cuda/cuda_lib/kernel/kernel.cuh>

namespace NKernel {

void PoissonBootstrap(const float lambda, ui64* seeds, uint seedsSize, float* weights, ui32 size, TCudaStream stream);
void UniformBootstrap(const float sampleRate, ui64* seeds, uint seedSize, float* weights, ui32 size, TCudaStream stream);
void BayesianBootstrap(ui64* seeds, uint seedSize, float* weights, ui32 size, float temperature, TCudaStream stream);

} //namespace NKernel
