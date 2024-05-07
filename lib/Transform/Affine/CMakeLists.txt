# add_mlir_library(AffineFullUnroll
#     AffineFullUnroll.cpp
#     AffineFullUnrollPatternRewrite.cpp

#     ${PROJECT_SOURCE_DIR}/lib/Transform/Affine/
#     ADDITIONAL_HEADER_DIRS

#     DEPENDS
#     MLIRAffineFullUnrollPasses

#     LINK_LIBS PUBLIC
# )

# set(LLVM_TARGET_DEFINITIONS Passes.td)
# mlir_tablegen(Passes.h.inc -gen-pass-decls -name Affine)
# add_public_tablegen_target(MLIRAffineFullUnrollPasses)
# add_mlir_doc(Passes AffinePasses ./ -gen-pass-doc)



# https://mlir.llvm.org/docs/Tutorials/transform/Ch2/#setting-up-to-add-new-transformations
add_mlir_library(
    # Library called MyExtension.
    AffineFullUnroll

    # Built from the following source files.
    AffineFullUnroll.cpp
    AffineFullUnrollPatternRewrite.cpp

    # Specifies directory for other header files
    ${PROJECT_SOURCE_DIR}/lib/Transform/Affine/
    ADDITIONAL_HEADER_DIRS

    # Make sure ODS declaration and definitions are generated before compiling
    # this.
    DEPENDS
    MLIRAffineFullUnrollPasses

    # LINK_LIBS PUBLIC
    #     MLIRIR
    #     MLIRInferTypeOpInterface
        # MLIRPass
)

# Tell Tablegen to use Passes.td as input.
set(LLVM_TARGET_DEFINITIONS Passes.td)

# Ask Tablegen to generate pass declarations from Passes.td, 
#Using the gen-pass-decls generator, we can generate most of the boilerplate above automatically. 
#This generator takes as an input a -name parameter, that provides a tag for the group of passes that are being generated.
# This generator produces code with multiple purposes:
#The first is to register the declared passes with the global registry. 
#For each pass, the generator produces a registerPassName where PassName is the name of the definition specified in tablegen. 
#It also generates a registerGroupPasses, where Group is the tag provided via the -name input parameter, that registers all of the passes present.
mlir_tablegen(Passes.h.inc -gen-pass-decls -name Affine)

# Add a CMakeTarget we can depend on to ensure the generation happens before the compilation.
add_public_tablegen_target(MLIRAffineFullUnrollPasses)
# Don't forget to generate the documentation, this will produce a Passes.md under
add_mlir_doc(Passes AffinePasses ./ -gen-pass-doc)
