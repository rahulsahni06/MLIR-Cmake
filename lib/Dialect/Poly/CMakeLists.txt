#  This generates the correct rules to run mlir-tblgen, 
#along with a ‘MLIRPolyOpsIncGen’ target which can be used to declare dependencies.
# add_mlir_dialect(PolyDialect poly) #

# NOTE: add_mlir_dialect() expects Ops.td to be defined 



# Use this if not using Ops.td
# .td file used here should include all of the newly defined .td files.
# eg, In PolyTypes.td we have added include "PolyDialect.td"
set(LLVM_TARGET_DEFINITIONS PolyTypes.td)


# mlir_tablegen(PolyOps.h.inc -gen-op-decls)
# mlir_tablegen(PolyOps.cpp.inc -gen-op-defs)
mlir_tablegen(PolyTypes.h.inc -gen-typedef-decls -typedefs-dialect=poly)
mlir_tablegen(PolyTypes.cpp.inc -gen-typedef-defs -typedefs-dialect=poly)
mlir_tablegen(PolyDialect.h.inc -gen-dialect-decls -dialect=poly)
mlir_tablegen(PolyDialect.cpp.inc -gen-dialect-defs -dialect=poly)
add_public_tablegen_target(MLIRPolyOpsIncGen)
add_dependencies(mlir-headers MLIRPolyOpsIncGen)


add_mlir_doc(PolyDialect PolyDialect Poly/ -gen-dialect-doc)   

add_mlir_dialect_library(MLIRPoly
    PolyDialect.cpp
    PolyType.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/lib/Dialect/Poly

    DEPENDS
    MLIRPolyOpsIncGen

    LINK_LIBS PUBLIC

    )
