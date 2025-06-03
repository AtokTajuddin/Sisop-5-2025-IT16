#include "std_lib.h"
#include "std_type.h" // Untuk byte, bool

// Fungsi pembagian integer (menangani angka negatif)
int div(int a, int b) {
    int result = 0;
    int sign = 1;

    if (b == 0) {
        return 0; // Penanganan error: pembagian dengan nol
    }

    if (a < 0) {
        a = -a;
        sign = -sign;
    }
    if (b < 0) {
        b = -b;
        sign = -sign;
    }

    while (a >= b) {
        a -= b;
        result++;
    }

    return result * sign;
}

// Fungsi modulus integer (menangani angka negatif)
int mod(int a, int b) {
    int result = a - (div(a, b) * b);
    return result;
}

// Fungsi perkalian integer (menangani angka negatif)
int mul(int a, int b) {
    int result = 0;
    int sign = 1;

    if (a < 0) {
        a = -a;
        sign = -sign;
    }
    if (b < 0) {
        b = -b;
        sign = -sign;
    }

    while (b > 0) {
        result += a;
        b--;
    }

    return result * sign;
}

// Fungsi untuk membandingkan dua string secara manual
bool compareStrings(char *str1, char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) return false;
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

// Fungsi penyalinan string yang aman dengan batasan panjang
void strncpy(char *dst, char *src, int max_len) {
    int i = 0;
    while (src[i] != '\0' && i < max_len - 1) { // Sisakan ruang untuk null terminator
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0'; // Pastikan null terminator
}

// Fungsi penyalinan string (diperbaiki)
void strcpy(char *dst, char *src) {
    strncpy(dst, src, 32); // Batasi hingga 31 karakter + null terminator
}

// Fungsi untuk membersihkan buffer
void clear(byte *buf, unsigned int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        buf[i] = 0; // Gunakan nilai byte 0
    }
}

// Fungsi konversi string ke integer (menangani angka negatif)
void atoi(char *str, int *num) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    } else if (str[0] == '+') {
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            break; // Karakter tidak valid, hentikan parsing
        }
        i++;
    }
    *num = result * sign;
}

// Fungsi internal untuk membalik string (digunakan oleh itoa)
static void reverse_string(char *str, int length) {
    int start = 0;
    int end = length - 1;
    char temp;
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Fungsi konversi integer ke string (menangani angka negatif)
void itoa(int num, char *str) {
    int i = 0;
    int is_negative = 0;

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num > 0) {
        str[i++] = (mod(num, 10)) + '0'; // Gunakan mod alih-alih %
        num = div(num, 10); // Gunakan div alih-alih /
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';
    reverse_string(str, i);
}
