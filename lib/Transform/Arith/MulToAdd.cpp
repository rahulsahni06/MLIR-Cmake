#include "MulToAdd.h"
#include "mlir/Pass/Pass.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Dialect/Arith/IR/Arith.h"

namespace mlir {
namespace tutorial {

using arith::AddIOp;
using arith::ConstantOp;
using arith::MulIOp;

// Replace y = C*x with y = C/2*x + C/2*x, when C is a power of 2, otherwise do
// nothing.
struct PowerOfTwoExpand :
  public OpRewritePattern<MulIOp> {
  PowerOfTwoExpand(mlir::MLIRContext *context)
      : OpRewritePattern<MulIOp>(context, /*benefit=*/2) {}

  LogicalResult matchAndRewrite(MulIOp op,
                                PatternRewriter &rewriter) const override {
    Value lhs = op.getOperand(0);

    // canonicalization patterns ensure the constant is on the right, if there is a constant
    // See https://mlir.llvm.org/docs/Canonicalization/#globally-applied-rules
    Value rhs = op.getOperand(1);

    //Check the operation type of rhs, in this case it should be a constant
    auto rhsDefiningOp = rhs.getDefiningOp<arith::ConstantIntOp>();

    if (!rhsDefiningOp) {
      return failure();
    }

    int64_t value = rhsDefiningOp.value();

    //Check if value is power of two
    if(!((value & (value - 1)) == 0)) {
        return failure();
    }

    ConstantOp newConstant = rewriter.create<ConstantOp>(
        rhsDefiningOp.getLoc(), rewriter.getIntegerAttr(rhs.getType(), value / 2));
    MulIOp newMul = rewriter.create<MulIOp>(op.getLoc(), lhs, newConstant);
    AddIOp newAdd = rewriter.create<AddIOp>(op.getLoc(), newMul, newMul);
    rewriter.replaceOp(op, newAdd);
    return success();
  }
};

// Replace y = 9*x with y = 8*x + x
struct PeelFromMul :
  public OpRewritePattern<MulIOp> {
  PeelFromMul(mlir::MLIRContext *context)
      : OpRewritePattern<MulIOp>(context, /*benefit=*/1) {}

  LogicalResult matchAndRewrite(MulIOp op,
                                PatternRewriter &rewriter) const override {
    Value lhs = op.getOperand(0);
    Value rhs = op.getOperand(1);
    auto rhsDefiningOp = rhs.getDefiningOp<arith::ConstantIntOp>();

    if (!rhsDefiningOp) {
      return failure();
    }

    int64_t value = rhsDefiningOp.value();

    ConstantOp newConstant = rewriter.create<ConstantOp>(
        rhsDefiningOp.getLoc(), rewriter.getIntegerAttr(rhs.getType(), value - 1));
    MulIOp newMul = rewriter.create<MulIOp>(op.getLoc(), lhs, newConstant);
    AddIOp newAdd = rewriter.create<AddIOp>(op.getLoc(), newMul, lhs);
    rewriter.replaceOp(op, newAdd);
    return success();
  }
};

void MulToAddPass::runOnOperation() {
  mlir::RewritePatternSet patterns(&getContext());
  patterns.add<PowerOfTwoExpand>(&getContext());
  patterns.add<PeelFromMul>(&getContext());
  (void)applyPatternsAndFoldGreedily(getOperation(), std::move(patterns));
}

} // namespace tutorial
} // namespace mlir