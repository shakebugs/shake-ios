#!/bin/sh

#  upload-symbols.sh
#  Shake
#
#  Created by Filip Belakon on 09.04.2021..
#  Copyright © 2021 Shake Technologies Inc. All rights reserved.

client_id="" client_secret=""
while (( $# > 1 )); do case $1 in
   --client_id) client_id="$2";;
   --client_secret) client_secret="$2";;
   *) break;
 esac; shift 2
done

if [ -z "$client_id" ] || [ -z "$client_secret" ]
    then
        echo "SHAKE_SCRIPT: err: please enter client_id and client_secret"
        exit 0
fi

BUNDLE_VERSION=$(/usr/libexec/PlistBuddy -c "print CFBundleVersion" "${SRCROOT}/${INFOPLIST_FILE}")
BUNDLE_VERSION_STRING=$(/usr/libexec/PlistBuddy -c "print CFBundleShortVersionString" "${SRCROOT}/${INFOPLIST_FILE}")

echo "CFBundleVersion: ${BUNDLE_VERSION}"
echo "CFBundleShortVersionString: ${BUNDLE_VERSION_STRING}"
echo "BundleId: ${PRODUCT_BUNDLE_IDENTIFIER}"

OAUTH_TOKEN_ENDPOINT="https://api.shakebugs.com/auth/oauth2/token"
COMMAND=$(curl --silent -d "grant_type=client_credentials&client_id=${client_id}&client_secret=${client_secret}" $OAUTH_TOKEN_ENDPOINT)

ACCESS_TOKEN=$(echo $COMMAND | tr { '\n' | tr , '\n' | tr } '\n' | grep "access_token" | awk  -F'"' '{print $4}')

if [ -z "$ACCESS_TOKEN" ]; then
    echo "SHAKE_SCRIPT: err: check for client id and client secret."
    echo "SHAKE_SCRIPT: err: cannot accessing api token..."
    exit 0
fi

uploading_dsym_file() {
    FILE=$1
    
    ENDPOINT="https://api.shakebugs.com/api/1.0/crash_reporting/app_debug_file/${PRODUCT_BUNDLE_IDENTIFIER}"
    
    STATUS=$(curl --silent --output /dev/null -H "Authorization: Bearer $ACCESS_TOKEN"\
        -F app_version_name="${BUNDLE_VERSION_STRING}" -F app_version_code="${BUNDLE_VERSION}"\
        -F os="iOS" -F platform="iOS" -F bundle_id="${PRODUCT_BUNDLE_IDENTIFIER}" -F file=@"${FILE}"\
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

