#ifndef LIB_TRANSFORM_ARITH_MUL_TO_ADD_H
#define LIB_TRANSFORM_ARITH_MUL_TO_ADD_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"

namespace mlir {
namespace tutorial {

class MulToAddPass
    : public PassWrapper<MulToAddPass,
                         OperationPass<mlir::func::FuncOp>> {
private:
  void runOnOperation() override;

  StringRef getArgument() const final { return "mul-to-add"; }

  StringRef getDescription() const final {
    return "Convert multiplications to repeated additions";
  }
};

} // namespace tutorial
} // namespace mlir

#endif // LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H_