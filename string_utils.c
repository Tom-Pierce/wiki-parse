#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_slice(const char *start, const char *end) {
  size_t length = (end - start);
  char *temp = malloc(length + 1);
  if (!temp) {
    free(temp);
    return NULL;
  }
  memcpy(temp, start, length);
  temp[length] = '\0';
  return temp;
}

void remove_char(char *str, int c) {
  char *scan = str;
  char *update = str;
  while (*scan) {
    if (*scan != c) {
      *update = *scan;
      update++;
    }
    scan++;
  }
  *update = '\0';
}

void remove_illegal_chars(char *str) {
  const char invalid_chars[] = {'\\', '/', ':', '*', '?', '"', '<', '>', '|'};
  int num_invalid = sizeof(invalid_chars) / sizeof(invalid_chars[0]);
  for (int i = 0; i < num_invalid; i++) {
    remove_char(str, invalid_chars[i]);
  }
}

void str_append(char *str, int max, char c) {
  int len = strlen(str);
  if (len + 1 < max) {
    str[len] = c;
    str[len + 1] = '\0';
  }
}
