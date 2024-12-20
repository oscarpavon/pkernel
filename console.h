#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdint.h>

extern int console_current_line;

void print(const char* string);

void print_in_current_line(const char* string);

void print_in_line_number(uint8_t line_number, char* string);

void print_in_line_buffer_number(uint8_t line_number, char* string);

void print_uint(uint32_t number);

void print_byte_hex(uint8_t number);

void clear();

extern int console_horizonal;
extern int console_vertical;

#endif
