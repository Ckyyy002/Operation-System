#ifndef __STD_LIB_H__
#define __STD_LIB_H__

#include "std_type.h"

int div(int a, int b);
int mod(int a, int b);

void memcpy(unsigned char* src, unsigned char* dst, unsigned int size);
void clear(unsigned char* buf, unsigned int size);

unsigned int strlen(char* str);
int strcmp(char* str1, char* str2);
void strcpy(char* src, char* dst);

#endif
