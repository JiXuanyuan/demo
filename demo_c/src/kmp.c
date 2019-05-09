#include "kmp.h"

int kmp_index_ordinary(string *s, string *p, int pos) {
    // index 值域1～length，0无匹配。
    if (pos <= 0 || pos > s->length) {
        LOG_ERROR("error, pos=%d", pos);
        return 0;
    }

    int index = 0;
    int i = pos;
    int j = 1;
    while (i <= s->length && j <= p->length) {
        LOG_DEBUG("s[%d]=%c, p[%d]=%c", i, s->ch[i-1], j, p->ch[j-1]);
        if (s->ch[i-1] == p->ch[j-1]) {
            i++;
            j++;
        } else {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > p->length) {
        index = i - p->length;
    }
    LOG_INFO("index=%d", index);
    return index;
}

static status kmp_next_init(string *p, int **next) {
    *next = (int *) common_malloc(p->length * sizeof(int));
    if (*next == NULL) {
        LOG_ERROR("realloc error");
        return FALSE;
    }

    // KMP算法核心，next映射表初始化
    int j = 1;
    int k = 0;
    (*next)[0] = 0;
    while (j < p->length) {
        if (k == 0 || p->ch[j-1] == p->ch[k-1]) {
            j++;
            k++;
            (*next)[j-1] = k;
        } else {
            k = (*next)[k-1];
        }
    }

    // 显示next映射表
    for (int i=0; i < p->length; i++) {
        LOG_INFO("next[%d]=%d", i, (*next)[i]);
    }
    LOG_DEBUG("next init");
    return TRUE;
}

static status kmp_next_destroy(int **next) {
    common_free(*next);
    *next = NULL;
    LOG_DEBUG("next destroy");
    return TRUE;
}

int kmp_index(string *s, string *p, int pos) {
    // index 值域1～length，0无匹配。
    if (pos <= 0 || pos > s->length) {
        LOG_ERROR("error, pos=%d", pos);
        return 0;
    }

    int index = 0;
    int i = pos;
    int j = 1;
    int *next;
    kmp_next_init(p, &next);
    while (i <= s->length && j <= p->length) {
        LOG_DEBUG("s[%d]=%c, p[%d]=%c", i, s->ch[i-1], j, p->ch[j-1]);
        if (s->ch[i-1] == p->ch[j-1]) {
            i++;
            j++;
        } else {
            j = next[j-1];
            if (j == 0 ) {
                i++;
                j++;
            }
        }
    }
    if (j > p->length) {
        index = i - p->length;
    }
    kmp_next_destroy(&next);

    LOG_INFO("index=%d", index);
    return index;
}
