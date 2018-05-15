/**
 * @file openocf_utils_EndPoint.c
 * @author Gregg Reynolds
 * @date December 2016
 *
 * @brief JNI implementation of EndPoint Java API (OCDevAddr)
 */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "_threads.h"

#include "openocf_utils_Endpoint.h"
#include "openocf_utils_Endpoint.ids.h"
#include "jni_utils.h"
#include "jni_init.h"
#include "org_iochibity_Exceptions.h"

#include "openocf.h"
/* #include "oic_malloc.h" */
/* #include "ocpayload.h" */
/* #include "ocresource.h" */
/* #include "ocresourcehandler.h" */
/* #include "ocstack.h" */

/* Endpoint = OCDevAddr */
jclass    K_ENDPOINT                      = NULL;
jmethodID MID_EP_CTOR                     = NULL;
jfieldID  FID_EP_HANDLE         = NULL;

jfieldID  FID_EP_NETWORK_FLAGS            = NULL;
jfieldID  FID_EP_NETWORK_POLICIES         = NULL;
jfieldID  FID_EP_NETWORK_SCOPE            = NULL;
jfieldID  FID_EP_TRANSPORT_SECURITY       = NULL;
jfieldID  FID_EP_PORT                     = NULL;
jfieldID  FID_EP_ADDRESS                  = NULL;
jfieldID  FID_EP_IFINDEX                  = NULL;
jfieldID  FID_EP_ROUTE_DATA               = NULL;


init_Endpoint(JNIEnv* env)
{
    jclass klass = NULL;

    if (K_ENDPOINT == NULL) {
	klass = (*env)->FindClass(env, FQCN_ENDPOINT); // "openocf/utils/Endpoint");
	JNI_ASSERT_NULL(klass, FINDCLASS_FAIL(FQCN_ENDPOINT), 0);
	K_ENDPOINT = (jclass)(*env)->NewGlobalRef(env, klass);
	(*env)->DeleteLocalRef(env, klass);
    }
    MID_EP_CTOR = (*env)->GetMethodID(env, K_ENDPOINT, "<init>", "()V");
    if (MID_EP_CTOR == 0) {
	printf("ERROR: GetMethodID failed for ctor of Endpoint.\n");
	return -1;
    }

    FID_EP_HANDLE = (*env)->GetFieldID(env, K_ENDPOINT, "_handle", "J");
    JNI_ASSERT_NULL(FID_EP_HANDLE,
			ERR_MSG(ERR_FLD, "Endpoint._handle"), -1);
    }

    /* FID_EP_NETWORK_FLAGS = (*env)->GetFieldID(env, K_ENDPOINT, "networkFlags", "I"); */
    /* if (FID_EP_NETWORK_FLAGS == NULL) { */
    /* 	printf("ERROR:  GetFieldID failed for networkFlags for Endpoint\n"); */
    /* 	fflush(NULL); */
    /* 	return OC_EH_INTERNAL_SERVER_ERROR; */
    /* } */
    /* FID_EP_NETWORK_POLICIES= (*env)->GetFieldID(env, K_ENDPOINT, "networkPolicies", "B"); */
    /* if (FID_EP_NETWORK_POLICIES == NULL) { */
    /* 	printf("ERROR:  GetFieldID failed for 'networkPolicy' of Endpoint\n"); */
    /* 	fflush(NULL); */
    /* 	return OC_EH_INTERNAL_SERVER_ERROR; */
    /* } */
    /* FID_EP_NETWORK_SCOPE= (*env)->GetFieldID(env, K_ENDPOINT, "networkScope", "B"); */
    /* if (FID_EP_NETWORK_SCOPE == NULL) { */
    /* 	printf("ERROR:  GetFieldID failed for 'networkPolicy' of Endpoint\n"); */
    /* 	fflush(NULL); */
    /* 	return OC_EH_INTERNAL_SERVER_ERROR; */
    /* } */
    /* FID_EP_TRANSPORT_SECURITY= (*env)->GetFieldID(env, K_ENDPOINT, "transportSecurity", "Z"); */
    /* if (FID_EP_TRANSPORT_SECURITY == NULL) { */
    /* 	printf("ERROR:  GetFieldID failed for 'transportSecurity' of Endpoint\n"); */
    /* 	fflush(NULL); */
    /* 	return OC_EH_INTERNAL_SERVER_ERROR; */
    /* } */
    /* FID_EP_PORT = (*env)->GetFieldID(env, K_ENDPOINT, "port", "I"); */
    /* if (FID_EP_PORT == NULL) { */
    /* 	printf("ERROR:  GetFieldID failed for port for Endpoint\n"); */
    /* 	fflush(NULL); */
    /* 	return OC_EH_INTERNAL_SERVER_ERROR; */
    /* } */
    /* FID_EP_ADDRESS = (*env)->GetFieldID(env, K_ENDPOINT, "address", "Ljava/lang/String;"); */
    /* if (FID_EP_ADDRESS == NULL) { */
    /* 	printf("ERROR:  GetFieldID failed for address of Endpoint\n"); */
    /* 	fflush(NULL); */
    /* 	return OC_EH_INTERNAL_SERVER_ERROR; */
    /* } */
    /* FID_EP_IFINDEX = (*env)->GetFieldID(env, K_ENDPOINT, "ifindex", "I"); */
    /* if (FID_EP_IFINDEX == NULL) { */
    /* 	printf("ERROR:  GetFieldID failed for ifindex Endpoint\n"); */
    /* 	fflush(NULL); */
    /* 	return OC_EH_INTERNAL_SERVER_ERROR; */
    /* } */
    /* FIXME */
    /* /\* OCDevAddr.routeData *\/ */
    /* if (crequest_in->devAddr.routeData) { */
    /* FID_EP_ROUTE_DATA = (*env)->GetFieldID(env, K_ENDPOINT, "routeData", "Ljava/lang/String;"); */
    /* if (FID_EP_ROUTE_DATA == NULL) { */
    /* 	    printf("ERROR: GetFieldID failed routeData of Endpoint\n"); */
    /* } */



