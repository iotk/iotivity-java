/*
 *******************************************************************
 *
 * Copyright 2015 Intel Corporation.
 *
 *-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
 */
package org.iotivity.base.examples.minimal.server;

import org.iotivity.base.EntityHandlerResult;
import org.iotivity.base.ErrorCode;
import org.iotivity.base.ObservationInfo;
import org.iotivity.base.OcException;
import org.iotivity.base.OcPlatform;
import org.iotivity.base.OcRepresentation;
import org.iotivity.base.OcResource;
import org.iotivity.base.OcResourceHandle;
import org.iotivity.base.OcResourceRequest;
import org.iotivity.base.OcResourceResponse;
import org.iotivity.base.RequestHandlerFlag;
import org.iotivity.base.RequestType;
import org.iotivity.base.ResourceProperty;

import java.util.EnumSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/**
 * Light
 * <p/>
 * This class represents a light resource
 */
public class Light implements OcPlatform.EntityHandler {
    private static final String NAME_KEY = "name";
    private static final String STATE_KEY = "state";
    private static final String POWER_KEY = "power";

    private String mResourceUri;                //resource URI
    private String mResourceTypeName;           //resource type name.
    private String mResourceInterface;          //resource interface.
    private OcResourceHandle mResourceHandle;   //resource handle

    private String mName;                       //light name
    private boolean mState;                     //light state
    private int mPower;                         //light power

    public Light(String resourceUri, String name, boolean state, int power) {
        mResourceUri = resourceUri;
        mResourceTypeName = "core.light";
        mResourceInterface = OcPlatform.DEFAULT_INTERFACE;
        mResourceHandle = null; //this is set when resource is registered

        mName = name;
        mState = state;
        mPower = power;
    }

    public synchronized void registerResource() throws OcException {
        if (null == mResourceHandle) {
            mResourceHandle = OcPlatform.registerResource(
                    mResourceUri,
                    mResourceTypeName,
                    mResourceInterface,
                    this,
                    EnumSet.of(ResourceProperty.DISCOVERABLE, ResourceProperty.OBSERVABLE)
            );
        }
    }

    /**
     * NOTE: This is just a sample implementation of entity handler. Entity handler can be
     * implemented in several ways by the manufacturer.
     *
     * @param request
     * @return
     */
    @Override
    public synchronized EntityHandlerResult handleEntity(final OcResourceRequest request) {
	msg("handleEntity");
	msg("\tRequest Type:    " + request.getRequestType());
	msg("\tResource URI:    " + request.getResourceUri());
	msg("\tResource Handle: " + request.getResourceHandle());
        EntityHandlerResult ehResult = EntityHandlerResult.ERROR;
        if (null == request) {
            msg("Server request is invalid");
            return ehResult;
        }

	Map<String, String> queries = request.getQueryParameters();
        if (!queries.isEmpty()) {
            msg("\tQuery Params: ");
        } else {
            msg("\tQuery Params: none");
        }

        // Get the request flags
        EnumSet<RequestHandlerFlag> requestFlags = request.getRequestHandlerFlagSet();
        if (requestFlags.contains(RequestHandlerFlag.INIT)) {
            msg("\tRequest Flag: Init");
            ehResult = EntityHandlerResult.OK;
        }
        if (requestFlags.contains(RequestHandlerFlag.REQUEST)) {
            msg("\tRequest Flag: Request");
            ehResult = handleRequest(request);
        }
        if (requestFlags.contains(RequestHandlerFlag.OBSERVER)) {
            msg("\tRequest Flag: Observer");
            ehResult = handleObserver(request);
        }

        return ehResult;
    }

    private EntityHandlerResult handleRequest(OcResourceRequest request) {
	msg("  ..handleRequest");
        EntityHandlerResult ehResult = EntityHandlerResult.ERROR;
        // Check for query params (if any)
        Map<String, String> queries = request.getQueryParameters();
        // if (!queries.isEmpty()) {
        //     msg("Query processing is up to entityHandler");
        // } else {
        //     msg("No query parameters in this request");
        // }

        for (Map.Entry<String, String> entry : queries.entrySet()) {
            msg("Query key: " + entry.getKey() + " value: " + entry.getValue());
        }

        //Get the request type
        RequestType requestType = request.getRequestType();
        switch (requestType) {
            case GET:
                // msg("\tRequest Type is GET");
                ehResult = handleGetRequest(request);
                break;
            case PUT:
                // msg("\tRequest Type is PUT");
                ehResult = handlePutRequest(request);
                break;
            case POST:
                // msg("\tRequest Type is POST");
                ehResult = handlePostRequest(request);
                break;
            case DELETE:
                // msg("\tRequest Type is DELETE");
                ehResult = handleDeleteRequest();
                break;
        }
        return ehResult;
    }

