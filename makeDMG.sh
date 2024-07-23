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
pathToDakota="/Users/fmckenna/dakota/dakota-6.16.0"

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
			 "createEDP/userEDP_R"
			 "createEDP/gmtEDP"		 
			 "createEVENT/ASCE7_WindSpeed"
			 "createEVENT/MultiplePEER"
			 "createEVENT/SiteResponse" 			 
			 "createEVENT/CFDEvent"
			 "createEVENT/hazardBasedEvent"
			 "createEVENT/DEDM_HRP"
			 "createEVENT/stochasticGroundMotion"
			 "createEVENT/stochasticWind"
			 "createEVENT/ASCE7_WindSpeed"
			 "createEVENT/LLNL_SW4"
			 "createEVENT/windTunnelExperiment"
			 "createEVENT/LowRiseTPU"
			 "createEVENT/pointWindSpeed"
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
	--icon "${APP_FILE}" 125 130 \
	--hide-extension "${APP_FILE}" \
	--app-drop-link 450 130 \
	--codesign $appleCredential \
	"${DMG_FILENAME}" \
	"app"
	
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
echo ""
echo "xcrun notarytool submit ./$DMG_FILENAME --apple-id $appleID --password $appleAppPassword --team-id $appleCredential"
echo "xcrun notarytool log ID --apple-id $appleID --team-id $appleCredential  --password $appleAppPAssword"
echo ""
echo "Finally staple the dmg"
echo "xcrun stapler staple \"$APP_NAME\" $DMG_FILENAME"

