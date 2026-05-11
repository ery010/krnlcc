#include <cuda.h>
#include <iostream>
#include <vector>

// Minimal PTX for vector addition
const char* ptx_code = R"(
.version 7.0
.target sm_80
.address_size 64

.visible .entry VecAdd(.param .u64 A, .param .u64 B, .param .u64 C, .param .u32 N) {
    .reg .pred %p1;
    .reg .f32  %f<4>;
    .reg .s32  %r<5>;
    .reg .u64  %rd<10>;

    mov.u32 %r1, %tid.x;
    mov.u32 %r2, %ntid.x;
    mov.u32 %r3, %ctaid.x;
    mad.lo.s32 %r4, %r3, %r2, %r1;

    ld.param.u32 %r0, [N];
    setp.ge.s32 %p1, %r4, %r0;
    @%p1 exit;

    mul.wide.s32 %rd1, %r4, 4;
    ld.param.u64 %rd2, [A];
    add.u64 %rd3, %rd2, %rd1;
    ld.global.f32 %f1, [%rd3];

    ld.param.u64 %rd4, [B];
    add.u64 %rd5, %rd4, %rd1;
    ld.global.f32 %f2, [%rd5];

    add.f32 %f3, %f1, %f2;

    ld.param.u64 %rd6, [C];
    add.u64 %rd7, %rd6, %rd1;
    st.global.f32 [%rd7], %f3;
    ret;
}
)";

#define CHECK_CUDA(res) if(res != CUDA_SUCCESS) { std::cerr << "CUDA Error: " << res << " at line " << __LINE__ << std::endl; return 1; }

int main() {
    int N = 1024;
    size_t size = N * sizeof(float);

    // Host data
    std::vector<float> h_A(N, 1.0f), h_B(N, 2.0f), h_C(N, 0.0f);

    // 1. Setup GPU Context
    CHECK_CUDA(cuInit(0));
    CUdevice device;
    cuDeviceGet(&device, 0);
    CUcontext context;
    cuCtxCreate(&context, 0, device);

    // 2. Load PTX
    CUmodule module;
    CHECK_CUDA(cuModuleLoadData(&module, ptx_code));
    CUfunction kernel;
    CHECK_CUDA(cuModuleGetFunction(&kernel, module, "VecAdd"));

    // 3. Allocate GPU Memory
    CUdeviceptr d_A, d_B, d_C;
    CHECK_CUDA(cuMemAlloc(&d_A, size));
    CHECK_CUDA(cuMemAlloc(&d_B, size));
    CHECK_CUDA(cuMemAlloc(&d_C, size));

    // 4. Copy data to GPU
    CHECK_CUDA(cuMemcpyHtoD(d_A, h_A.data(), size));
    CHECK_CUDA(cuMemcpyHtoD(d_B, h_B.data(), size));

    // 5. Launch Kernel
    // Arguments: [ptr_to_A, ptr_to_B, ptr_to_C, val_of_N]
    void* args[] = { &d_A, &d_B, &d_C, &N };
    
    // Launch 1 block of 1024 threads
    CHECK_CUDA(cuLaunchKernel(kernel, 
                              1, 1, 1,    // Grid dim
                              N, 1, 1,    // Block dim
                              0, nullptr, args, nullptr));

    // 6. Copy back and verify
    CHECK_CUDA(cuMemcpyDtoH(h_C.data(), d_C, size));

    std::cout << "Result of first element: " << h_C[0] << " (Expected: 3.0)" << std::endl;

    // Cleanup
    cuMemFree(d_A); cuMemFree(d_B); cuMemFree(d_C);
    cuCtxDestroy(context);
    return 0;
}