/*
 * Class:     openocf_utils_EndPoint
 * Method:    networkProtocol
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_openocf_utils_EndPoint_networkProtocol
(JNIEnv * env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);
  if (tls_response_in == NULL) {
    // FIXME: if our TLS var has not been initialized, we have not
    // recieved a discovery response containing the remote
    // EndPoint info.
    // FIXME: return multicast info?
    return -1;
  } else {
    return RESPONSE_IN->devAddr.adapter;
  }
}

/*
 * Class:     openocf_utils_EndPoint
 * Method:    networkFlags
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_openocf_utils_EndPoint_networkFlags
(JNIEnv * env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);
  if (tls_response_in == NULL) {
    return -1;
  } else {
    return RESPONSE_IN->devAddr.flags;
  }
}

/*
 * Class:     openocf_utils_EndPoint
 * Method:    networkScope
 * Signature: ()B
 */
JNIEXPORT jbyte JNICALL Java_openocf_utils_EndPoint_networkScope
(JNIEnv * env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);
  if (tls_response_in == NULL) {
    return -1;
  } else {
    return RESPONSE_IN->devAddr.flags & 0x0F;
  }
}

/*
 * Class:     openocf_utils_EndPoint
 * Method:    transportIsSecure
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_EndPoint_transportIsSecure
(JNIEnv * env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);
  if (tls_response_in == NULL) {
    return false;
  } else {
    return  RESPONSE_IN->devAddr.flags & 0x0010;	/* (1 << 4) */
  }
}

/*
 * Class:     openocf_utils_EndPoint
 * Method:    isIPv6
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_EndPoint_isIPv6
(JNIEnv * env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);
  if (tls_response_in == NULL) {
    return false;
  } else {
    return  RESPONSE_IN->devAddr.flags & 0x0020;	/* (1 << 5) */
  }
}

