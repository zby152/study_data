#include "stdio.h"
#include "type.h"

#define LB32_MASK 0x00000001
#define LB64_MASK 0x0000000000000001
#define L64_MASK 0x00000000ffffffff

/* Initial Permutation Table */
static char IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

/* Inverse Initial Permutation Table */
static char PI[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

/*
 * input  S(64 bits state)
 * into   PT(permutation table)
 * output R(64 bits result)
 */
#define DES_PT(S, PT, R)                          \
    u64 R = 0;                                    \
    for (int i = 0; i < 64; i++) {                \
        (R) <<= 1;                                \
        (R) |= ((S) >> (64 - PT[i])) & LB64_MASK; \
    }

/* The S-Box tables */
static u32 SB[8][64] = {
    {/* S1 */
     14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
     0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
     4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
     15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
    {/* S2 */
     15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
     3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
     0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
     13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
    {/* S3 */
     10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
     13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
     13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
     1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
    {/* S4 */
     7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
     13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
     10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
     3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
    {/* S5 */
     2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
     14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
     4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
     11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
    {/* S6 */
     12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
     10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
     9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
     4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
    {/* S7 */
     4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
     13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
     1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
     6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
    {/* S8 */
     13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
     1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
     7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
     2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

/* Post S-Box permutation */
static char SBP[] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25};

/* Key Permuted Choice Table */
static char KPC[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

/* Compression D-box Table */
static char KDB[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};

/*Expansion D-box Table */
static char EDB[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

/* Iteration Shift Array */
static char iteration_shift_left[] = {
    /* 1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16 */
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

/* Key Parity Drop */
#define KEY_PD(K, R)                               \
    /* 56 bits */                                  \
    u64(R) = 0;                                    \
                                                   \
    /* initial key schedule calculation */         \
    for (int i = 0; i < 56; i++) {                 \
        (R) <<= 1;                                 \
        (R) |= ((K) >> (64 - KPC[i])) & LB64_MASK; \
    }

static void keyGen(u64 keyPD, u64* sub_key) {
    /* 28 bits */
    u32 L, R;
    L = (u32)((keyPD >> 28) & 0x000000000fffffff);
    R = (u32)(keyPD & 0x000000000fffffff);

    /* 56 bits */
    u64 LR;

    /* Calculation of the 16 keys */
    for (int i = 0; i < 16; i++) {
        /* key schedule */
        // shifting Li and Ri
        for (int j = 0; j < iteration_shift_left[i]; j++) {
            L = 0x0fffffff & (L << 1) | 0x00000001 & (L >> 27);
            R = 0x0fffffff & (R << 1) | 0x00000001 & (R >> 27);
        }

        /* merge */
        LR = 0;
        LR = (((u64)L) << 28) | (u64)R;

        /* generate round key */
        sub_key[i] = 0;
        for (int j = 0; j < 48; j++) {
            sub_key[i] <<= 1;
            sub_key[i] |= (LR >> (56 - KDB[j])) & LB64_MASK;
        }
    }
}

/*
 * The DES function
 * plaintext: 64 bits message
 * key:       64 bits key for encryption/decryption
 * mode:      'e' = encryption, 'd' = decryption
 */
u64 DES(u64 plaintext, u64 key, char mode) {
    KEY_PD(key, keyPD)
    u64 sub_key[16] = {0};
    keyGen(keyPD, sub_key);

    DES_PT(plaintext, IP, init_perm_res)
    /* Decompose T64 into L and R parts */
    u32 L = 0;
    u32 R = 0;
    L = (u32)(init_perm_res >> 32) & L64_MASK;
    R = (u32)(init_perm_res)&L64_MASK;

    for (int i = 0; i < 16; i++) {
        /* f(R,k) function */
        /* expansion 32 bits R -> 48 bits s_input */
        u64 s_input = 0;
        for (int j = 0; j < 48; j++) {
            s_input <<= 1;
            s_input |= (u64)((R >> (32 - EDB[j])) & LB32_MASK);
        }

        /*
         * Encryption/Decryption
         * XORing expanded Ri with Ki
         */
        if (mode == 'd') {
            // decryption
            s_input = s_input ^ sub_key[15 - i];
        } else {
            // encryption
            s_input = s_input ^ sub_key[i];
        }

        u8 row, col;
        u32 s_output = 0;
        /* S-Box Tables */
        for (int j = 0; j < 8; j++) {
            row = (char)((s_input & (0x0000840000000000 >> 6 * j)) >> (42 - 6 * j));
            row = (row >> 4) | row & 0x01;
            col = (char)((s_input & (0x0000780000000000 >> 6 * j)) >> (43 - 6 * j));

            s_output <<= 4;
            s_output |= (u32)(SB[j][16 * row + col] & 0x0f);
        }

        /* post S-box permutation */
        u32 f_function_res = 0;
        for (int j = 0; j < 32; j++) {
            f_function_res <<= 1;
            f_function_res |= (s_output >> (32 - SBP[j])) & LB32_MASK;
        }

        /* Xor */
        L ^= f_function_res;

        /* exchange */
        L ^= R;
        R ^= L;
        L ^= R;
    }

    u64 pre_output = (((u64)R) << 32) | (u64)L;
    DES_PT(pre_output, PI, ct)
    return ct;
}

PRIVATE void hex2value(char* ps, u64* cur) {
    if (*(ps + 1) == 'x') ps = ps + 2;
    if (*(ps) == '\0') return;
    u64 m = (*ps <= '9') ? (*ps - '0') : (*ps + 10 - 'A');
    *cur = 16 * (*cur) + m;
    hex2value(ps + 1, cur);
}

PRIVATE void value2hex(u32 val, char* ps, int count) {
    u32 m = val % 16;
    u32 q = val / 16;
    if (count) {
        value2hex(q, ps - 1, count - 1);
    }
    *ps = (m < 10) ? (m + '0') : (m - 10 + 'A');
}

int main(int argc, char* argv[]) {
    if (argv[1][1] == 'h') {
        printf("des -e -m <64 bits  plaintext> -k <64 bits key>\n");
        printf("des -d -m <64 bits ciphertext> -k <64 bits key>\n");
    } else if (argv[1][1] == 'e') {
        char* pt_str = argv[3];
        u64 pt = 0;
        hex2value(pt_str, &pt);

        char* key_str = argv[5];
        u64 key = 0;
        hex2value(key_str, &key);

        u64 ct = DES(pt, key, 'e');
        u32 l = (ct >> 32) & L64_MASK;
        u32 r = (ct >> 0) & L64_MASK;

        printf("ciphertext: 0x");

        char* ll = "00000000";
        value2hex(l, ll + 7, 7);
        printf("%s", ll);

        char* rr = "00000000";
        value2hex(r, rr + 7, 7);
        printf("%s\n", rr);
    } else if (argv[1][1] == 'd') {
        char* ct_str = argv[3];
        u64 ct = 0;
        hex2value(ct_str, &ct);

        char* key_str = argv[5];
        u64 key = 0;
        hex2value(key_str, &key);

        u64 pt = DES(ct, key, 'd');
        u32 l = (pt >> 32) & L64_MASK;
        u32 r = (pt >> 0) & L64_MASK;

        printf("plaintext:  0x");

        char* ll = "00000000";
        value2hex(l, ll + 7, 7);
        printf("%s", ll);

        char* rr = "00000000";
        value2hex(r, rr + 7, 7);
        printf("%s\n", rr);
    } else {
        printf("des -e -m <64 bits  plaintext> -k <64 bits key>\n");
        printf("des -d -m <64 bits ciphertext> -k <64 bits key>\n");
    }
    return 0;
}