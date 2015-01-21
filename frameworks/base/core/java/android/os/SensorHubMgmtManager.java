package android.os;
import android.os.ISensorHubMgmtService;
import android.util.Log;

public class SensorHubMgmtManager
{
    ISensorHubMgmtService mService;
    private static final String TAG = "SensorHubMgmtManager";

    public String read(int maxLength) {
        try {
            return mService.read(maxLength);
        } catch (RemoteException e) {
            Log.e(TAG, "Excpetion in read: " + e.toString());
            return null;
        }
    }
    public int write(String mString) {
        try {
            return mService.write(mString);
        } catch (RemoteException e) {
            Log.e(TAG, "Excpetion in write: " + e.toString());
            return 0;
        }
    }
    public SensorHubMgmtManager(ISensorHubMgmtService service) {
        mService = service;
    }
}
