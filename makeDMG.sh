#!/bin/bash

#
# parse args
#

DMG_METHOD="NEW"

release=${1:-"NO_RELEASE"}

if [ -n "$release" ] && [ "$release" = "quick" ]; then
    echo "QUICK EXIT"
else
    echo "NOT QUICK"
fi
    

#
# Paramaters
#

APP_NAME="Hydro-UQ"
APP_FILE="Hydro_UQ.app"
DMG_FILENAME="Hydro-UQ_Mac_Download.dmg"

# remove & rebuild app and macdeploy it

QTDIR="/Users/fmckenna/Qt/5.15.2/clang_64/"

pathToBackendApps="/Users/fmckenna/NHERI/SimCenterBackendApplications"
pathToOpenSees="/Users/fmckenna/bin/OpenSees3.6.0"
pathToDakota="/Users/fmckenna/dakota/dakota-6.16.0"

#
# source userID file containig stuff dor signing, ok if not there
#

#
# build it
#

source ./makeEXE.sh $release

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

if [ -n "$release" ] && [ "$release" = "quick" ]; then
    exit 0
fi

# copy applications folderm opensees and dakota

#echo "cp -fR $pathToBackendApps/applications ./$APP_FILE/Contents/MacOS"
mkdir  ./$APP_FILE/Contents/MacOS/applications
cp -fR $pathToBackendApps/applications ./$APP_FILE/Contents/MacOS/

#cp -fr $pathToOpenSees/bin/* ./$APP_FILE/Contents/MacOS/applications/opensees/bin
#cp -fr $pathToOpenSees/lib/* ./$APP_FILE/Contents/Resources/opensees

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


mkdir  ./$APP_FILE/Contents/MacOS/applications/opensees
mkdir  ./$APP_FILE/Contents/MacOS/applications/dakota
cp -fr $pathToOpenSees/* ./$APP_FILE/Contents/MacOS/applications/opensees
cp -fr $pathToDakota/*  ./$APP_FILE/Contents/MacOS/applications/dakota

#
# clean up
#

find ./$APP_FILE -name __pycache__ -exec rm -rf {} +;
find ./$APP_FILE -name results -exec rm -rf {} +;


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



if [ "${DMG_METHOD}" = "NEW" ]; then

    #
    # mv app into empty folder for create-dmg to work
    # brew install create-dmg
    #

    echo "codesign --deep --force --verbose --options runtime --timestamp  --sign "$appleCredential" $APP_FILE"

    codesign --verbose=4 --deep --force --verbose --options=runtime --timestamp  --sign "$appleCredential" $APP_FILE    


    
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
    
    cmd_status=$?
    
    if [[ $cmd_status != 0 ]]
    then
	echo "DMG Creation FAILED cd build and try the following:"
	echo "hdiutil create $DMG_FILENAME -fs HFS+ -srcfolder ./$APP_FILE -format UDZO -volname $APP_NAME"    
	echo "codesign --force --sign "$appleCredential" $DMG_FILENAME"
	echo "xcrun altool --notarize-app -u $appleID -p $appleAppPassword -f ./$DMG_FILENAME --primary-bundle-id altool"
	echo "xcrun altool --notarization-info ID  -u $appleID  -p $appleAppPassword"
	echo "xcrun stapler staple \"$APP_NAME\" $DMG_FILENAME"
    fi
    
    #codesign dmg
    echo "codesign --force --sign "$appleCredential" $DMG_FILENAME"
    codesign --force --sign "$appleCredential" $DMG_FILENAME
    

fi

#
# submit to apple store
#

if [ -n "$release" ] && [ "$release" = "release" ]; then


    echo "xcrun notarytool submit ./$DMG_FILENAME --apple-id $appleID --password $appleAppPassword --team-id $appleCredential"
    
    xcrun notarytool submit ./$DMG_FILENAME --apple-id $appleID --password $appleAppPassword --team-id $appleCredential
    echo ""    
    echo "xcrun notarytool log ID --apple-id $appleID --team-id $appleCredential  --password $appleAppPassword"

    
    echo ""
    echo "Finally staple the dmg"
    echo "xcrun stapler staple \"$APP_NAME\" $DMG_FILENAME"
fi

