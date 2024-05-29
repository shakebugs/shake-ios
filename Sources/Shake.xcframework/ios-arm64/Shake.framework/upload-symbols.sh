#  upload-symbols.sh
#  Shake
#
#  Created by Filip Belakon on 09.04.2021..
#  Copyright © 2021 Shake Technologies Inc. All rights reserved.

api_key="" endpoint_url="https://api.shakebugs.com"

BUNDLE_VERSION=$(/usr/libexec/PlistBuddy -c "print CFBundleVersion" "${SRCROOT}/${INFOPLIST_FILE}")
BUNDLE_VERSION_STRING=$(/usr/libexec/PlistBuddy -c "print CFBundleShortVersionString" "${SRCROOT}/${INFOPLIST_FILE}")

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    --api_key)
    api_key="$2"
    shift # past argument
    shift # past value
    ;;
    --app_version_name)
    BUNDLE_VERSION_STRING="$2"
    shift # past argument
    shift # past value
    ;;
    --app_version_code)
    BUNDLE_VERSION="$2"
    shift # past argument
    shift # past value
    ;;
    --endpoint_url)
    endpoint_url="$2"
    shift # past argument
    shift # past value
    ;;
    *)    # unknown option
    POSITIONAL+=("$1") # save it in an array for later
    shift # past argument
    ;;
esac
done

if [ -z "$api_key" ]
    then
        echo "SHAKE_SCRIPT: err: please enter api_key"
        exit 0
fi

echo "CFBundleVersion: ${BUNDLE_VERSION}"
echo "CFBundleShortVersionString: ${BUNDLE_VERSION_STRING}"
echo "BundleId: ${PRODUCT_BUNDLE_IDENTIFIER}"

uploading_dsym_file() {
    FILE=$1
    
    ENDPOINT="${endpoint_url}/api/2.0/crash_reporting/app_debug_file"
    
    STATUS=$(curl --silent --output /dev/null -H "X-API-KEY: $api_key" -H "X-OS: iOS" -H "X-PLATFORM: iOS" -H "X-APP-ID: $PRODUCT_BUNDLE_IDENTIFIER"\
        -F app_version_name="${BUNDLE_VERSION_STRING}" -F app_version_code="${BUNDLE_VERSION}" -F file=@"${FILE}"\
        "$ENDPOINT" --write-out %{http_code})
    
    if [ $STATUS -ne 200 ]; then
        echo "SHAKE_SCRIPT err: dSYM archive not successfully uploaded."
        echo "Something went wrong during Shake dSYM upload. Status code is $STATUS"
        echo "SHAKE_SCRIPT: deleting temporary dSYM archive..."
        rm -f "${FILE}"
        exit 0
    fi
}


if [ -e "${DWARF_DSYM_FOLDER_PATH}/${DWARF_DSYM_FILE_NAME}" ]
then
    
    DSYM_SRC="${DWARF_DSYM_FOLDER_PATH}"
    DSYM_ARCHIVE_PATH="/tmp/${DSYM_SRC##*/}.zip"

    echo
    echo "Archiving dSYMs \"${DSYM_SRC}\" to \"${DSYM_ARCHIVE_PATH}\""

    cd ${DWARF_DSYM_FOLDER_PATH}
    
    for dSYM in *
    do
        if [[ "$dSYM" == *.dSYM ]] ;
        then
            echo "adding symbols $dSYM"
            /usr/bin/zip --recurse-paths --quiet "${DSYM_ARCHIVE_PATH}" "$dSYM"
        fi
    done

    for subfolder in *
    do
        if [ -d "${DWARF_DSYM_FOLDER_PATH}/$subfolder" ]
        then
            cd "$subfolder"
            
            for dSYM in *
            do
                if [[ $dSYM == *.dSYM ]] ;
                then
                    echo "adding symbols $dSYM"
                    /usr/bin/zip --recurse-paths --quiet "${DSYM_ARCHIVE_PATH}" *.dSYM
                    break
                fi
            done
            
            cd ..
        fi
    done
    
    uploading_dsym_file "$DSYM_ARCHIVE_PATH"
    
    echo "SHAKE_SCRIPT: deleting temporary dSYM archive..."
    rm -f "$DSYM_ARCHIVE_PATH"
    
    
    echo "SHAKE_SCRIPT: dSYM upload complete."

#zip error: Nothing to do! (try: zip --recurse-paths --quiet /tmp/DebugUAT-iphoneos.zip . -i *.dSYM)

else
    echo "warning: dSYM not found. Please check if 'Debug Information Format' is set to 'DWARF with dSYM file' for building target. You may ignore this warning if build locally. File ${DWARF_DSYM_FOLDER_PATH}/${DWARF_DSYM_FILE_NAME} not found"
    exit 0
fi

