QT       += core gui 3dcore 3drender 3dinput 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bathymetry.cpp \
    boundCond.cpp \
    buildings.cpp \
    cfdsolvers/openfoam/zerofiles.cpp \
    generateFiles.cpp \
    interfaceframe.cpp \
    server/stampede2/stampede2.cpp \
    swcfd.cpp \
    swsolvers/geoclaw/geoclaw.cpp \
    initialCon.cpp \
    initialize.cpp \
    main.cpp \
    mainwindow.cpp \
    meshing.cpp \
    cfdsolvers/openfoam/constantfiles.cpp \
    cfdsolvers/openfoam/systemfiles.cpp \
    optionStack.cpp \
    optionTree.cpp \
    projsettings.cpp \
    qt3dframe.cpp \
    scenemodifier.cpp \
    solver.cpp \
    cfdsolvers/openfoam/openfoam.cpp

HEADERS += \
    dependencies/Eigen/Cholesky \
    dependencies/Eigen/CholmodSupport \
    dependencies/Eigen/Core \
    dependencies/Eigen/Dense \
    dependencies/Eigen/Eigen \
    dependencies/Eigen/Eigenvalues \
    dependencies/Eigen/Geometry \
    dependencies/Eigen/Householder \
    dependencies/Eigen/IterativeLinearSolvers \
    dependencies/Eigen/Jacobi \
    dependencies/Eigen/LU \
    dependencies/Eigen/MetisSupport \
    dependencies/Eigen/OrderingMethods \
    dependencies/Eigen/PaStiXSupport \
    dependencies/Eigen/PardisoSupport \
    dependencies/Eigen/QR \
    dependencies/Eigen/QtAlignedMalloc \
    dependencies/Eigen/SPQRSupport \
    dependencies/Eigen/SVD \
    dependencies/Eigen/Sparse \
    dependencies/Eigen/SparseCholesky \
    dependencies/Eigen/SparseCore \
    dependencies/Eigen/SparseLU \
    dependencies/Eigen/SparseQR \
    dependencies/Eigen/StdDeque \
    dependencies/Eigen/StdList \
    dependencies/Eigen/StdVector \
    dependencies/Eigen/SuperLUSupport \
    dependencies/Eigen/UmfPackSupport \
    dependencies/Eigen/src/Cholesky/LDLT.h \
    dependencies/Eigen/src/Cholesky/LLT.h \
    dependencies/Eigen/src/Cholesky/LLT_LAPACKE.h \
    dependencies/Eigen/src/CholmodSupport/CholmodSupport.h \
    dependencies/Eigen/src/Core/Array.h \
    dependencies/Eigen/src/Core/ArrayBase.h \
    dependencies/Eigen/src/Core/ArrayWrapper.h \
    dependencies/Eigen/src/Core/Assign.h \
    dependencies/Eigen/src/Core/AssignEvaluator.h \
    dependencies/Eigen/src/Core/Assign_MKL.h \
    dependencies/Eigen/src/Core/BandMatrix.h \
    dependencies/Eigen/src/Core/Block.h \
    dependencies/Eigen/src/Core/BooleanRedux.h \
    dependencies/Eigen/src/Core/CommaInitializer.h \
    dependencies/Eigen/src/Core/ConditionEstimator.h \
    dependencies/Eigen/src/Core/CoreEvaluators.h \
    dependencies/Eigen/src/Core/CoreIterators.h \
    dependencies/Eigen/src/Core/CwiseBinaryOp.h \
    dependencies/Eigen/src/Core/CwiseNullaryOp.h \
    dependencies/Eigen/src/Core/CwiseTernaryOp.h \
    dependencies/Eigen/src/Core/CwiseUnaryOp.h \
    dependencies/Eigen/src/Core/CwiseUnaryView.h \
    dependencies/Eigen/src/Core/DenseBase.h \
    dependencies/Eigen/src/Core/DenseCoeffsBase.h \
    dependencies/Eigen/src/Core/DenseStorage.h \
    dependencies/Eigen/src/Core/Diagonal.h \
    dependencies/Eigen/src/Core/DiagonalMatrix.h \
    dependencies/Eigen/src/Core/DiagonalProduct.h \
    dependencies/Eigen/src/Core/Dot.h \
    dependencies/Eigen/src/Core/EigenBase.h \
    dependencies/Eigen/src/Core/ForceAlignedAccess.h \
    dependencies/Eigen/src/Core/Fuzzy.h \
    dependencies/Eigen/src/Core/GeneralProduct.h \
    dependencies/Eigen/src/Core/GenericPacketMath.h \
    dependencies/Eigen/src/Core/GlobalFunctions.h \
    dependencies/Eigen/src/Core/IO.h \
    dependencies/Eigen/src/Core/Inverse.h \
    dependencies/Eigen/src/Core/Map.h \
    dependencies/Eigen/src/Core/MapBase.h \
    dependencies/Eigen/src/Core/MathFunctions.h \
    dependencies/Eigen/src/Core/MathFunctionsImpl.h \
    dependencies/Eigen/src/Core/Matrix.h \
    dependencies/Eigen/src/Core/MatrixBase.h \
    dependencies/Eigen/src/Core/NestByValue.h \
    dependencies/Eigen/src/Core/NoAlias.h \
    dependencies/Eigen/src/Core/NumTraits.h \
    dependencies/Eigen/src/Core/PermutationMatrix.h \
    dependencies/Eigen/src/Core/PlainObjectBase.h \
    dependencies/Eigen/src/Core/Product.h \
    dependencies/Eigen/src/Core/ProductEvaluators.h \
    dependencies/Eigen/src/Core/Random.h \
    dependencies/Eigen/src/Core/Redux.h \
    dependencies/Eigen/src/Core/Ref.h \
    dependencies/Eigen/src/Core/Replicate.h \
    dependencies/Eigen/src/Core/ReturnByValue.h \
    dependencies/Eigen/src/Core/Reverse.h \
    dependencies/Eigen/src/Core/Select.h \
    dependencies/Eigen/src/Core/SelfAdjointView.h \
    dependencies/Eigen/src/Core/SelfCwiseBinaryOp.h \
    dependencies/Eigen/src/Core/Solve.h \
    dependencies/Eigen/src/Core/SolveTriangular.h \
    dependencies/Eigen/src/Core/SolverBase.h \
    dependencies/Eigen/src/Core/StableNorm.h \
    dependencies/Eigen/src/Core/Stride.h \
    dependencies/Eigen/src/Core/Swap.h \
    dependencies/Eigen/src/Core/Transpose.h \
    dependencies/Eigen/src/Core/Transpositions.h \
    dependencies/Eigen/src/Core/TriangularMatrix.h \
    dependencies/Eigen/src/Core/VectorBlock.h \
    dependencies/Eigen/src/Core/VectorwiseOp.h \
    dependencies/Eigen/src/Core/Visitor.h \
    dependencies/Eigen/src/Core/arch/AVX/Complex.h \
    dependencies/Eigen/src/Core/arch/AVX/MathFunctions.h \
    dependencies/Eigen/src/Core/arch/AVX/PacketMath.h \
    dependencies/Eigen/src/Core/arch/AVX/TypeCasting.h \
    dependencies/Eigen/src/Core/arch/AVX512/MathFunctions.h \
    dependencies/Eigen/src/Core/arch/AVX512/PacketMath.h \
    dependencies/Eigen/src/Core/arch/AltiVec/Complex.h \
    dependencies/Eigen/src/Core/arch/AltiVec/MathFunctions.h \
    dependencies/Eigen/src/Core/arch/AltiVec/PacketMath.h \
    dependencies/Eigen/src/Core/arch/CUDA/Complex.h \
    dependencies/Eigen/src/Core/arch/CUDA/Half.h \
    dependencies/Eigen/src/Core/arch/CUDA/MathFunctions.h \
    dependencies/Eigen/src/Core/arch/CUDA/PacketMath.h \
    dependencies/Eigen/src/Core/arch/CUDA/PacketMathHalf.h \
    dependencies/Eigen/src/Core/arch/CUDA/TypeCasting.h \
    dependencies/Eigen/src/Core/arch/Default/Settings.h \
    dependencies/Eigen/src/Core/arch/NEON/Complex.h \
    dependencies/Eigen/src/Core/arch/NEON/MathFunctions.h \
    dependencies/Eigen/src/Core/arch/NEON/PacketMath.h \
    dependencies/Eigen/src/Core/arch/SSE/Complex.h \
    dependencies/Eigen/src/Core/arch/SSE/MathFunctions.h \
    dependencies/Eigen/src/Core/arch/SSE/PacketMath.h \
    dependencies/Eigen/src/Core/arch/SSE/TypeCasting.h \
    dependencies/Eigen/src/Core/arch/ZVector/Complex.h \
    dependencies/Eigen/src/Core/arch/ZVector/MathFunctions.h \
    dependencies/Eigen/src/Core/arch/ZVector/PacketMath.h \
    dependencies/Eigen/src/Core/functors/AssignmentFunctors.h \
    dependencies/Eigen/src/Core/functors/BinaryFunctors.h \
    dependencies/Eigen/src/Core/functors/NullaryFunctors.h \
    dependencies/Eigen/src/Core/functors/StlFunctors.h \
    dependencies/Eigen/src/Core/functors/TernaryFunctors.h \
    dependencies/Eigen/src/Core/functors/UnaryFunctors.h \
    dependencies/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
    dependencies/Eigen/src/Core/products/GeneralMatrixMatrix.h \
    dependencies/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
    dependencies/Eigen/src/Core/products/GeneralMatrixMatrixTriangular_BLAS.h \
    dependencies/Eigen/src/Core/products/GeneralMatrixMatrix_BLAS.h \
    dependencies/Eigen/src/Core/products/GeneralMatrixVector.h \
    dependencies/Eigen/src/Core/products/GeneralMatrixVector_BLAS.h \
    dependencies/Eigen/src/Core/products/Parallelizer.h \
    dependencies/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
    dependencies/Eigen/src/Core/products/SelfadjointMatrixMatrix_BLAS.h \
    dependencies/Eigen/src/Core/products/SelfadjointMatrixVector.h \
    dependencies/Eigen/src/Core/products/SelfadjointMatrixVector_BLAS.h \
    dependencies/Eigen/src/Core/products/SelfadjointProduct.h \
    dependencies/Eigen/src/Core/products/SelfadjointRank2Update.h \
    dependencies/Eigen/src/Core/products/TriangularMatrixMatrix.h \
    dependencies/Eigen/src/Core/products/TriangularMatrixMatrix_BLAS.h \
    dependencies/Eigen/src/Core/products/TriangularMatrixVector.h \
    dependencies/Eigen/src/Core/products/TriangularMatrixVector_BLAS.h \
    dependencies/Eigen/src/Core/products/TriangularSolverMatrix.h \
    dependencies/Eigen/src/Core/products/TriangularSolverMatrix_BLAS.h \
    dependencies/Eigen/src/Core/products/TriangularSolverVector.h \
    dependencies/Eigen/src/Core/util/BlasUtil.h \
    dependencies/Eigen/src/Core/util/Constants.h \
    dependencies/Eigen/src/Core/util/DisableStupidWarnings.h \
    dependencies/Eigen/src/Core/util/ForwardDeclarations.h \
    dependencies/Eigen/src/Core/util/MKL_support.h \
    dependencies/Eigen/src/Core/util/Macros.h \
    dependencies/Eigen/src/Core/util/Memory.h \
    dependencies/Eigen/src/Core/util/Meta.h \
    dependencies/Eigen/src/Core/util/NonMPL2.h \
    dependencies/Eigen/src/Core/util/ReenableStupidWarnings.h \
    dependencies/Eigen/src/Core/util/StaticAssert.h \
    dependencies/Eigen/src/Core/util/XprHelper.h \
    dependencies/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
    dependencies/Eigen/src/Eigenvalues/ComplexSchur.h \
    dependencies/Eigen/src/Eigenvalues/ComplexSchur_LAPACKE.h \
    dependencies/Eigen/src/Eigenvalues/EigenSolver.h \
    dependencies/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
    dependencies/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
    dependencies/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
    dependencies/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
    dependencies/Eigen/src/Eigenvalues/RealQZ.h \
    dependencies/Eigen/src/Eigenvalues/RealSchur.h \
    dependencies/Eigen/src/Eigenvalues/RealSchur_LAPACKE.h \
    dependencies/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
    dependencies/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_LAPACKE.h \
    dependencies/Eigen/src/Eigenvalues/Tridiagonalization.h \
    dependencies/Eigen/src/Geometry/AlignedBox.h \
    dependencies/Eigen/src/Geometry/AngleAxis.h \
    dependencies/Eigen/src/Geometry/EulerAngles.h \
    dependencies/Eigen/src/Geometry/Homogeneous.h \
    dependencies/Eigen/src/Geometry/Hyperplane.h \
    dependencies/Eigen/src/Geometry/OrthoMethods.h \
    dependencies/Eigen/src/Geometry/ParametrizedLine.h \
    dependencies/Eigen/src/Geometry/Quaternion.h \
    dependencies/Eigen/src/Geometry/Rotation2D.h \
    dependencies/Eigen/src/Geometry/RotationBase.h \
    dependencies/Eigen/src/Geometry/Scaling.h \
    dependencies/Eigen/src/Geometry/Transform.h \
    dependencies/Eigen/src/Geometry/Translation.h \
    dependencies/Eigen/src/Geometry/Umeyama.h \
    dependencies/Eigen/src/Geometry/arch/Geometry_SSE.h \
    dependencies/Eigen/src/Householder/BlockHouseholder.h \
    dependencies/Eigen/src/Householder/Householder.h \
    dependencies/Eigen/src/Householder/HouseholderSequence.h \
    dependencies/Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
    dependencies/Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
    dependencies/Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
    dependencies/Eigen/src/IterativeLinearSolvers/IncompleteCholesky.h \
    dependencies/Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
    dependencies/Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
    dependencies/Eigen/src/IterativeLinearSolvers/LeastSquareConjugateGradient.h \
    dependencies/Eigen/src/IterativeLinearSolvers/SolveWithGuess.h \
    dependencies/Eigen/src/Jacobi/Jacobi.h \
    dependencies/Eigen/src/LU/Determinant.h \
    dependencies/Eigen/src/LU/FullPivLU.h \
    dependencies/Eigen/src/LU/InverseImpl.h \
    dependencies/Eigen/src/LU/PartialPivLU.h \
    dependencies/Eigen/src/LU/PartialPivLU_LAPACKE.h \
    dependencies/Eigen/src/LU/arch/Inverse_SSE.h \
    dependencies/Eigen/src/MetisSupport/MetisSupport.h \
    dependencies/Eigen/src/OrderingMethods/Amd.h \
    dependencies/Eigen/src/OrderingMethods/Eigen_Colamd.h \
    dependencies/Eigen/src/OrderingMethods/Ordering.h \
    dependencies/Eigen/src/PaStiXSupport/PaStiXSupport.h \
    dependencies/Eigen/src/PardisoSupport/PardisoSupport.h \
    dependencies/Eigen/src/QR/ColPivHouseholderQR.h \
    dependencies/Eigen/src/QR/ColPivHouseholderQR_LAPACKE.h \
    dependencies/Eigen/src/QR/CompleteOrthogonalDecomposition.h \
    dependencies/Eigen/src/QR/FullPivHouseholderQR.h \
    dependencies/Eigen/src/QR/HouseholderQR.h \
    dependencies/Eigen/src/QR/HouseholderQR_LAPACKE.h \
    dependencies/Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
    dependencies/Eigen/src/SVD/BDCSVD.h \
    dependencies/Eigen/src/SVD/JacobiSVD.h \
    dependencies/Eigen/src/SVD/JacobiSVD_LAPACKE.h \
    dependencies/Eigen/src/SVD/SVDBase.h \
    dependencies/Eigen/src/SVD/UpperBidiagonalization.h \
    dependencies/Eigen/src/SparseCholesky/SimplicialCholesky.h \
    dependencies/Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
    dependencies/Eigen/src/SparseCore/AmbiVector.h \
    dependencies/Eigen/src/SparseCore/CompressedStorage.h \
    dependencies/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
    dependencies/Eigen/src/SparseCore/MappedSparseMatrix.h \
    dependencies/Eigen/src/SparseCore/SparseAssign.h \
    dependencies/Eigen/src/SparseCore/SparseBlock.h \
    dependencies/Eigen/src/SparseCore/SparseColEtree.h \
    dependencies/Eigen/src/SparseCore/SparseCompressedBase.h \
    dependencies/Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
    dependencies/Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
    dependencies/Eigen/src/SparseCore/SparseDenseProduct.h \
    dependencies/Eigen/src/SparseCore/SparseDiagonalProduct.h \
    dependencies/Eigen/src/SparseCore/SparseDot.h \
    dependencies/Eigen/src/SparseCore/SparseFuzzy.h \
    dependencies/Eigen/src/SparseCore/SparseMap.h \
    dependencies/Eigen/src/SparseCore/SparseMatrix.h \
    dependencies/Eigen/src/SparseCore/SparseMatrixBase.h \
    dependencies/Eigen/src/SparseCore/SparsePermutation.h \
    dependencies/Eigen/src/SparseCore/SparseProduct.h \
    dependencies/Eigen/src/SparseCore/SparseRedux.h \
    dependencies/Eigen/src/SparseCore/SparseRef.h \
    dependencies/Eigen/src/SparseCore/SparseSelfAdjointView.h \
    dependencies/Eigen/src/SparseCore/SparseSolverBase.h \
    dependencies/Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
    dependencies/Eigen/src/SparseCore/SparseTranspose.h \
    dependencies/Eigen/src/SparseCore/SparseTriangularView.h \
    dependencies/Eigen/src/SparseCore/SparseUtil.h \
    dependencies/Eigen/src/SparseCore/SparseVector.h \
    dependencies/Eigen/src/SparseCore/SparseView.h \
    dependencies/Eigen/src/SparseCore/TriangularSolver.h \
    dependencies/Eigen/src/SparseLU/SparseLU.h \
    dependencies/Eigen/src/SparseLU/SparseLUImpl.h \
    dependencies/Eigen/src/SparseLU/SparseLU_Memory.h \
    dependencies/Eigen/src/SparseLU/SparseLU_Structs.h \
    dependencies/Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
    dependencies/Eigen/src/SparseLU/SparseLU_Utils.h \
    dependencies/Eigen/src/SparseLU/SparseLU_column_bmod.h \
    dependencies/Eigen/src/SparseLU/SparseLU_column_dfs.h \
    dependencies/Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
    dependencies/Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
    dependencies/Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
    dependencies/Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
    dependencies/Eigen/src/SparseLU/SparseLU_panel_bmod.h \
    dependencies/Eigen/src/SparseLU/SparseLU_panel_dfs.h \
    dependencies/Eigen/src/SparseLU/SparseLU_pivotL.h \
    dependencies/Eigen/src/SparseLU/SparseLU_pruneL.h \
    dependencies/Eigen/src/SparseLU/SparseLU_relax_snode.h \
    dependencies/Eigen/src/SparseQR/SparseQR.h \
    dependencies/Eigen/src/StlSupport/StdDeque.h \
    dependencies/Eigen/src/StlSupport/StdList.h \
    dependencies/Eigen/src/StlSupport/StdVector.h \
    dependencies/Eigen/src/StlSupport/details.h \
    dependencies/Eigen/src/SuperLUSupport/SuperLUSupport.h \
    dependencies/Eigen/src/UmfPackSupport/UmfPackSupport.h \
    dependencies/Eigen/src/misc/Image.h \
    dependencies/Eigen/src/misc/Kernel.h \
    dependencies/Eigen/src/misc/RealSvd2x2.h \
    dependencies/Eigen/src/misc/blas.h \
    dependencies/Eigen/src/misc/lapack.h \
    dependencies/Eigen/src/misc/lapacke.h \
    dependencies/Eigen/src/misc/lapacke_mangling.h \
    dependencies/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
    dependencies/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
    dependencies/Eigen/src/plugins/BlockMethods.h \
    dependencies/Eigen/src/plugins/CommonCwiseBinaryOps.h \
    dependencies/Eigen/src/plugins/CommonCwiseUnaryOps.h \
    dependencies/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
    dependencies/Eigen/src/plugins/MatrixCwiseUnaryOps.h \
    dependencies/rapidjson/allocators.h \
    dependencies/rapidjson/cursorstreamwrapper.h \
    dependencies/rapidjson/document.h \
    dependencies/rapidjson/encodedstream.h \
    dependencies/rapidjson/encodings.h \
    dependencies/rapidjson/error/en.h \
    dependencies/rapidjson/error/error.h \
    dependencies/rapidjson/filereadstream.h \
    dependencies/rapidjson/filewritestream.h \
    dependencies/rapidjson/fwd.h \
    dependencies/rapidjson/internal/biginteger.h \
    dependencies/rapidjson/internal/clzll.h \
    dependencies/rapidjson/internal/diyfp.h \
    dependencies/rapidjson/internal/dtoa.h \
    dependencies/rapidjson/internal/ieee754.h \
    dependencies/rapidjson/internal/itoa.h \
    dependencies/rapidjson/internal/meta.h \
    dependencies/rapidjson/internal/pow10.h \
    dependencies/rapidjson/internal/regex.h \
    dependencies/rapidjson/internal/stack.h \
    dependencies/rapidjson/internal/strfunc.h \
    dependencies/rapidjson/internal/strtod.h \
    dependencies/rapidjson/internal/swap.h \
    dependencies/rapidjson/istreamwrapper.h \
    dependencies/rapidjson/memorybuffer.h \
    dependencies/rapidjson/memorystream.h \
    dependencies/rapidjson/msinttypes/inttypes.h \
    dependencies/rapidjson/msinttypes/stdint.h \
    dependencies/rapidjson/ostreamwrapper.h \
    dependencies/rapidjson/pointer.h \
    dependencies/rapidjson/prettywriter.h \
    dependencies/rapidjson/rapidjson.h \
    dependencies/rapidjson/reader.h \
    dependencies/rapidjson/schema.h \
    dependencies/rapidjson/stream.h \
    dependencies/rapidjson/stringbuffer.h \
    dependencies/rapidjson/writer.h \
    interfaceframe.h \
    server/stampede2/stampede2.h \
    swsolvers/geoclaw/geoclaw.h \
    mainwindow.h \
    qt3dframe.h \
    scenemodifier.h \
    cfdsolvers/openfoam/openfoam.h

FORMS += \
    interfaceframe.ui \
    mainwindow.ui 

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

INCLUDEPATH += \
    dependencies/Eigen
    dependencies/rapidjson

DISTFILES += \
    dependencies/Eigen/CMakeLists.txt
