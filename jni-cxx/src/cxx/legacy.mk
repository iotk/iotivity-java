# Makefile for building iotivity java api


# == CHANGE THE SETTINGS BELOW TO SUIT YOUR ENVIRONMENT =======================

# Where to install. The installation starts in the src and doc directories,
# so take care if INSTALL_TOP is not an absolute path. See the local target.
INSTALL_TOP= $(INSTALL_SYSROOT)
INSTALL_BIN= $(INSTALL_TOP)/bin
INSTALL_INC= $(INSTALL_TOP)/include
INSTALL_LIB= $(INSTALL_TOP)/lib
INSTALL_MAN= $(INSTALL_TOP)/man/man1

INSTALL_JNI= $(INSTALL_TOP)/lib
# INSTALL_JNI= $(INSTALL_TOP)/lib/iotivity/$V

# How to install. If your install program does not support "-p", then
# you may have to run ranlib on the installed liblua.a.
INSTALL= install -p
INSTALL_EXEC= $(INSTALL) -m 0755
# INSTALL_DATA= $(INSTALL) -m 0644
#
# If you don't have "install" you can use "cp" instead.
# INSTALL= cp -p
# INSTALL_EXEC= $(INSTALL)
# INSTALL_DATA= $(INSTALL)

# Programs
CC     ?= gcc
AR     ?= ar rcu
MKDIR  ?= mkdir -p
RANLIB ?= ranlib
RM     ?= rm -f

# Options
CPPFLAGS= -fPIC -Wall -Wextra -Wno-unused -Wno-comment $(SYSCFLAGS) $(MYCFLAGS) $(IOT_CXXFLAGS)
CXXFLAGS=-std=c++11
CFLAGS  =-std=c11
LDFLAGS= $(SYSLDFLAGS) $(MYLDFLAGS)
LIBS= -lm $(SYSLIBS) $(MYLIBS)

SYSCFLAGS=-m64 -pthread
SYSLDFLAGS=
SYSLIBS=

OSXCFLAGS=-m64 -Wno-unused-private-field -Wno-unused-parameter -Wno-unused-function -Wno-comment
MYLDFLAGS=
MYLIBS=
MYOBJS=

# == END OF USER SETTINGS -- NO NEED TO CHANGE ANYTHING BELOW THIS LINE =======
# What to install.
TO_LIB= $(BUILD_SYSROOT)/libiotivity-jni.jnilib
# TO_MAN= iotivity.1 iotivity.1

# version and release.
V= 1.1
R= $V.10


# IOTLIBPATH = [env.get('BUILD_DIR')])
# IOTRPATH = [env.get('BUILD_DIR')])

IOTLIBS = -loc -lchibity -loc_logger -lpthread

# if SECURED=1, add  -locprovision  -locpmapi

# IOTIVITY_LIBPATH="$(IOTIVITY_HOME)/out/$(IOTIVITY_HOST_OS)/$(IOTIVITY_HOST_ARCH)/$(IOTIVITY_STAGE)"

# IOTLIBS = $(IOTIVITY_LIBPATH)/liboctbstack.a \
# 	$(IOTIVITY_LIBPATH)/libconnectivity_abstraction.a \
# 	$(IOTIVITY_LIBPATH)/liboc_logger.dylib \
# 	$(IOTIVITY_LIBPATH)/liboc.dylib \
# 	-lpthread

# ifeq ($(SECURED), 1)
#     IOTLIBS += "-ltinydtls -locprovision -locpmapi"
# endif

# elif target_os == 'win32':
#    shlibsuffix = '.dll'
#    jnilibsuffix = '.dll'

#    jni_env.Replace(SHLIBSUFFIX = '.jnilib')

# if target_os in ['darwin', 'ios']:
# 	jni_env.AppendUnique(CPPDEFINES = ['_DARWIN_C_SOURCE'])

