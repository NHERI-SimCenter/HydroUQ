#
# parse args
#

DMG_METHOD="NEW"

for arg in "$@"
do
    if [ "$arg" == "--old" ] || [ "$arg" == "-o" ] || [ $arg == "-OLD" ]; then
	DMG_METHOD="OLD"
    fi
done


#
# Paramaters
#

APP_NAME="Hydro-UQ"
APP_FILE="Hydro_UQ.app"
DMG_FILENAME="Hydro-UQ_Mac_Download.dmg"

# remove & rebuild app and macdeploy it

QTDIR="/Users/fmckenna/Qt/5.15.2/clang_64/"
#QTDIR="/Users/fmckenna/Qt/6.6.0/macos/"
pathToBackendApps="/Users/fmckenna/NHERI/SimCenterBackendApplications"
pathToOpenSees="/Users/fmckenna/bin/OpenSees3.6.0"
pathToDakota="/Users/fmckenna/dakota-6.12.0"

#pathToPython="/Users/fmckenna/PythonEnvR2D"
#
# source userID file containig stuff dor signing, ok if not there
#

#
# build it
#

./makeEXE.sh
cd build
rm $DMG_FILENAME

#
# Check to see if the app built
#

if ! [ -x "$(command -v open $pathApp)" ]; then
	echo "$APP_FILE did not build. Exiting."
	exit 
fi

#
# macdeployqt it
#

macdeployqt ./Hydro_UQ.app 

#
# copy files from VTK dir
#

cp ../../VTK/lib/libvtkgl2ps-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingGL2PSOpenGL2-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkChartsCore-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkCommonColor-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkCommonComputationalGeometry-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkCommonCore-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkCommonDataModel-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkCommonExecutionModel-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkCommonMath-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkCommonMisc-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkCommonSystem-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkCommonTransforms-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkDICOMParser-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersCore-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersExtraction-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersGeneral-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersGeometry-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersHybrid-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersHyperTree-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersImaging-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersModeling-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersSources-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersStatistics-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkFiltersTexture-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkGUISupportQt-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkIOCore-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkIOGeometry-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkIOImage-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkIOLegacy-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkIOXML-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkIOXMLParser-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkImagingColor-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkImagingCore-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkImagingGeneral-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkImagingHybrid-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkImagingSources-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkInfovisCore-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkInfovisLayout-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkInteractionStyle-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkInteractionWidgets-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkParallelCore-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkParallelDIY-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingAnnotation-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingContext2D-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingContextOpenGL2-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingContextOpenGL2-9.2.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingCore-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingFreeType-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingHyperTreeGrid-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingLabel-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingOpenGL2-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingUI-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingVolume-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkRenderingVolume-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkViewsCore-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkViewsInfovis-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkViewsQt-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkdoubleconversion-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkexpat-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkfmt-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkfreetype-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkglew-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkjpeg-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkkissfft-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkloguru-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtklz4-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtklzma-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkmetaio-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkpng-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkpugixml-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtksys-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtktiff-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks
cp ../../VTK/lib/libvtkzlib-9.2.1.dylib ./Hydro_UQ.app/Contents/Frameworks

