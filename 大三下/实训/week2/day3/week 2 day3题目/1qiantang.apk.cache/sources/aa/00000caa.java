package com.ttzgame.pay;

import android.content.Intent;
import android.os.Handler;
import android.os.Looper;
import java.lang.ref.WeakReference;
import org.cocos2dx.lib.Cocos2dxActivity;

/* loaded from: classes.dex */
public class Pay {
    private WeakReference<Cocos2dxActivity> b;
    private Handler c = new Handler(Looper.getMainLooper());

    /* renamed from: a  reason: collision with root package name */
    protected a[] f1294a = {new a("pond_1", "240浅塘币", "240浅塘币", 6.0d), new a("pond_2", "500浅塘币", "500浅塘币", 12.0d), new a("pond_3", "760浅塘币", "760浅塘币", 18.0d), new a("pond_5", "1280浅塘币", "1280浅塘币", 30.0d), new a("pond_rmAd", "去广告", "去广告", 6.0d)};

    /* loaded from: classes.dex */
    public static class a {

        /* renamed from: a  reason: collision with root package name */
        public String f1297a;
        public String b;
        public String c;
        public double d;

        public a(String str, String str2, String str3, double d) {
            this.f1297a = str;
            this.b = str2;
            this.c = str3;
            this.d = d;
        }
    }

    /* JADX INFO: Access modifiers changed from: protected */
    public Pay(Cocos2dxActivity cocos2dxActivity) {
        this.b = new WeakReference<>(cocos2dxActivity);
    }

    /* JADX INFO: Access modifiers changed from: private */
    public static native void nativePayResult(String str, boolean z);

    public void a() {
    }

    public void a(int i, int i2, Intent intent) {
    }

    public void a(String str) {
    }

    /* JADX INFO: Access modifiers changed from: protected */
    public void a(final String str, final boolean z) {
        final Cocos2dxActivity d = d();
        if (d == null) {
            return;
        }
        this.c.postDelayed(new Runnable() { // from class: com.ttzgame.pay.Pay.1
            @Override // java.lang.Runnable
            public void run() {
                d.runOnGLThread(new Runnable() { // from class: com.ttzgame.pay.Pay.1.1
                    @Override // java.lang.Runnable
                    public void run() {
                        Pay.nativePayResult(str, z);
                    }
                });
            }
        }, 300L);
    }

    public void b() {
    }

    public void c() {
    }

    /* JADX INFO: Access modifiers changed from: protected */
    public Cocos2dxActivity d() {
        WeakReference<Cocos2dxActivity> weakReference = this.b;
        if (weakReference != null) {
            return weakReference.get();
        }
        return null;
    }
}