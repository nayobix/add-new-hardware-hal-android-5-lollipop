package com.android.server.sensorhubmgmt;

import android.content.Context;
import android.os.Handler;
import android.os.ISensorHubMgmtService;
import android.os.Looper;
import android.os.Message;
import android.os.Process;
import android.util.Log;

public class SensorHubMgmtService extends ISensorHubMgmtService.Stub {

    private static final String TAG = "SensorHubMgmtService";
    private Context mContext;
    private int mNativePointer;

    public SensorHubMgmtService(Context context) {
        super();
        mContext = context;
        Log.i(TAG, "SensorHubMgmtService started");
        mNativePointer = init_native();
        Log.i(TAG, "test() returns " + test_native(mNativePointer, 20));
    }
    protected void finalize() throws Throwable {
        finalize_native(mNativePointer);
        super.finalize();
    }
    public String read(int maxLength)
    {
        int length;
        byte[] buffer = new byte[maxLength];
        length = read_native(mNativePointer, buffer);
        return new String(buffer, 0, length);
    }
    public int write(String mString)
    {
        byte[] buffer = mString.getBytes();
        return write_native(mNativePointer, buffer);
    }
    private static native int init_native();
    private static native void finalize_native(int ptr);
    private static native int read_native(int ptr, byte[] buffer);
    private static native int write_native(int ptr, byte[] buffer);
    private static native int test_native(int ptr, int value);
}
