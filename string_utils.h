#ifndef STR_SLICE_H
#define STR_SLICE_H

char *str_slice(const char *start, const char *end);

char *remove_char(char *str, int c);

char *remove_illegal_chars(char *str);

void str_append(char *str, int max, char c);

#endif
