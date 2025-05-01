#pragma once
#include <stdio.h>

char* ltoa(long value, char* str, int base) {
    sprintf(str, (base == 10 ? "%ld" :
                  base == 16 ? "%lx" :
                  base == 8  ? "%lo" : "%ld"), value);
    return str;
}

char* dtostrf(float val, int width, unsigned int prec, char* buf) {
    char format[10];
    snprintf(format, sizeof(format), "%%%d.%df", width, prec);
    snprintf(buf, width + prec + 10, format, val);
    return buf;
}

char* ultoa(unsigned long value, char* str, int base) {
    char* ptr = str;
    char* ptr1 = str;
    char tmp_char;
    unsigned long tmp_value;

    // Нельзя использовать base < 2
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[tmp_value % base];
    } while (value);

    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return str;
}
