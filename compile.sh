build_root='/Users/rahul/Projects/Library/llvm-project/build'
mlir_src_root='/Users/rahul/Projects/Library/llvm-project/mlir'

rm -r build
mkdir -p build && cd build 
cmake .. -DMLIR_DIR=${build_root}/lib/cmake/mlir -DLLVM_EXTERNAL_LIT=${build_root}/bin/llvm-lit -DMLIR_ENABLE_EXECUTION_ENGINE=1 -DLLVM_ENABLE_LLD=ON -DCMAKE_BUILD_TYPE=Release 
cmake --build . 
