package android.arch.lifecycle;

import android.support.annotation.RestrictTo;
import java.util.HashMap;
import java.util.Map;

@RestrictTo({RestrictTo.Scope.LIBRARY_GROUP})
/* loaded from: classes.dex */
public class MethodCallsLogger {
    private Map<String, Integer> mCalledMethods = new HashMap();

    @RestrictTo({RestrictTo.Scope.LIBRARY_GROUP})
    public boolean approveCall(String str, int i) {
        Integer num = this.mCalledMethods.get(str);
        boolean z = false;
        int intValue = num != null ? num.intValue() : 0;
        if ((intValue & i) != 0) {
            z = true;
        }
        this.mCalledMethods.put(str, Integer.valueOf(i | intValue));
        return !z;
    }
}