/*
 * Class:     openocf_utils_EndPoint
 * Method:    isIPv4
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_EndPoint_isIPv4
(JNIEnv * env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);
  if (tls_response_in == NULL) {
    return false;
  } else {
    return  RESPONSE_IN->devAddr.flags & 0x0040;	/* (1 << 6) */
  }
}

/*
 * Class:     openocf_utils_EndPoint
 * Method:    isMulticast
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_EndPoint_isMulticast
(JNIEnv * env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);
  if (tls_response_in == NULL) {
    return false;
  } else {
    return RESPONSE_IN->devAddr.flags & 0x0080;	/* (1 << 7) */
  }
}


/*
 * Class:     openocf_utils_EndPoint
 * Method:    port
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_openocf_utils_EndPoint_port
(JNIEnv * env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);
  if (tls_response_in == NULL) {
    return -1;
  } else {
    return RESPONSE_IN->devAddr.port;
  }
}

/*
 * Class:     openocf_utils_EndPoint
 * Method:    ipAddress
 * Signature: ()Ljava/lang/String;
 */
 jstring JNICALL Java_openocf_utils_EndPoint_ipAddress
(JNIEnv * env, jobject this)
{
    OC_UNUSED(env);
    OC_UNUSED(this);
    /* printf("%s : %s ENTRY, %d\n", __FILE__, __func__, (intptr_t)THREAD_ID); */
    /* printf("TLS: %d\n", tls_response_in); */

    if (tls_response_in) {
	return(*env)->NewStringUTF(env, RESPONSE_IN->devAddr.addr);
    } else {
	// FIXME: if our TLS var has not been initialized, we have not
	// recieved a discovery response containing the remote
	// EndPoint info.
	printf("FIXME: implement %s\n", __func__);
	return NULL;
    }
}

/*
 * Class:     openocf_utils_EndPoint
 * Method:    ifindex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_openocf_utils_EndPoint_ifindex
(JNIEnv * env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);
  if (tls_response_in == NULL) {
    return -1;
  } else {
    return RESPONSE_IN->devAddr.ifindex;
  }
}

/*
 * Class:     openocf_utils_EndPoint
 * Method:    routeData
 * Signature: ()Ljava/lang/String;
 */
/* JNIEXPORT jstring JNICALL Java_openocf_utils_EndPoint_routeData */
/* (JNIEnv * env, jobject this) */
/* { */
/*   OC_UNUSED(env); */
/*   OC_UNUSED(this); */
/*   return RESPONSE_IN->routeData; */
/* } */

/*
 * Class:     openocf_utils_Endpoint
 * Method:    getIPAddress
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_openocf_utils_Endpoint_getIPAddress
(JNIEnv *env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);

  OCDevAddr *ep = (*env)->GetLongField(env, this, FID_EP_HANDLE);

  return(*env)->NewStringUTF(env, ep->addr);
}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setIPAddress
 * Signature: (Ljava/lang/String;)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setIPAddress
(JNIEnv *env, jobject this, jstring j_ipaddr){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    getBLEAddress
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_openocf_utils_Endpoint_getBLEAddress
(JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    getPort
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_openocf_utils_Endpoint_getPort
(JNIEnv *env, jobject this)
{
  OC_UNUSED(env);
  OC_UNUSED(this);

  OCDevAddr *ep = (*env)->GetLongField(env, this, FID_EP_HANDLE);

  return ep->port;
}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setPort
 * Signature: (I)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setPort
(JNIEnv *env, jobject this, jint j_port){}

/* /\* */
/*  * Class:     openocf_utils_Endpoint */
/*  * Method:    getNetworkAdapter */
/*  * Signature: ()I */
/*  *\/ */
/* JNIEXPORT jint JNICALL Java_openocf_utils_Endpoint_getNetworkAdapter */
/*   (JNIEnv *env, jobject); */

