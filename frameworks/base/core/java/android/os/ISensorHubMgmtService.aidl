package android.os;

interface ISensorHubMgmtService {
    /**
    * {@hide}
    */
    String read(int maxLength);

    /**
    * {@hide}
    */
    int write(String mString);
}
