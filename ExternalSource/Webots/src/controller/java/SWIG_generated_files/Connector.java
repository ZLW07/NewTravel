/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.cyberbotics.webots.controller;

public class Connector extends Device {
  private transient long swigCPtr;

  protected Connector(long cPtr, boolean cMemoryOwn) {
    super(wrapperJNI.Connector_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Connector obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        wrapperJNI.delete_Connector(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Connector(String name) {
    this(wrapperJNI.new_Connector(name), true);
  }

  public void enablePresence(int samplingPeriod) {
    wrapperJNI.Connector_enablePresence(swigCPtr, this, samplingPeriod);
  }

  public void disablePresence() {
    wrapperJNI.Connector_disablePresence(swigCPtr, this);
  }

  public int getPresenceSamplingPeriod() {
    return wrapperJNI.Connector_getPresenceSamplingPeriod(swigCPtr, this);
  }

  public int getPresence() {
    return wrapperJNI.Connector_getPresence(swigCPtr, this);
  }

  public boolean isLocked() {
    return wrapperJNI.Connector_isLocked(swigCPtr, this);
  }

  public void lock() {
    wrapperJNI.Connector_lock(swigCPtr, this);
  }

  public void unlock() {
    wrapperJNI.Connector_unlock(swigCPtr, this);
  }

}
