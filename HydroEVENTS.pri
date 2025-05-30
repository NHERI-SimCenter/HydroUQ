INCLUDEPATH += $$PWD/EVENTS
INCLUDEPATH += EVENTS
# INCLUDEPATH += $$PWD/EDP
# INCLUDEPATH += EDP
# INCLUDEPATH += ../SimCenterCommon/Common
INCLUDEPATH += $$PWD/EVENTS/GeoClawOpenFOAM
INCLUDEPATH += $$PWD/EVENTS/WaveDigitalFlume
INCLUDEPATH += $$PWD/EVENTS/coupledDigitalTwin
INCLUDEPATH += $$PWD/EVENTS/MPM
INCLUDEPATH += $$PWD/EVENTS/MPMEvent
INCLUDEPATH += $$PWD/EVENTS/TaichiEvent
INCLUDEPATH += $$PWD/EVENTS/Celeris
INCLUDEPATH += $$PWD/EVENTS/CelerisWebGPU
INCLUDEPATH += $$PWD/EVENTS/CelerisWebGPU/js
INCLUDEPATH += $$PWD/EVENTS/NOAA
INCLUDEPATH += $$PWD/EVENTS/StochasticWaveModel
INCLUDEPATH += $$PWD/EVENTS/StochasticWaveModel/include
INCLUDEPATH += $$PWD/EVENTS/StochasticWaveModel/src
INCLUDEPATH += $$PWD/EVENTS/Common
INCLUDEPATH += $$PWD/SlidingStackedWidget

SOURCES += \
    $$PWD/EVENTS/HydroEventSelection.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/hydroerror.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/GeoClawOpenFOAM.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/H20utilities/h20utilities.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundary.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundarydata.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/buildings.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/cfdsolvers/openfoam/openfoam.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/cfdsolvers/openfoam/systemfiles.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/floatingbds.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconalpha.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconpres.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconvel.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/materials.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/meshing.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/qt3dframe.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/scenemodifier.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/solver.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/swcfdint.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/swsolvers/geoclaw/geoclaw.cpp \
    $$PWD/EVENTS/GeoClawOpenFOAM/postprocess.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/CoupledDigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/SettingsDigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/OutputsDigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/OpenSeesDigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/OpenFOAM_DigitalTwin.cpp \
    $$PWD/EVENTS/coupledDigitalTwin/VisualizeDigitalTwin.cpp \
    $$PWD/EVENTS/MPM/MPM.cpp \
    $$PWD/EVENTS/MPM/BoundaryMPM.cpp \
    $$PWD/EVENTS/MPM/BoundariesMPM.cpp \
    $$PWD/EVENTS/MPM/OutputsMPM.cpp \
    $$PWD/EVENTS/MPM/SensorsMPM.cpp \
    $$PWD/EVENTS/MPM/SensorMPM.cpp \
    $$PWD/EVENTS/MPM/BodiesMPM.cpp \
    $$PWD/EVENTS/MPM/SettingsMPM.cpp \
    $$PWD/EVENTS/MPM/MaterialMPM.cpp \
    $$PWD/EVENTS/MPM/GeometriesMPM.cpp \
    $$PWD/EVENTS/MPM/GeometryMPM.cpp \
    $$PWD/EVENTS/MPM/AlgorithmMPM.cpp \
    $$PWD/EVENTS/MPM/PartitionsMPM.cpp \
    $$PWD/EVENTS/MPM/PartitionMPM.cpp \
    $$PWD/EVENTS/MPM/ResultsMPM.cpp \
    $$PWD/EVENTS/MPM/GeometryAI.cpp \
    $$PWD/EVENTS/MPM/SPH.cpp \
    $$PWD/EVENTS/MPM/CaseSPH.cpp \
    $$PWD/EVENTS/MPM/ExecutionSPH.cpp \
    $$PWD/EVENTS/MPMEvent/MPMEvent.cpp \
    $$PWD/EVENTS/MPMEvent/BasicMPMEvent.cpp \
    $$PWD/EVENTS/TaichiEvent/TaichiEvent.cpp \
    $$PWD/EVENTS/TaichiEvent/BasicTaichiEvent.cpp \
    $$PWD/EVENTS/Celeris/CelerisDomain.cpp \
    $$PWD/EVENTS/Celeris/CelerisSolver.cpp \
    $$PWD/EVENTS/Celeris/CelerisTaichi.cpp \
    $$PWD/EVENTS/Celeris/CelerisTaichiEvent.cpp \
    $$PWD/EVENTS/CelerisWebGPU/Celeris.cpp \
    $$PWD/EVENTS/CelerisWebGPU/WebGPU.cpp \
    $$PWD/EVENTS/CelerisWebGPU/volumetric.cpp \
    $$PWD/EVENTS/NOAA/DigitalCoast.cpp \
    $$PWD/EVENTS/StochasticWaveModel/src/StochasticWaveInput.cpp \
    $$PWD/EVENTS/StochasticWaveModel/src/Jonswap.cpp \
    $$PWD/EVENTS/WaveDigitalFlume/WaveDigitalFlume.cpp \
    $$PWD/EVENTS/Common/projectsettings.cpp \
    $$PWD/EVENTS/Common/bathymetry.cpp
    # $$PWD/SlidingStackedWidget/slidingstackedwidget.cpp


