#include <iostream>
#include <cuda_runtime.h>
#include <Kokkos_Core.hpp>


// CUDA 核函数，用于向量加法
__global__ void vectorAdd(int *a, int *b, int *c, int n) {
    // 计算当前线程的全局索引
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    
    // 确保线程索引在有效范围内
    if (tid < n) {
        c[tid] = a[tid] + b[tid];
    }
}

int hello(int argc, char* argv[]) {


    Kokkos::initialize(argc, argv);

    std::cout << "##########################\n";
    std::cout << "KOKKOS CONFIG             \n";
    std::cout << "##########################\n";
    std::ostringstream msg;
    std::cout << "Kokkos configuration" << std::endl;
    Kokkos::print_configuration(msg);
    std::cout << msg.str();
    std::cout << "##########################\n";

    Kokkos::finalize();


    cudaSetDevice(1);
    int n = 100000;  // 向量大小
    int *h_a, *h_b, *h_c;  // 主机上的向量
    int *d_a, *d_b, *d_c;  // 设备（GPU）上的向量
    int size = n * sizeof(int);
    
    // 分配主机内存
    h_a = (int*)malloc(size);
    h_b = (int*)malloc(size);
    h_c = (int*)malloc(size);
    
    // 初始化 h_a 和 h_b
    for (int i = 0; i < n; ++i) {
        h_a[i] = i;
        h_b[i] = 2 * i;
    }
    
    // 分配设备内存
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);
    
    // 将数据从主机内存复制到设备内存
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);
    
    // 定义 CUDA 核函数调用的网格和块大小
    int blockSize = 256;
    int numBlocks = (n + blockSize - 1) / blockSize;
    
    // 调用 CUDA 核函数
    vectorAdd<<<numBlocks, blockSize>>>(d_a, d_b, d_c, n);
    
    // 将结果从设备内存复制回主机内存
    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);
    
    // 打印部分结果
    for (int i = 0; i < 10; ++i) {
        printf("%d + %d = %d\n", h_a[i], h_b[i], h_c[i]);
    }
    
    // 释放内存
    free(h_a);
    free(h_b);
    free(h_c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    
    return 0;
}