    private EntityHandlerResult handleGetRequest(final OcResourceRequest request) {
	msg("  ....handleGetRequest");
        EntityHandlerResult ehResult;
        OcResourceResponse response = new OcResourceResponse();
        response.setRequestHandle(request.getRequestHandle());
        response.setResourceHandle(request.getResourceHandle());

        if (mIsSlowResponse) { // Slow response case
            new Thread(new Runnable() {
                public void run() {
                    handleSlowResponse(request);
                }
            }).start();
            ehResult = EntityHandlerResult.SLOW;
        } else { // normal response case.
            response.setErrorCode(SUCCESS);
            response.setResponseResult(EntityHandlerResult.OK);
            response.setResourceRepresentation(getOcRepresentation());
            ehResult = sendResponse(response);
        }
        return ehResult;
    }

    private EntityHandlerResult handlePutRequest(OcResourceRequest request) {
    	msg("  ....handlePutRequest");
	OcResourceResponse response = new OcResourceResponse();
        response.setRequestHandle(request.getRequestHandle());
        response.setResourceHandle(request.getResourceHandle());

        setOcRepresentation(request.getResourceRepresentation());
        response.setResourceRepresentation(getOcRepresentation());
        response.setResponseResult(EntityHandlerResult.OK);
        response.setErrorCode(SUCCESS);
        return sendResponse(response);
    }

    private static int sUriCounter = 1;
    private EntityHandlerResult handlePostRequest(OcResourceRequest request) {
	msg("  ....handlePostRequest");
        OcResourceResponse response = new OcResourceResponse();
        response.setRequestHandle(request.getRequestHandle());
        response.setResourceHandle(request.getResourceHandle());
        String newUri = "/a/light" + (++sUriCounter);
        SimpleServer.createNewLightResource(newUri, "John's light " + sUriCounter);
	msg("        new uri: " + newUri);
        OcRepresentation rep_post = getOcRepresentation();
        try {
            rep_post.setValue(OcResource.CREATED_URI_KEY, newUri);
        } catch (OcException e) {
            msgError(TAG, e.toString());
        }
        response.setResourceRepresentation(rep_post);
        response.setErrorCode(SUCCESS);
        response.setNewResourceUri(newUri);
        response.setResponseResult(EntityHandlerResult.RESOURCE_CREATED);
        return sendResponse(response);
    }

    private EntityHandlerResult handleDeleteRequest() {
	msg("  ....handleDeleteRequest");
        try {
            this.unregisterResource();
            return EntityHandlerResult.RESOURCE_DELETED;
        } catch (OcException e) {
            msgError(TAG, e.toString());
            msg("Failed to unregister a light resource");
            return EntityHandlerResult.ERROR;
        }
    }

    private void handleSlowResponse(OcResourceRequest request) {
	msg("  ....handleSlowResponse");
        sleep(10);
        msg("Sending slow response...");
        OcResourceResponse response = new OcResourceResponse();
        response.setRequestHandle(request.getRequestHandle());
        response.setResourceHandle(request.getResourceHandle());

        response.setErrorCode(SUCCESS);
        response.setResponseResult(EntityHandlerResult.OK);
        response.setResourceRepresentation(getOcRepresentation());
        sendResponse(response);
    }

    private List<Byte> mObservationIds; //IDs of observes

    private EntityHandlerResult handleObserver(final OcResourceRequest request) {
	msg("  ....handleObserver");
        ObservationInfo observationInfo = request.getObservationInfo();
        switch (observationInfo.getObserveAction()) {
            case REGISTER:
		msg("\t\tObserve Action: REGISTER");
                if (null == mObservationIds) {
                    mObservationIds = new LinkedList<>();
                }
                mObservationIds.add(observationInfo.getOcObservationId());
                break;
            case UNREGISTER:
		msg("\t\tObserve Action: UNREGISTER");
                mObservationIds.remove((Byte)observationInfo.getOcObservationId());
                break;
        }
        // Observation happens on a different thread in notifyObservers method.
        // If we have not created the thread already, we will create one here.
        if (null == mObserverNotifier) {
            mObserverNotifier = new Thread(new Runnable() {
                public void run() {
                    notifyObservers(request);
                }
            });
            mObserverNotifier.start();
        }
        return EntityHandlerResult.OK;
    }

