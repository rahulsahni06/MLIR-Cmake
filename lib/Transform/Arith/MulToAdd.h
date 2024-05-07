#ifndef LIB_TRANSFORM_ARITH_MUL_TO_ADD_H
#define LIB_TRANSFORM_ARITH_MUL_TO_ADD_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"

namespace mlir {
namespace tutorial {

#define GEN_PASS_DECL_MULTOADD
#include"lib/Transform/Arith/Passes.h.inc"

} // namespace tutorial
} // namespace mlir

#endif // LIB_TRANSFORM_ARITH_MUL_TO_ADD_H