# copy applications folderm opensees and dakota
echo "cp -fR $pathToBackendApps/applications ./$APP_FILE/Contents/MacOS"
cp -fR $pathToBackendApps/applications ./$APP_FILE/Contents/MacOS
mkdir  ./$APP_FILE/Contents/MacOS/applications/opensees
mkdir  ./$APP_FILE/Contents/MacOS/applications/dakota
echo "cp -fr $pathToOpenSees/* $pathApp/Contents/MacOS/applications/opensees"
cp -fr $pathToOpenSees/* ./$APP_FILE/Contents/MacOS/applications/opensees
cp -fr $pathToDakota/*  ./$APP_FILE/Contents/MacOS/applications/dakota

# clean up
declare -a notWantedApp=("createBIM" 
			 "performRegionalMapping"
			 "performRegionalEventSimulation"
			 "performDL"			
			 "createEDP/standardEarthquakeEDP_R"
			 "createEDP/standardEarthquake"
			 "createEDP/userEDP_R"
			 "createEDP/gmtEDP"		 
			 "createEDP/simpleEDP"
			 "createEDP/standardWindEDP"
			 "createEVENT/ASCE7_WindSpeed"
			 "createEVENT/MultiplePEER"
			 "createEVENT/SiteResponse" 			 
			 "createEVENT/CFDEvent"
			 "createEVENT/hazardBasedEvent"
			 "createEVENT/DEDM_HRP"
			 "createEVENT/stochasticGroundMotion"
			 "createEVENT/stochasticWind"
			 "createEVENT/stochasticWind"
			 "createEVENT/ASCE7_WindSpeed"
			 "createEVENT/LLNL_SW4"
			 "createEVENT/windTunnelExperiment"
			 "createEVENT/LowRiseTPU"
			 "createEVENT/pointWindSpeed"
			 "createSAM/MDOF-LU"
			 "performSIMULATION/IMasEDP"
			 "performSIMULATION/extractPGA"
			 "performSIMULATION/openSees_R"
			)

for app in "${notWantedApp[@]}"
do
   echo "removing $app"
   rm -fr ./$APP_FILE/Contents/MacOS/applications/$app
done

find ./$APP_FILE -name __pycache__ -exec rm -rf {} +;

#
# load my credential file
#

userID="../userID.sh"

if [ ! -f "$userID" ]; then

    echo "creating dmg $DMG_FILENAME"
    rm $DMG_FILENAME
    hdiutil create $DMG_FILENAME -fs HFS+ -srcfolder ./$APP_FILE -format UDZO -volname $APP_NAME

    echo "No password & credential file to continue with codesign and App store verification"
    exit
fi

source $userID
echo $appleID    


if [ "${DMG_METHOD}" == "NEW" ]; then

    #
    # mv app into empty folder for create-dmg to work
    # brew install create-dmg
    #

    echo "codesign --deep --force --verbose --options=runtime  --sign "$appleCredential" $APP_FILE"
    codesign --deep --force --verbose --options=runtime  --sign "$appleCredential" $APP_FILE    
    
    mkdir app
    mv $APP_FILE app
    
    #horizontal
    ../macInstall/create-dmg \
	--volname "${APP_NAME}" \
	--background "../macInstall/background3.png" \
	--window-pos 200 120 \
	--window-size 600 350 \
	--no-internet-enable \
	--icon-size 125 \
	--icon "../icons/NHERI-WEuq-Icon.ico" 125 130 \
	--hide-extension "${APP_NAME}.app" \
	--app-drop-link 450 130 \
	--codesign $appleCredential \
	"${DMG_FILENAME}" \
	"app"

    #  --icon "${APP_NAME}.app" 125 130 \	
    #  --notarize $appleID $appleAppPassword \
	
    mv ./app/$APP_FILE ./
    rm -fr app

else

    #codesign
    echo "codesign --deep --force --verbose --options=runtime  --sign "$appleCredential" $APP_FILE"
    codesign --deep --force --verbose --options=runtime  --sign "$appleCredential" $APP_FILE

    # create dmg
    echo "hdiutil create $DMG_FILENAME -fs HFS+ -srcfolder ./$APP_FILE -format UDZO -volname $APP_NAME"
    hdiutil create $DMG_FILENAME -fs HFS+ -srcfolder ./$APP_FILE -format UDZO -volname $APP_NAME
    
    status=$?
    if [[ $status != 0 ]]
    then
	echo "DMG Creation FAILED cd build and try the following:"
	echo "hdiutil create $DMG_FILENAME -fs HFS+ -srcfolder ./$APP_FILE -format UDZO -volname $APP_NAME"    
	echo "codesign --force --sign "$appleCredential" $DMG_FILENAME"
	echo "xcrun altool --notarize-app -u $appleID -p $appleAppPassword -f ./$DMG_FILENAME --primary-bundle-id altool"
	echo "xcrun altool --notarization-info ID  -u $appleID  -p $appleAppPassword"
	echo "xcrun stapler staple \"$APP_NAME\" $DMG_FILENAME"
	exit $status;
    fi

    #codesign dmg
    echo "codesign --force --sign "$appleCredential" $DMG_FILENAME"
    codesign --force --sign "$appleCredential" $DMG_FILENAME
fi

echo "Issue the following: " 
echo "xcrun altool --notarize-app -u $appleID -p $appleAppPassword -f ./$DMG_FILENAME --primary-bundle-id altool"
echo ""
echo "returns id: ID .. wait for email indicating success"
echo "To check status"
echo "xcrun altool --notarization-info ID  -u $appleID  -p $appleAppPassword"
echo ""
echo "Finally staple the dmg"
echo "xcrun stapler staple \"$APP_NAME\" $DMG_FILENAME"
