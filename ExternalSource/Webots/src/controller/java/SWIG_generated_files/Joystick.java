/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.cyberbotics.webots.controller;

public class Joystick {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Joystick(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Joystick obj) {
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
        wrapperJNI.delete_Joystick(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Joystick() {
    this(wrapperJNI.new_Joystick(), true);
  }

  public void enable(int samplingPeriod) {
    wrapperJNI.Joystick_enable(swigCPtr, this, samplingPeriod);
  }

  public void disable() {
    wrapperJNI.Joystick_disable(swigCPtr, this);
  }

  public int getSamplingPeriod() {
    return wrapperJNI.Joystick_getSamplingPeriod(swigCPtr, this);
  }

  public boolean isConnected() {
    return wrapperJNI.Joystick_isConnected(swigCPtr, this);
  }

  public String getModel() {
    return wrapperJNI.Joystick_getModel(swigCPtr, this);
  }

  public int getNumberOfAxes() {
    return wrapperJNI.Joystick_getNumberOfAxes(swigCPtr, this);
  }

  public int getAxisValue(int axis) {
    return wrapperJNI.Joystick_getAxisValue(swigCPtr, this, axis);
  }

  public int getNumberOfPovs() {
    return wrapperJNI.Joystick_getNumberOfPovs(swigCPtr, this);
  }

  public int getPovValue(int pov) {
    return wrapperJNI.Joystick_getPovValue(swigCPtr, this, pov);
  }

  public int getPressedButton() {
    return wrapperJNI.Joystick_getPressedButton(swigCPtr, this);
  }

  public void setConstantForce(int level) {
    wrapperJNI.Joystick_setConstantForce(swigCPtr, this, level);
  }

  public void setConstantForceDuration(double duration) {
    wrapperJNI.Joystick_setConstantForceDuration(swigCPtr, this, duration);
  }

  public void setAutoCenteringGain(double gain) {
    wrapperJNI.Joystick_setAutoCenteringGain(swigCPtr, this, gain);
  }

  public void setResistanceGain(double gain) {
    wrapperJNI.Joystick_setResistanceGain(swigCPtr, this, gain);
  }

  public void setForceAxis(int axis) {
    wrapperJNI.Joystick_setForceAxis(swigCPtr, this, axis);
  }

}
