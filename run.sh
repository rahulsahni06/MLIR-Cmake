build_root=/Users/rahul/Projects/MLIR_Tutorial/mlir-tutorial-cmake/build

# $1: [--affine-full-unroll, --affine-full-unroll-rewrite, --mul-to-add ]
# #2: [./test_files/affine_loop_unroll.mlir, ./test_files/ctlz.mlir, ./test_files/power_2_plus_one.mlir]
${build_root}/bin/tutorial-opt $1 $2