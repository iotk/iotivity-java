package org.iochibity;

import java.util.List;

// All methods EXCEPT observeStimulus implemented by ServiceProvider abstract class
public interface IServiceProvider {

    public long                   getHandle(); // OCResource*

    // black boxing
    public void             exhibit();  // Behavior(); // called by user
    // observeStimulus: implemented by user, called by stack
    // abstract public int            observeStimulus(StimulusIn stimulusIn);
    public void             react(); // called by stack

    // OCResource fields
    public InstanceId             getInstanceId();

    public String                 getUriPath();
    public void                   setUriPath(String theUri);

    public List<String>           getTypes();
    public boolean                addType(String t);

    public List<String>           getInterfaces();
    public boolean                addInterface(String iface);

    public PropertyMap            getProperties();
    public Object                 putProperty(String key, Object val);

    public List<IServiceProvider> getChildren();

    // OCResource uint32_t sequenceNum -out of place, this is a Message serial
    // public int          getSerial();      // for observables, https://tools.ietf.org/html/rfc7641

    public List<ActionSet>        getActionSet();
    public int                    getPolicies(); // ???

    // from incoming request:
    public int              method();
    
}

