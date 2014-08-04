/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: /Users/deyuandeng/Documents/Computer_Science/Android/Learning_Android - Book/LogClient/src/com/marakana/logservice/ILogService.aidl
 */
package com.marakana.logservice;
public interface ILogService extends android.os.IInterface
{
/** Local-side IPC implementation stub class. */
public static abstract class Stub extends android.os.Binder implements com.marakana.logservice.ILogService
{
private static final java.lang.String DESCRIPTOR = "com.marakana.logservice.ILogService";
/** Construct the stub at attach it to the interface. */
public Stub()
{
this.attachInterface(this, DESCRIPTOR);
}
/**
 * Cast an IBinder object into an com.marakana.logservice.ILogService interface,
 * generating a proxy if needed.
 */
public static com.marakana.logservice.ILogService asInterface(android.os.IBinder obj)
{
if ((obj==null)) {
return null;
}
android.os.IInterface iin = (android.os.IInterface)obj.queryLocalInterface(DESCRIPTOR);
if (((iin!=null)&&(iin instanceof com.marakana.logservice.ILogService))) {
return ((com.marakana.logservice.ILogService)iin);
}
return new com.marakana.logservice.ILogService.Stub.Proxy(obj);
}
public android.os.IBinder asBinder()
{
return this;
}
@Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
{
switch (code)
{
case INTERFACE_TRANSACTION:
{
reply.writeString(DESCRIPTOR);
return true;
}
case TRANSACTION_log_d:
{
data.enforceInterface(DESCRIPTOR);
java.lang.String _arg0;
_arg0 = data.readString();
java.lang.String _arg1;
_arg1 = data.readString();
this.log_d(_arg0, _arg1);
reply.writeNoException();
return true;
}
case TRANSACTION_log:
{
data.enforceInterface(DESCRIPTOR);
com.marakana.logservice.Message _arg0;
if ((0!=data.readInt())) {
_arg0 = com.marakana.logservice.Message.CREATOR.createFromParcel(data);
}
else {
_arg0 = null;
}
this.log(_arg0);
reply.writeNoException();
return true;
}
}
return super.onTransact(code, data, reply, flags);
}
private static class Proxy implements com.marakana.logservice.ILogService
{
private android.os.IBinder mRemote;
Proxy(android.os.IBinder remote)
{
mRemote = remote;
}
public android.os.IBinder asBinder()
{
return mRemote;
}
public java.lang.String getInterfaceDescriptor()
{
return DESCRIPTOR;
}
public void log_d(java.lang.String tag, java.lang.String message) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
_data.writeString(tag);
_data.writeString(message);
mRemote.transact(Stub.TRANSACTION_log_d, _data, _reply, 0);
_reply.readException();
}
finally {
_reply.recycle();
_data.recycle();
}
}
public void log(com.marakana.logservice.Message msg) throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
if ((msg!=null)) {
_data.writeInt(1);
msg.writeToParcel(_data, 0);
}
else {
_data.writeInt(0);
}
mRemote.transact(Stub.TRANSACTION_log, _data, _reply, 0);
_reply.readException();
}
finally {
_reply.recycle();
_data.recycle();
}
}
}
static final int TRANSACTION_log_d = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
static final int TRANSACTION_log = (android.os.IBinder.FIRST_CALL_TRANSACTION + 1);
}
public void log_d(java.lang.String tag, java.lang.String message) throws android.os.RemoteException;
public void log(com.marakana.logservice.Message msg) throws android.os.RemoteException;
}
