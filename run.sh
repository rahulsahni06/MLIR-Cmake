build_root=/Users/rahul/Projects/MLIR_Tutorial/mlir-tutorial-cmake/build

${build_root}/bin/tutorial-opt --affine-full-unroll $1

# ./run.sh ./test_files/ctlz.mlir