#include "lib/Dialect/Poly/PolyDialect.h"
#include "lib/Dialect/Poly/PolyTypes.h"
#include "mlir/IR/Builders.h"

#include "lib/Dialect/Poly/PolyDialect.cpp.inc"

namespace mlir {
namespace tutorial {
namespace poly {

void PolyDialect::initialize() {
  addTypes<
#define GET_TYPEDEF_LIST
#include "lib/Dialect/Poly/PolyTypes.cpp.inc"
      >();
}

}  // namespace poly
}  // namespace tutorial
}  // namespace mlir