/* /\* */
/*  * Class:     openocf_utils_Endpoint */
/*  * Method:    getNetworkFlags */
/*  * Signature: ()I */
/*  *\/ */
/* JNIEXPORT jint JNICALL Java_openocf_utils_Endpoint_getNetworkFlags */
/*   (JNIEnv *env, jobject); */

/* /\* */
/*  * Class:     openocf_utils_Endpoint */
/*  * Method:    isTransportSecure */
/*  * Signature: ()Z */
/*  *\/ */
/* JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isTransportSecure */
/*   (JNIEnv *env, jobject); */

/* /\* */
/*  * Class:     openocf_utils_Endpoint */
/*  * Method:    setTransportSecure */
/*  * Signature: (Z)Lopenocf/utils/Endpoint; */
/*  *\/ */
/* JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setTransportSecure */
/*   (JNIEnv *env, jobject, jboolean); */

/* /\* */
/*  * Class:     openocf_utils_Endpoint */
/*  * Method:    isTransportUDP */
/*  * Signature: ()Z */
/*  *\/ */
/* JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isTransportUDP */
/*   (JNIEnv *env, jobject); */

/* /\* */
/*  * Class:     openocf_utils_Endpoint */
/*  * Method:    setTransportUDP */
/*  * Signature: (Z)Lopenocf/utils/Endpoint; */
/*  *\/ */
/* JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setTransportUDP */
/*   (JNIEnv *env, jobject, jboolean); */

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isTransportTCP
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isTransportTCP
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setTransportTCP
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setTransportTCP
  (JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isTransportGATT
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isTransportGATT
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setTransportGATT
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setTransportGATT
  (JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isTransportRFCOMM
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isTransportRFCOMM
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setTransportRFCOMM
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setTransportRFCOMM
(JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isTransportNFC
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isTransportNFC
  (JNIEnv *env, jobject this){}
/*
 * Class:     openocf_utils_Endpoint
 * Method:    setTransportNFC
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setTransportNFC
  (JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    getAdapter
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_openocf_utils_Endpoint_getAdapter
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isNetworkIP
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isNetworkIP
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isNetworkIPv4
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isNetworkIPv4
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setNetworkIPv4
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setNetworkIPv4
  (JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isNetworkIPv6
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isNetworkIPv6
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setNetworkIPv6
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setNetworkIPv6
(JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    getNetworkScope
 * Signature: ()B
 */
JNIEXPORT jbyte JNICALL Java_openocf_utils_Endpoint_getNetworkScope
(JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isScopeInterface
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isScopeInterface
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setScopeInterface
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setScopeInterface
  (JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isScopeLink
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isScopeLink
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setScopeLink
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setScopeLink
  (JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isScopeRealm
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isScopeRealm
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setScopeRealm
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setScopeRealm
  (JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isScopeAdmin
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isScopeAdmin
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setScopeAdmin
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setScopeAdmin
  (JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isScopeSite
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isScopeSite
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setScopeSite
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setScopeSite
(JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isScopeOrg
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isScopeOrg
(JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setScopeOrg
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setScopeOrg
(JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isScopeGlobal
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isScopeGlobal
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setScopeGlobal
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setScopeGlobal
  (JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    isRoutingMulticast
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_openocf_utils_Endpoint_isRoutingMulticast
  (JNIEnv *env, jobject this){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    setRoutingMulticast
 * Signature: (Z)Lopenocf/utils/Endpoint;
 */
JNIEXPORT jobject JNICALL Java_openocf_utils_Endpoint_setRoutingMulticast
(JNIEnv *env, jobject this, jboolean j_torf){}

/*
 * Class:     openocf_utils_Endpoint
 * Method:    getIfIndex
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_openocf_utils_Endpoint_getIfIndex
  (JNIEnv *env, jobject this)
{}