# if target_arch in ['x86']:
# 	env.AppendUnique(CCFLAGS = ['-m32'])
# 	env.AppendUnique(LINKFLAGS = ['-m32'])
# elif target_arch in ['x86_64']:
# 	env.AppendUnique(CCFLAGS = ['-m64'])
# 	env.AppendUnique(LINKFLAGS = ['-m64'])
# elif target_arch in ['arm'] or target_arch.find('v5') > 0:
# 	env.AppendUnique(CPPFLAGS = ['-march=armv5te'])
# elif target_arch.find('v7a-hard') > 0:
# 	env.AppendUnique(CPPFLAGS = ['-march=armv7-a'])
# 	env.AppendUnique(CPPFLAGS = ['-mfloat-abi=hard'])
# 	env.AppendUnique(CCFLAGS = ['-mfloat-abi=hard'])
# 	env.AppendUnique(LINKFLAGS = ['-mfloat-abi=hard'])
# elif target_arch.find('v7a') > 0:
# 	env.AppendUnique(CPPFLAGS = ['-march=armv7-a'])
# elif target_arch.find('arm64') >= 0:
# 	env.AppendUnique(CPPFLAGS = ['-march=armv8-a'])

	# -I$/usr/include/mraa \

IOT_CXXFLAGS= -I. \
	-I./src \
	-I${JAVA_HOME}/include \
	-I${JAVA_HOME}/include/$(TARGET_OS) \
	-I${INSTALL_SYSROOT}/include \
	-I${IOTIVITY_HOME}/resource/csdk/connectivity/api \
	-I${IOTIVITY_HOME}/resource/include \
	-I${IOTIVITY_HOME}/resource/c_common \
	-I${IOTIVITY_HOME}/resource/csdk/stack/include \
	-I${IOTIVITY_HOME}/resource/csdk/logger/include \
	-I${IOTIVITY_HOME}/resource/csdk/stack/internal \
	-I${IOTIVITY_HOME}/resource/csdk/cjson \
	-I${IOTIVITY_HOME}/resource/oc_logger/include \
	-I${IOTIVITY_HOME}/resource/csdk/logger/include \
	-I${IOTIVITY_HOME}/resource/csdk/connectivity/lib/libcoap-4.1.1 \
	-I${IOTIVITY_HOME}/resource/csdk/security \
	-I${IOTIVITY_HOME}/resource/csdk/security/ocsecurity

	# -I${SDKTARGETSYSROOT}/usr/include/c++/4.9.1 \
	# -I${SDKTARGETSYSROOT}/usr/include/c++/4.9.1/i586-poky-linux

	# -I${IOTIVITY_HOME}/resource/c_common/oic_string/include \
	# -I${IOTIVITY_HOME}/resource/c_common/oic_malloc/include \
	# -I${IOTIVITY_HOME}/resource/../extlibs/boost/boost_1_58_0 \
	# -I${IOTIVITY_HOME}/resource/../build_common/android/compatibility \

	# -I${IOTIVITY_HOME}/resource/csdk/ocsocket/include \

# IOT_A=	liblua.a
# CORE_O= JniOcStack.o JniUtils.o JniEntityHandler.o JniOnResourceFoundListener.o \
# 	JniOnDeviceInfoListener.o JniOnPlatformInfoListener.o JniOnPresenceListener.o \
# 	JniOnGetListener.o JniOnPutListener.o JniOnPostListener.o JniOnDeleteListener.o \
# 	JniOnObserveListener.o JniOcRepresentation.o JniOcResourceHandle.o \
# 	JniOcPresenceHandle.o JniOcRequestHandle.o JniOcResourceRequest.o \
# 	JniOcResourceIdentifier.o JniOcSecurity.o \
# 	JniOcResourceResponse.o JniOcPlatform.o JniOcResource.o

# SEC=	JniOcSecureResource.o JniOcProvisioning.o JniSecureUtils.o \
# 	JniProvisionResultListner.o JniPinCheckListener.o JniDisplayPinListener.o

