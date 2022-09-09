/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.cyberbotics.webots.controller;

public class LidarPoint {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected LidarPoint(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(LidarPoint obj) {
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
        wrapperJNI.delete_LidarPoint(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setX(float value) {
    wrapperJNI.LidarPoint_x_set(swigCPtr, this, value);
  }

  public float getX() {
    return wrapperJNI.LidarPoint_x_get(swigCPtr, this);
  }

  public void setY(float value) {
    wrapperJNI.LidarPoint_y_set(swigCPtr, this, value);
  }

  public float getY() {
    return wrapperJNI.LidarPoint_y_get(swigCPtr, this);
  }

  public void setZ(float value) {
    wrapperJNI.LidarPoint_z_set(swigCPtr, this, value);
  }

  public float getZ() {
    return wrapperJNI.LidarPoint_z_get(swigCPtr, this);
  }

  public void setLayer_id(int value) {
    wrapperJNI.LidarPoint_layer_id_set(swigCPtr, this, value);
  }

  public int getLayer_id() {
    return wrapperJNI.LidarPoint_layer_id_get(swigCPtr, this);
  }

  public void setTime(float value) {
    wrapperJNI.LidarPoint_time_set(swigCPtr, this, value);
  }

  public float getTime() {
    return wrapperJNI.LidarPoint_time_get(swigCPtr, this);
  }

  public double getLayerId() {
    return wrapperJNI.LidarPoint_getLayerId(swigCPtr, this);
  }

  public LidarPoint() {
    this(wrapperJNI.new_LidarPoint(), true);
  }

}
