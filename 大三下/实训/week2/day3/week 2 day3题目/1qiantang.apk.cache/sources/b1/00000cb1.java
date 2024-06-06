package com.ttzgame.pay;

/* loaded from: classes.dex */
public final class b {

    /* renamed from: a  reason: collision with root package name */
    private static char f1299a = '=';
    private static byte[] b = new byte[128];
    private static char[] c = new char[64];

    static {
        int i;
        int i2;
        int i3 = 0;
        for (int i4 = 0; i4 < 128; i4++) {
            b[i4] = -1;
        }
        for (int i5 = 90; i5 >= 65; i5--) {
            b[i5] = (byte) (i5 - 65);
        }
        int i6 = 122;
        while (true) {
            i = 26;
            if (i6 < 97) {
                break;
            }
            b[i6] = (byte) ((i6 - 97) + 26);
            i6--;
        }
        int i7 = 57;
        while (true) {
            i2 = 52;
            if (i7 < 48) {
                break;
            }
            b[i7] = (byte) ((i7 - 48) + 52);
            i7--;
        }
        byte[] bArr = b;
        bArr[43] = 62;
        bArr[47] = 63;
        for (int i8 = 0; i8 <= 25; i8++) {
            c[i8] = (char) (i8 + 65);
        }
        int i9 = 0;
        while (i <= 51) {
            c[i] = (char) (i9 + 97);
            i++;
            i9++;
        }
        while (i2 <= 61) {
            c[i2] = (char) (i3 + 48);
            i2++;
            i3++;
        }
        char[] cArr = c;
        cArr[62] = '+';
        cArr[63] = '/';
    }

    public static String a(byte[] bArr) {
        if (bArr == null) {
            return null;
        }
        int length = bArr.length * 8;
        if (length == 0) {
            return "";
        }
        int i = length % 24;
        int i2 = length / 24;
        char[] cArr = new char[(i != 0 ? i2 + 1 : i2) * 4];
        int i3 = 0;
        int i4 = 0;
        int i5 = 0;
        while (i3 < i2) {
            int i6 = i4 + 1;
            byte b2 = bArr[i4];
            int i7 = i6 + 1;
            byte b3 = bArr[i6];
            int i8 = i7 + 1;
            byte b4 = bArr[i7];
            byte b5 = (byte) (b3 & 15);
            byte b6 = (byte) (b2 & 3);
            byte b7 = (byte) ((b2 & Byte.MIN_VALUE) == 0 ? b2 >> 2 : (b2 >> 2) ^ 192);
            byte b8 = (byte) ((b3 & Byte.MIN_VALUE) == 0 ? b3 >> 4 : (b3 >> 4) ^ 240);
            int i9 = (b4 & Byte.MIN_VALUE) == 0 ? b4 >> 6 : (b4 >> 6) ^ 252;
            int i10 = i5 + 1;
            char[] cArr2 = c;
            cArr[i5] = cArr2[b7];
            int i11 = i10 + 1;
            cArr[i10] = cArr2[(b6 << 4) | b8];
            int i12 = i11 + 1;
            cArr[i11] = cArr2[(b5 << 2) | ((byte) i9)];
            cArr[i12] = cArr2[b4 & 63];
            i3++;
            i5 = i12 + 1;
            i4 = i8;
        }
        if (i == 8) {
            byte b9 = bArr[i4];
            byte b10 = (byte) (b9 & 3);
            int i13 = (b9 & Byte.MIN_VALUE) == 0 ? b9 >> 2 : (b9 >> 2) ^ 192;
            int i14 = i5 + 1;
            char[] cArr3 = c;
            cArr[i5] = cArr3[(byte) i13];
            int i15 = i14 + 1;
            cArr[i14] = cArr3[b10 << 4];
            char c2 = f1299a;
            cArr[i15] = c2;
            cArr[i15 + 1] = c2;
        } else if (i == 16) {
            byte b11 = bArr[i4];
            byte b12 = bArr[i4 + 1];
            byte b13 = (byte) (b12 & 15);
            byte b14 = (byte) (b11 & 3);
            byte b15 = (byte) ((b11 & Byte.MIN_VALUE) == 0 ? b11 >> 2 : (b11 >> 2) ^ 192);
            int i16 = (b12 & Byte.MIN_VALUE) == 0 ? b12 >> 4 : (b12 >> 4) ^ 240;
            int i17 = i5 + 1;
            char[] cArr4 = c;
            cArr[i5] = cArr4[b15];
            int i18 = i17 + 1;
            cArr[i17] = cArr4[((byte) i16) | (b14 << 4)];
            cArr[i18] = cArr4[b13 << 2];
            cArr[i18 + 1] = f1299a;
        }
        return new String(cArr);
    }
}