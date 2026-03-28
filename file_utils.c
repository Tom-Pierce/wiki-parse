#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// returns the next line of a file pointer. strips \n so it must be handled by
// the caller
char *read_line(FILE *fptr) {
  int buf_size = 512;
  char *line;
  char *buf;
  char *tmp;
  int read_chars = 0;
  line = malloc(buf_size);

  if (line == NULL) {
    return NULL;
  }

  buf = line;

  while (fgets(buf, buf_size - read_chars, fptr)) {
    read_chars = strlen(line);

    // return line if fgets reached a \n
    if (line[read_chars - 1] == '\n') {
      line[read_chars - 1] = '\0';
      return (line);
    } else {
      // realloc to read more of the string
      buf_size = buf_size * 2;
      tmp = realloc(line, buf_size);
      if (tmp) {
        line = tmp;
        buf = line + read_chars;
      } else {
        free(line);
        return NULL;
      }
    }
  }
  if (read_chars > 0) {
    return line;
  }
  return NULL;
}


