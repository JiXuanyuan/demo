#ifndef _STRING_H_
#define _STRING_H_

#include "common.h"

typedef struct {
    char *ch;
    int length;
    int size;
} string;

typedef BOOL status;

status string_init(string *s);
status string_destroy(string *s);
status string_assign(string *s, char *c);
void string_echo(string *s);

#endif