IOCHIBITY_O= \
	JniEntityHandler.o \
	JniOcDirectPairDevice.o \
	JniOcPlatform.o \
	JniOcPresenceHandle.o \
	JniOcRepresentation.o \
	JniOcRequestHandle.o \
	JniOcResource.o \
	JniOcResourceHandle.o \
	JniOcResourceIdentifier.o \
	JniOcResourceRequest.o \
	JniOcResourceResponse.o \
	JniOcSecurity.o \
	JniOcStack.o \
	JniOnDPDevicesFoundListener.o \
	JniOnDeleteListener.o \
	JniOnDeviceInfoListener.o \
	JniOnDirectPairingListener.o \
	JniOnGetListener.o \
	JniOnObserveListener.o \
	JniOnPlatformInfoListener.o \
	JniOnPostListener.o \
	JniOnPresenceListener.o \
	JniOnPutListener.o \
	JniOnResourceFoundListener.o \
	JniUtils.o \

IOTSEC=	JniOcSecureResource.o \
	JniOcProvisioning.o \
	JniDisplayPinListener.o \
	JniPinCheckListener.o \
	JniProvisionResultListner.o \
	JniSecureUtils.o

# ble not yet supported:
# JniCaInterface.o \


# Targets start here.
# default: $(PLAT)

BASE_O= $(IOCHIBITY_O)

#$(IOTSEC)

# Convenience targets for popular platforms
# ALL= all

all:	$(BASE_O)

ALL=all

# NB: do not change the order of the CORE_O files and the libs:
linux:	check-env
	@echo "Making Linux"
	$(MAKE) -f legacy.mk $(ALL)
	g++ -o $(BUILD_SYSROOT)/libiotivity-jni$(JNILIBSUFFIX) \
	-shared \
	-L. $(IOCHIBITY_O) \
	-L$(INSTALL_SYSROOT)/lib \
	$(IOTLIBS)

# -flat_namespace

# all:	$(BASE_O)

clean:
	$(RM) $(BASE_O)
	$(RM) *dylib *jnilib

# make may get confused with test/ and install/
dummy:

test:	dummy
	@echo test?

install: dummy
	$(MKDIR) $(INSTALL_LIB) $(INSTALL_JNI)
	$(INSTALL_EXEC) $(TO_LIB) $(INSTALL_JNI)

	# -DlocalRepositoryPath=$(MVN_REPO)

	# cd src && $(INSTALL_EXEC) $(TO_BIN) $(INSTALL_BIN)
	# cd src && $(INSTALL_DATA) $(TO_INC) $(INSTALL_INC)
	# cd doc && $(INSTALL_DATA) $(TO_MAN) $(INSTALL_MAN)

uninstall:
	cd src && cd $(INSTALL_LIB) && $(RM) $(TO_LIB)

	# cd src && cd $(INSTALL_BIN) && $(RM) $(TO_BIN)
	# cd src && cd $(INSTALL_INC) && $(RM) $(TO_INC)
	# cd doc && cd $(INSTALL_MAN) && $(RM) $(TO_MAN)

local:
	$(MAKE) install INSTALL_TOP=../install

# depend:
# 	@$(CC) $(CFLAGS) -MM l*.c

echo:	check-env
	@echo "HOST= $(IOTIVITY_HOST_OS)"
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(SYSLDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"
	@echo "SHLIBSUFFIX= $(SHLIBSUFFIX)"
	@echo "JNILIBSUFFIX= $(JNILIBSUFFIX)"


# list targets that do not create files (but not all makes understand .PHONY)
# .PHONY: all $(PLATS) default o a clean depend echo none
.PHONY: o a clean dummy test

check-env:
ifeq ( $($@), "darwin")
    JNILIBSUFFIX = '.jnilib'
    SHLIBSUFFIX = '.dylib'
endif
ifndef IOTIVITY_HOME
	$(error IOTIVITY_HOME is undefined)
endif
# ifndef INSTALL_SYSROOT
# 	$(error INSTALL_SYSROOT is undefined)
# endif
ifeq ($(IOTIVITY_HOST_OS),'linux')
    SHLIBSUFFIX = '.so'
    JNILIBSUFFIX = '.so'
endif

# ifeq ($(STAGE),'release')
# MYCFLAGS += -O2
# else
# MYCFLAGS += -g
# endif



# DO NOT DELETE

# (end of Makefile)
