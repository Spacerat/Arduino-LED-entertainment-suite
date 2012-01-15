/* 
simple serial library 
header file
*/

#ifndef _SERIAL_LIB
#define _SERIAL_LIB

void serial_init();
void serial_write(unsigned char c);
void serial_puts(const char * string);
int serial_printf(const char *fmt, ...);

#endif

