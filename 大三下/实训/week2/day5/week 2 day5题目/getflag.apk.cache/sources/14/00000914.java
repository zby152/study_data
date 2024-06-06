package com.ayy.hsapk1;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.KeyGenerator;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

/* loaded from: classes3.dex */
public class MainActivity extends AppCompatActivity {
    private String str;

    @Override // androidx.fragment.app.FragmentActivity, androidx.activity.ComponentActivity, androidx.core.app.ComponentActivity, android.app.Activity
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        setContentView(R.layout.activity_main);
        final TextView textView = (TextView) findViewById(R.id.username);
        final TextView textView2 = (TextView) findViewById(R.id.password);
        Button materialButton = (Button) findViewById(R.id.login_button);
        final byte[] bArr = {11, 22, 13, 23, 121, 32, 15, 27, 44, 35, 43, 32, 13, 24, 13, 111};
        try {
            this.str = decrypt("AES/CBC/PKCS5Padding", "HyKsaPpqT4l436tHiSEXtIlLgVV4GE7mGc2WoI0KlP2YhKFco7OPcJYtS58BFwDq", new SecretKeySpec(new byte[]{12, 32, 13, 14, 23, 108, 31, 108, 44, 121, 42, 121, 42, 113, 41, 124}, 0, 16, "AES"), new IvParameterSpec(new byte[]{12, 32, 13, 14, 23, 108, 31, 108, 44, 121, 42, 121, 42, 113, 41, 124}));
        } catch (InvalidAlgorithmParameterException | InvalidKeyException | NoSuchAlgorithmException | BadPaddingException | IllegalBlockSizeException | NoSuchPaddingException e) {
            e.printStackTrace();
        }
        materialButton.setOnClickListener(new View.OnClickListener() { // from class: com.ayy.hsapk1.MainActivity.1
            @Override // android.view.View.OnClickListener
            public void onClick(View view) {
                String securePassword = MainActivity.this.getSecurePassword(textView2.getText().toString(), bArr);
                if (!textView.getText().toString().equals("hillstone") || !securePassword.equals("4368354b57abefdb3da930aa1f7db42c3a1d318401d7474c25f5a14bbaf8fb34")) {
                    Toast.makeText(MainActivity.this, "Login Failure", 0).show();
                    System.out.println(securePassword);
                    return;
                }
                MainActivity mainActivity = MainActivity.this;
                Toast.makeText(mainActivity, mainActivity.str, 0).show();
            }
        });
    }

    /* JADX INFO: Access modifiers changed from: private */
    public String getSecurePassword(String str, byte[] bArr) {
        try {
            MessageDigest instance = MessageDigest.getInstance("SHA-256");
            instance.update(bArr);
            byte[] digest = instance.digest(str.getBytes());
            StringBuilder sb = new StringBuilder();
            for (byte b : digest) {
                sb.append(Integer.toString((b & 255) + 256, 16).substring(1));
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static SecretKey generateKey(int i) throws NoSuchAlgorithmException {
        KeyGenerator instance = KeyGenerator.getInstance("AES");
        instance.init(i);
        return instance.generateKey();
    }

    public static IvParameterSpec generateIv() {
        byte[] bArr = new byte[16];
        new SecureRandom().nextBytes(bArr);
        return new IvParameterSpec(bArr);
    }

    public static String encrypt(String str, String str2, SecretKey secretKey, IvParameterSpec ivParameterSpec) throws NoSuchPaddingException, NoSuchAlgorithmException, InvalidAlgorithmParameterException, InvalidKeyException, BadPaddingException, IllegalBlockSizeException {
        Cipher instance = Cipher.getInstance(str);
        instance.init(1, secretKey, ivParameterSpec);
        return Base64.getEncoder().encodeToString(instance.doFinal(str2.getBytes()));
    }

    public static String decrypt(String str, String str2, SecretKey secretKey, IvParameterSpec ivParameterSpec) throws NoSuchPaddingException, NoSuchAlgorithmException, InvalidAlgorithmParameterException, InvalidKeyException, BadPaddingException, IllegalBlockSizeException {
        Cipher instance = Cipher.getInstance(str);
        instance.init(2, secretKey, ivParameterSpec);
        return new String(instance.doFinal(Base64.getDecoder().decode(str2)));
    }
}