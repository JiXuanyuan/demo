#include "string.h"

#define STRING_EMPTY        '\0'
#define STRING_SIZE_INIT    50
#define STRING_SIZE_INCR    20

status string_init(string *s) {
    char *p = (char *)common_malloc(STRING_SIZE_INIT * sizeof(char));
    if (p == NULL) {
        LOG_ERROR("malloc error");
        return FALSE;
    }
    for (int i=0; i<STRING_SIZE_INIT; i++) {
        p[i] = STRING_EMPTY;
    }

    s->ch = p;
    s->length = 0;
    s->size = STRING_SIZE_INIT;
    LOG_DEBUG("init");
    return TRUE;
}

status string_destroy(string *s) {
    common_free(s->ch);
    s->ch = NULL;
    s->length = 0;
    s->size = 0;
    LOG_DEBUG("destroy");
    return TRUE;
} 

static status string_increase(string *s) {
    int nsize = s->size + STRING_SIZE_INCR;
    char *nch = (char *)common_realloc(s->ch, nsize * sizeof(char));
    if (nch == NULL) {
        LOG_ERROR("realloc error");
        return FALSE;
    }
    s->ch = nch;
    s->size = nsize;
    LOG_DEBUG("increase");
    return TRUE;
}

status string_assign(string *s, char *c) {
    for (char *p=c; *p!=STRING_EMPTY; p++) {
        if (s->length >= s->size) {
            string_increase(s);
        }
        s->ch[s->length] = *p;
        s->length++;
    }

    LOG_DEBUG("assign");
    return TRUE;
}

void string_echo(string *s) {
    printf("length=%d, size=%d\n", s->length, s->size);
    printf("%s\n", s->ch);
    LOG_DEBUG("echo");
}