
REM ## make the exe .. it assumes Hydro-UQ_Windows_Download exists with vcredist and openssl there

cd build
conan install .. --build missing
qmake QMAKE_CXXFLAGS+=-D_SC_RELEASE ..\Hydro-UQ.pro
nmake

REM ## copy application into folder and winddeployqt it

copy .\Release\Hydro_UQ.exe .\HydroUQ_Windows_Download
cd HydroUQ_Windows_Download
windeployqt Hydro_UQ.exe

REM ## copy examples

rmdir /s /q .\Examples
mkdir .\Examples
xcopy /s /e /Q ..\..\Examples .\Examples

REM ## delete applications folder and copy new stuff

rmdir /s /q .\applications
mkdir .\applications
mkdir .\applications\common
mkdir .\applications\createEDP
mkdir .\applications\createEVENT
mkdir .\applications\createSAM
mkdir .\applications\performSIMULATION
mkdir .\applications\performUQ
mkdir .\applications\Workflow
mkdir .\applications\opensees
mkdir .\applications\dakota
mkdir .\applications\python
mkdir .\applications\claymore
mkdir .\applications\taichi
mkdir .\applications\gns

xcopy /s /e ..\..\..\SimCenterBackendApplications\applications\common  .\applications\common
xcopy /s /e ..\..\..\SimCenterBackendApplications\applications\createEDP  .\applications\createEDP
xcopy /s /e ..\..\..\SimCenterBackendApplications\applications\createEVENT  .\applications\createEVENT
xcopy /s /e ..\..\..\SimCenterBackendApplications\applications\createSAM  .\applications\createSAM
xcopy /s /e ..\..\..\SimCenterBackendApplications\applications\performSIMULATION  .\applications\performSIMULATION
xcopy /s /e ..\..\..\SimCenterBackendApplications\applications\performUQ  .\applications\performUQ
xcopy /s /e ..\..\..\SimCenterBackendApplications\applications\Workflow  .\applications\Workflow
xcopy /s /e ..\..\..\SimCenterBackendApplications\applications\OpenSees  .\applications\opensees
xcopy /s /e ..\..\..\SimCenterBackendApplications\applications\dakota  .\applications\dakota
xcopy /s /e /Q ..\..\..\SimCenterBackendApplications\applications\python  .\applications\python

rmdir /s /q .\applications\createEVENT\ASCE7_WindSpeed
rmdir /s /q .\applications\createEVENT\DEDM_HRP
rmdir /s /q .\applications\createEVENT\EmptyDomainCFD
rmdir /s /q .\applications\createEVENT\experimentalWindForces
rmdir /s /q .\applications\createEVENT\experimentalWindPressures
rmdir /s /q .\applications\createEVENT\groundMotionIM
rmdir /s /q .\applications\createEVENT\HighRiseTPU
rmdir /s /q .\applications\createEVENT\IsolatedBuildingCFD
rmdir /s /q .\applications\createEVENT\LLNL_SW4
rmdir /s /q .\applications\createEVENT\LowRiseTPU
rmdir /s /q .\applications\createEVENT\M9
rmdir /s /q .\applications\createEVENT\multiplePEER
rmdir /s /q .\applications\createEVENT\physicsBasedMotion
rmdir /s /q .\applications\createEVENT\siteResponse
rmdir /s /q .\applications\createEVENT\stochasticWind
rmdir /s /q .\applications\createEVENT\stochasticGroundMotion
rmdir /s /q .\applications\createEVENT\windTunnelExperiment


REM ## zip it up with 7zip

set sevenzip_path="C:\Program Files\7-Zip\7z.exe"
cd ..
if exist .\HydroUQ_Windows_Download.zip (
    del .\HydroUQ_Windows_Download.zip
    echo File deleted.
)
%sevenzip_path% a -tzip .\HydroUQ_Windows_Download.zip  .\HydroUQ_Windows_Download



