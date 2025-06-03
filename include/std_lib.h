#ifndef STD_LIB_H
#define STD_LIB_H

#include "std_type.h"

int div(int a, int b);
int mod(int a, int b);
int mul(int a, int b); // Deklarasi baru untuk perkalian
bool compareStrings(char *str1, char *str2);
void strncpy(char *dst, char *src, int max_len);
void strcpy(char *dst, char *src);
void clear(byte *buf, unsigned int size);
void atoi(char *str, int *num);
void itoa(int num, char *str);

#endif
