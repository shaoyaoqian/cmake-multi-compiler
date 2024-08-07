. ~/spack/share/spack/setup-env.sh
spack load gcc@11.4.0
spack env activate -p kokkos_fenics
spack load cmake

export SPACK_VIEW=~/spack/var/spack/environments/kokkos_fenics/.spack-env/view
export SPACK_CXX=$SPACK_VIEW/bin/nvcc_wrapper
export NPUHEART_GEOMETRY_PATH=~/geometry/

# OPENMP的环境变量
export OMP_NUM_THREADS=20
export OMP_PROC_BIND=spread OMP_PLACES=threads

# CUDA的环境变量(Kokkos使用)
export CUDA_VISIBLE_DEVICES=0