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
