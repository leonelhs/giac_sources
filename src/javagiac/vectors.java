/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.6
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package javagiac;

public class vectors {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected vectors(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(vectors obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        giacJNI.delete_vectors(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public vectors() {
    this(giacJNI.new_vectors__SWIG_0(), true);
  }

  public vectors(long n) {
    this(giacJNI.new_vectors__SWIG_1(n), true);
  }

  public long size() {
    return giacJNI.vectors_size(swigCPtr, this);
  }

  public long capacity() {
    return giacJNI.vectors_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    giacJNI.vectors_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return giacJNI.vectors_isEmpty(swigCPtr, this);
  }

  public void clear() {
    giacJNI.vectors_clear(swigCPtr, this);
  }

  public void add(String x) {
    giacJNI.vectors_add(swigCPtr, this, x);
  }

  public String get(int i) {
    return giacJNI.vectors_get(swigCPtr, this, i);
  }

  public void set(int i, String val) {
    giacJNI.vectors_set(swigCPtr, this, i, val);
  }

}