HEADERS += \
    $$PWD/EVENTS/HydroEventSelection.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/hydroerror.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/H20utilities/h20utilities.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundary.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundarydata.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/buildings.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/floatingbds.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconalpha.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconpres.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconvel.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/GeoClawOpenFOAM.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/materials.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/meshing.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/qt3dframe.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/scenemodifier.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/solver.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/swcfdint.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/swsolvers/geoclaw/geoclaw.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/cfdsolvers/openfoam/openfoam.h \
    $$PWD/EVENTS/GeoClawOpenFOAM/postprocess.h \
    $$PWD/EVENTS/coupledDigitalTwin/CoupledDigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/SettingsDigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/OutputsDigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/OpenSeesDigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/OpenFOAM_DigitalTwin.h \
    $$PWD/EVENTS/coupledDigitalTwin/VisualizeDigitalTwin.h \
    $$PWD/EVENTS/MPM/MPM.h \
    $$PWD/EVENTS/MPM/BoundaryMPM.h \
    $$PWD/EVENTS/MPM/BoundariesMPM.h \
    $$PWD/EVENTS/MPM/OutputsMPM.h \
    $$PWD/EVENTS/MPM/SensorsMPM.h \
    $$PWD/EVENTS/MPM/SensorMPM.h \
    $$PWD/EVENTS/MPM/BodiesMPM.h \
    $$PWD/EVENTS/MPM/SettingsMPM.h \   
    $$PWD/EVENTS/MPM/MaterialMPM.h \
    $$PWD/EVENTS/MPM/GeometriesMPM.h \
    $$PWD/EVENTS/MPM/GeometryMPM.h \
    $$PWD/EVENTS/MPM/AlgorithmMPM.h \
    $$PWD/EVENTS/MPM/PartitionsMPM.h \   
    $$PWD/EVENTS/MPM/PartitionMPM.h \  
    $$PWD/EVENTS/MPM/ResultsMPM.h \
    $$PWD/EVENTS/MPM/GeometryAI.h \
    $$PWD/EVENTS/MPM/SPH.h \
    $$PWD/EVENTS/MPM/CaseSPH.h \
    $$PWD/EVENTS/MPM/ExecutionSPH.h \
    $$PWD/EVENTS/MPMEvent/MPMEvent.h \
    $$PWD/EVENTS/MPMEvent/BasicMPMEvent.h \
    $$PWD/EVENTS/TaichiEvent/TaichiEvent.h \
    $$PWD/EVENTS/TaichiEvent/BasicTaichiEvent.h \
    $$PWD/EVENTS/Celeris/CelerisDomain.h \
    $$PWD/EVENTS/Celeris/CelerisSolver.h \
    $$PWD/EVENTS/Celeris/CelerisTaichi.h \
    $$PWD/EVENTS/Celeris/CelerisTaichiEvent.h \
    $$PWD/EVENTS/CelerisWebGPU/Celeris.h \
    $$PWD/EVENTS/CelerisWebGPU/WebGPU.h \
    $$PWD/EVENTS/CelerisWebGPU/volumetric.h \
    $$PWD/EVENTS/NOAA/DigitalCoast.h \
    $$PWD/EVENTS/StochasticWaveModel/include/StochasticWaveInput.h \
    $$PWD/EVENTS/StochasticWaveModel/include/Jonswap.h \
    $$PWD/EVENTS/WaveDigitalFlume/WaveDigitalFlume.h \
    $$PWD/EVENTS/Common/projectsettings.h \
    $$PWD/EVENTS/Common/bathymetry.h \
    $$PWD/EVENTS/dependencies/Eigen/Cholesky \
    $$PWD/EVENTS/dependencies/Eigen/CholmodSupport \
    $$PWD/EVENTS/dependencies/Eigen/Core \
    $$PWD/EVENTS/dependencies/Eigen/Dense \
    $$PWD/EVENTS/dependencies/Eigen/Eigen \
    $$PWD/EVENTS/dependencies/Eigen/Eigenvalues \
    $$PWD/EVENTS/dependencies/Eigen/Geometry \
    $$PWD/EVENTS/dependencies/Eigen/Householder \
    $$PWD/EVENTS/dependencies/Eigen/IterativeLinearSolvers \
    $$PWD/EVENTS/dependencies/Eigen/Jacobi \
    $$PWD/EVENTS/dependencies/Eigen/LU \
    $$PWD/EVENTS/dependencies/Eigen/MetisSupport \
    $$PWD/EVENTS/dependencies/Eigen/OrderingMethods \
    $$PWD/EVENTS/dependencies/Eigen/PaStiXSupport \
    $$PWD/EVENTS/dependencies/Eigen/PardisoSupport \
    $$PWD/EVENTS/dependencies/Eigen/QR \
    $$PWD/EVENTS/dependencies/Eigen/QtAlignedMalloc \
    $$PWD/EVENTS/dependencies/Eigen/SPQRSupport \
    $$PWD/EVENTS/dependencies/Eigen/SVD \
    $$PWD/EVENTS/dependencies/Eigen/Sparse \
    $$PWD/EVENTS/dependencies/Eigen/SparseCholesky \
    $$PWD/EVENTS/dependencies/Eigen/SparseCore \
    $$PWD/EVENTS/dependencies/Eigen/SparseLU \
    $$PWD/EVENTS/dependencies/Eigen/SparseQR \
    $$PWD/EVENTS/dependencies/Eigen/StdDeque \
    $$PWD/EVENTS/dependencies/Eigen/StdList \
    $$PWD/EVENTS/dependencies/Eigen/StdVector \
    $$PWD/EVENTS/dependencies/Eigen/SuperLUSupport \
    $$PWD/EVENTS/dependencies/Eigen/UmfPackSupport \
    $$PWD/EVENTS/dependencies/Eigen/src/Cholesky/LDLT.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Cholesky/LLT.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Cholesky/LLT_LAPACKE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/CholmodSupport/CholmodSupport.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Array.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/ArrayBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/ArrayWrapper.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Assign.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/AssignEvaluator.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Assign_MKL.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/BandMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Block.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/BooleanRedux.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/CommaInitializer.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/ConditionEstimator.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/CoreEvaluators.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/CoreIterators.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/CwiseBinaryOp.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/CwiseNullaryOp.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/CwiseTernaryOp.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/CwiseUnaryOp.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/CwiseUnaryView.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/DenseBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/DenseCoeffsBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/DenseStorage.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Diagonal.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/DiagonalMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/DiagonalProduct.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Dot.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/EigenBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/ForceAlignedAccess.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Fuzzy.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/GeneralProduct.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/GenericPacketMath.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/GlobalFunctions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/IO.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Inverse.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Map.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/MapBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/MathFunctions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/MathFunctionsImpl.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Matrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/MatrixBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/NestByValue.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/NoAlias.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/NumTraits.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/PermutationMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/PlainObjectBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Product.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/ProductEvaluators.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Random.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Redux.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Ref.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Replicate.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/ReturnByValue.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Reverse.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Select.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/SelfAdjointView.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/SelfCwiseBinaryOp.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Solve.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/SolveTriangular.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/SolverBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/StableNorm.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Stride.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Swap.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Transpose.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Transpositions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/TriangularMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/VectorBlock.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/VectorwiseOp.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/Visitor.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/AVX/Complex.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/AVX/MathFunctions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/AVX/PacketMath.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/AVX/TypeCasting.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/AVX512/MathFunctions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/AVX512/PacketMath.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/AltiVec/Complex.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/AltiVec/MathFunctions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/AltiVec/PacketMath.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/CUDA/Complex.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/CUDA/Half.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/CUDA/MathFunctions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/CUDA/PacketMath.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/CUDA/PacketMathHalf.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/CUDA/TypeCasting.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/Default/Settings.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/NEON/Complex.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/NEON/MathFunctions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/NEON/PacketMath.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/SSE/Complex.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/SSE/MathFunctions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/SSE/PacketMath.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/SSE/TypeCasting.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/ZVector/Complex.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/ZVector/MathFunctions.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/arch/ZVector/PacketMath.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/functors/AssignmentFunctors.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/functors/BinaryFunctors.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/functors/NullaryFunctors.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/functors/StlFunctors.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/functors/TernaryFunctors.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/functors/UnaryFunctors.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/GeneralMatrixMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/GeneralMatrixMatrixTriangular_BLAS.h\
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/GeneralMatrixMatrix_BLAS.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/GeneralMatrixVector.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/GeneralMatrixVector_BLAS.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/Parallelizer.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/SelfadjointMatrixMatrix_BLAS.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/SelfadjointMatrixVector.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/SelfadjointMatrixVector_BLAS.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/SelfadjointProduct.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/SelfadjointRank2Update.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/TriangularMatrixMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/TriangularMatrixMatrix_BLAS.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/TriangularMatrixVector.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/TriangularMatrixVector_BLAS.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/TriangularSolverMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/TriangularSolverMatrix_BLAS.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/products/TriangularSolverVector.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/BlasUtil.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/Constants.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/DisableStupidWarnings.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/ForwardDeclarations.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/MKL_support.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/Macros.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/Memory.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/Meta.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/NonMPL2.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/ReenableStupidWarnings.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/StaticAssert.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Core/util/XprHelper.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/ComplexSchur.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/ComplexSchur_LAPACKE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/EigenSolver.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/RealQZ.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/RealSchur.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/RealSchur_LAPACKE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_LAPACKE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Eigenvalues/Tridiagonalization.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/AlignedBox.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/AngleAxis.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/EulerAngles.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/Homogeneous.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/Hyperplane.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/OrthoMethods.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/ParametrizedLine.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/Quaternion.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/Rotation2D.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/RotationBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/Scaling.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/Transform.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/Translation.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/Umeyama.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Geometry/arch/Geometry_SSE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Householder/BlockHouseholder.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Householder/Householder.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Householder/HouseholderSequence.h \
    $$PWD/EVENTS/dependencies/Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
    $$PWD/EVENTS/dependencies/Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
    $$PWD/EVENTS/dependencies/Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
    $$PWD/EVENTS/dependencies/Eigen/src/IterativeLinearSolvers/IncompleteCholesky.h \
    $$PWD/EVENTS/dependencies/Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
    $$PWD/EVENTS/dependencies/Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/IterativeLinearSolvers/LeastSquareConjugateGradient.h \
    $$PWD/EVENTS/dependencies/Eigen/src/IterativeLinearSolvers/SolveWithGuess.h \
    $$PWD/EVENTS/dependencies/Eigen/src/Jacobi/Jacobi.h \
    $$PWD/EVENTS/dependencies/Eigen/src/LU/Determinant.h \
    $$PWD/EVENTS/dependencies/Eigen/src/LU/FullPivLU.h \
    $$PWD/EVENTS/dependencies/Eigen/src/LU/InverseImpl.h \
    $$PWD/EVENTS/dependencies/Eigen/src/LU/PartialPivLU.h \
    $$PWD/EVENTS/dependencies/Eigen/src/LU/PartialPivLU_LAPACKE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/LU/arch/Inverse_SSE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/MetisSupport/MetisSupport.h \
    $$PWD/EVENTS/dependencies/Eigen/src/OrderingMethods/Amd.h \
    $$PWD/EVENTS/dependencies/Eigen/src/OrderingMethods/Eigen_Colamd.h \
    $$PWD/EVENTS/dependencies/Eigen/src/OrderingMethods/Ordering.h \
    $$PWD/EVENTS/dependencies/Eigen/src/PaStiXSupport/PaStiXSupport.h \
    $$PWD/EVENTS/dependencies/Eigen/src/PardisoSupport/PardisoSupport.h \
    $$PWD/EVENTS/dependencies/Eigen/src/QR/ColPivHouseholderQR.h \
    $$PWD/EVENTS/dependencies/Eigen/src/QR/ColPivHouseholderQR_LAPACKE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/QR/CompleteOrthogonalDecomposition.h \
    $$PWD/EVENTS/dependencies/Eigen/src/QR/FullPivHouseholderQR.h \
    $$PWD/EVENTS/dependencies/Eigen/src/QR/HouseholderQR.h \
    $$PWD/EVENTS/dependencies/Eigen/src/QR/HouseholderQR_LAPACKE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SVD/BDCSVD.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SVD/JacobiSVD.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SVD/JacobiSVD_LAPACKE.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SVD/SVDBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SVD/UpperBidiagonalization.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCholesky/SimplicialCholesky.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/AmbiVector.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/CompressedStorage.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/MappedSparseMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseAssign.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseBlock.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseColEtree.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseCompressedBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseDenseProduct.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseDiagonalProduct.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseDot.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseFuzzy.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseMap.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseMatrixBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparsePermutation.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseProduct.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseRedux.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseRef.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseSelfAdjointView.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseSolverBase.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseTranspose.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseTriangularView.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseUtil.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseVector.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/SparseView.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseCore/TriangularSolver.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLUImpl.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_Memory.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_Structs.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_Utils.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_column_bmod.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_column_dfs.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_panel_bmod.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_panel_dfs.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_pivotL.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_pruneL.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseLU/SparseLU_relax_snode.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SparseQR/SparseQR.h \
    $$PWD/EVENTS/dependencies/Eigen/src/StlSupport/StdDeque.h \
    $$PWD/EVENTS/dependencies/Eigen/src/StlSupport/StdList.h \
    $$PWD/EVENTS/dependencies/Eigen/src/StlSupport/StdVector.h \
    $$PWD/EVENTS/dependencies/Eigen/src/StlSupport/details.h \
    $$PWD/EVENTS/dependencies/Eigen/src/SuperLUSupport/SuperLUSupport.h \
    $$PWD/EVENTS/dependencies/Eigen/src/UmfPackSupport/UmfPackSupport.h \
    $$PWD/EVENTS/dependencies/Eigen/src/misc/Image.h \
    $$PWD/EVENTS/dependencies/Eigen/src/misc/Kernel.h \
    $$PWD/EVENTS/dependencies/Eigen/src/misc/RealSvd2x2.h \
    $$PWD/EVENTS/dependencies/Eigen/src/misc/blas.h \
    $$PWD/EVENTS/dependencies/Eigen/src/misc/lapack.h \
    $$PWD/EVENTS/dependencies/Eigen/src/misc/lapacke.h \
    $$PWD/EVENTS/dependencies/Eigen/src/misc/lapacke_mangling.h \
    $$PWD/EVENTS/dependencies/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
    $$PWD/EVENTS/dependencies/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
    $$PWD/EVENTS/dependencies/Eigen/src/plugins/BlockMethods.h \
    $$PWD/EVENTS/dependencies/Eigen/src/plugins/CommonCwiseBinaryOps.h \
    $$PWD/EVENTS/dependencies/Eigen/src/plugins/CommonCwiseUnaryOps.h \
    $$PWD/EVENTS/dependencies/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
    $$PWD/EVENTS/dependencies/Eigen/src/plugins/MatrixCwiseUnaryOps.h 
    # $$PWD/SlidingStackedWidget/slidingstackedwidget.h

FORMS += \
    $$PWD/EVENTS/GeoClawOpenFOAM/GeoClawOpenFOAM_copy.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundary.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundarydata.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/boundarydata_copy.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/buildings.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/floatingbds.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconalpha.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconpres.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/initialconvel.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/GeoClawOpenFOAM.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/materials.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/meshing.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/projectsettings_old.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/solver.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/swcfdint.ui \
    $$PWD/EVENTS/GeoClawOpenFOAM/postprocess.ui \
    $$PWD/EVENTS/WaveDigitalFlume/WaveDigitalFlume.ui \
    $$PWD/EVENTS/Common/projectsettings.ui \
    $$PWD/EVENTS/Common/bathymetry.ui


#    
#    $$PWD/EVENTS/coupledDigitalTwin/SettingsDigitalTwin.h \    


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

INCLUDEPATH += \
    $$PWD/EVENTS/dependencies/Eigen

DISTFILES += \
    $$PWD/EVENTS/dependencies/Eigen/CMakeLists.txt