    private void notifyObservers(OcResourceRequest request) {
        while (true) {
            // increment current power value by 10 every 2 seconds
            mPower += 10;
            sleep(2);
	    System.out.println("");
            try {
                if (mIsListOfObservers) {
		    msg("Notifying list of observers...");
                    OcResourceResponse response = new OcResourceResponse();
                    response.setErrorCode(SUCCESS);
                    response.setResourceRepresentation(getOcRepresentation());
                    OcPlatform.notifyListOfObservers(
                            mResourceHandle,
                            mObservationIds,
                            response);
                } else {
		    msg("Notifying all observers...");
                    OcPlatform.notifyAllObservers(mResourceHandle);
                }
            } catch (OcException e) {
                ErrorCode errorCode = e.getErrorCode();
                if (ErrorCode.NO_OBSERVERS == errorCode) {
                    msg("No more observers, stopping notifications");
                }
                return;
            }
	    printThis();
	    msg("Notification completed");
        }
    }

    private EntityHandlerResult sendResponse(OcResourceResponse response) {
        try {
            OcPlatform.sendResponse(response);
            return EntityHandlerResult.OK;
        } catch (OcException e) {
            msgError(TAG, e.toString());
            msg("Failed to send response");
            return EntityHandlerResult.ERROR;
        }
    }

    public synchronized void unregisterResource() throws OcException {
	msg("unregisterResource");
        if (null != mResourceHandle) {
            OcPlatform.unregisterResource(mResourceHandle);
        }
    }

    public void setOcRepresentation(OcRepresentation rep) {
        try {
            if (rep.hasAttribute(NAME_KEY)) mName = rep.getValue(NAME_KEY);
            if (rep.hasAttribute(STATE_KEY)) mState = rep.getValue(STATE_KEY);
            if (rep.hasAttribute(POWER_KEY)) mPower = rep.getValue(POWER_KEY);
        } catch (OcException e) {
            msgError(TAG, e.toString());
            msg("Failed to get representation values");
        }
    }

    public OcRepresentation getOcRepresentation() {
        OcRepresentation rep = new OcRepresentation();
        try {
            rep.setValue(NAME_KEY, mName);
            rep.setValue(STATE_KEY, mState);
            rep.setValue(POWER_KEY, mPower);
        } catch (OcException e) {
            msgError(TAG, e.toString());
            msg("Failed to set representation values");
        }
        return rep;
    }

    //******************************************************************************
    // End of the OIC specific code
    //******************************************************************************

    public void setSlowResponse(boolean isSlowResponse) {
        mIsSlowResponse = isSlowResponse;
    }

    public void useListOfObservers(boolean isListOfObservers) {
        mIsListOfObservers = isListOfObservers;
    }

    public void printThis() {
	msg("THIS:");
        msg("\t" + "URI" + ": " + mResourceUri);
	msg("\t" + NAME_KEY + ": " + mName);
	msg("\t" + STATE_KEY + ": " + mState);
	msg("\t" + POWER_KEY + ": " + mPower);
    }

    private void sleep(int seconds) {
        try {
            Thread.sleep(seconds * 1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
            msgError(TAG, e.toString());
        }
    }

    // private void msg(String text) {
    //         SimpleServer.msg(text);
    // }

    public static void msg(final String text) {
        System.out.println("[O]" + TAG + " | " + text);
    }

    public static void msg(final String tag, final String text) {
        System.out.println("[O]" + tag + " | " + text);
    }

    public static void msgError(final String tag ,final String text) {
        System.out.println("[E]" + tag + " | " + text);
    }

   // private void msgError(String tag, String text) {
   //          SimpleServer.msgError(tag, text);
   //  }

    private final static String TAG = Light.class.getSimpleName();
    private final static int SUCCESS = 200;
    private boolean mIsSlowResponse = false;
    private boolean mIsListOfObservers = false;
    private Thread mObserverNotifier;
}
