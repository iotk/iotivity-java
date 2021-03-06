#!/usr/bin/env sh

# fixup dynamic links on darwin. maybe not needed if DYLD_LIBRARY_PATH correct?

# set java lib path to taste
JLP=${IOTIVITY_HOME}/out/darwin/x86_64/release

# JLP=/usr/local/lib/iotivity/1.1

if [ -d "$IOTIVITY_HOME" ];
then
        if [ ! -d "$JLP" ]
	then
	        echo "java.library.path not found: $JLP";
	        exit
	fi
else
	echo "IOTIVITY_HOME ($IOTIVITY_HOME) not found."
	exit
fi

install_name_tool \
    -change \
    out/darwin/x86_64/release/resource/src/liboc.dylib \
    $JLP/liboc.dylib \
    ./libiotivity-jni.jnilib

install_name_tool \
    -change \
    out/darwin/x86_64/release/resource/csdk/liboctbstack.dylib \
    $JLP/liboctbstack.dylib \
    ./libiotivity-jni.jnilib

install_name_tool \
    -change \
    out/darwin/x86_64/release/resource/provisioning/libocprovision.dylib \
    $JLP/libocprovision.dylib \
    ./libiotivity-jni.jnilib

install_name_tool \
    -change \
    out/darwin/x86_64/release/resource/csdk/security/provisioning/libocpmapi.dylib \
    $JLP/libocpmapi.dylib \
    ./libiotivity-jni.jnilib

install_name_tool \
    -change \
    out/darwin/x86_64/release/resource/oc_logger/liboc_logger.dylib \
    $JLP/liboc_logger.dylib \
    ./libiotivity-jni.jnilib

