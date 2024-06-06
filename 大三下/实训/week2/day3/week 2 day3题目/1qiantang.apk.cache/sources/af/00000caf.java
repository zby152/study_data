package com.ttzgame.pay;

import android.text.TextUtils;
import com.alipay.sdk.app.PayTask;
import com.ttzgame.pay.Pay;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Random;
import org.cocos2dx.lib.Cocos2dxActivity;

/* loaded from: classes.dex */
public class a extends Pay {
    public a(Cocos2dxActivity cocos2dxActivity) {
        super(cocos2dxActivity);
    }

    private String a(String str, String str2, String str3) {
        return (((((((((("partner=\"2088911708570095\"&seller_id=\"ttzgame@163.com\"") + "&out_trade_no=\"" + e() + "\"") + "&subject=\"" + str + "\"") + "&body=\"" + str2 + "\"") + "&total_fee=\"" + str3 + "\"") + "&notify_url=\"http://notify.msp.hk/notify.htm\"") + "&service=\"mobile.securitypay.pay\"") + "&payment_type=\"1\"") + "&_input_charset=\"utf-8\"") + "&it_b_pay=\"30m\"") + "&return_url=\"m.alipay.com\"";
    }

    private String b(String str) {
        Pay.a[] aVarArr;
        for (Pay.a aVar : this.f1294a) {
            if (aVar.f1297a.equals(str)) {
                return a(aVar.b, aVar.c, "" + aVar.d);
            }
        }
        return null;
    }

    private String c(String str) {
        return SignUtils.a(str);
    }

    private String e() {
        String format = new SimpleDateFormat("MMddHHmmss", Locale.getDefault()).format(new Date());
        Random random = new Random();
        return (format + random.nextInt()).substring(0, 15);
    }

    private String f() {
        return "sign_type=\"RSA\"";
    }

    @Override // com.ttzgame.pay.Pay
    public void a(final String str) {
        String b = b(str);
        if (b == null) {
            a(str, false);
            return;
        }
        String c = c(b);
        try {
            c = URLEncoder.encode(c, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        final String str2 = b + "&sign=\"" + c + "\"&" + f();
        new Thread(new Runnable() { // from class: com.ttzgame.pay.a.1
            @Override // java.lang.Runnable
            public void run() {
                a aVar;
                String str3;
                boolean z = true;
                String a2 = new c(new PayTask(a.this.d()).pay(str2, true)).a();
                if (TextUtils.equals(a2, "9000")) {
                    aVar = a.this;
                    str3 = str;
                } else if (TextUtils.equals(a2, "8000")) {
                    return;
                } else {
                    aVar = a.this;
                    str3 = str;
                    z = false;
                }
                aVar.a(str3, z);
            }
        }).start();
    }
}