#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// returns the next line of a file pointer
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
  return NULL;
}

int main(int argc, char *argv[]) {
  // TODO at some point, take in output directory and have multiple output files
  // in that dir

  const char *open_tag = "<page>";
  const char *close_tag = "</page>";

  if (argc < 3) {
    printf("Usage: page_split <filename> <output path>");
    return 1;
  }
  printf("splitting %s, saving in %s\n", argv[1], argv[2]);

  FILE *fptrin, *fptrout;
  char *line;
  char *output_start = NULL;
  char *output_end = NULL;
  int in_page = 0;
  fptrin = fopen(argv[1], "r");
  fptrout = fopen(argv[2], "w");

  while ((line = read_line(fptrin)) != NULL) {
    if (!in_page) {
      output_start = strstr(line, open_tag);
      if (output_start) {
        fputs(output_start, fptrout);
        fputs("\n", fptrout);
        in_page = 1;
      }
    } else {
      output_end = strstr(line, close_tag);
      if (output_end) {
        in_page = 0;
        size_t length = (output_end - line) + strlen(close_tag);
        char temp[length + 1];
        memcpy(temp, line, length);
        temp[length] = '\0';
        fputs(temp, fptrout);
        fputs("\n", fptrout);
      } else {
        fputs(line, fptrout);
        fputs("\n", fptrout);
      }
    }
    free(line);
  }
  fclose(fptrin);
  fclose(fptrout);
  return 0;
}
