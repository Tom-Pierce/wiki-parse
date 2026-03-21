#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (line[read_chars - 1] == '\n') {
      line[read_chars - 1] = '\0';
      return (line);
      free(line);
    } else {
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

  if (argc < 3) {
    printf("Usage: page_split <filename> <output path>");
    return 1;
  }
  printf("splitting %s, saving in %s\n", argv[1], argv[2]);

  FILE *fptrin, *fptrout;
  char *line;
  char *beginning = NULL;
  int linecount = 0;
  fptrin = fopen(argv[1], "r");
  fptrout = fopen(argv[2], "w");

  while (!beginning) {
    line = read_line(fptrin);
    if (!line) {
      return -1;
    }
    beginning = strstr(line, "<page>");
    linecount++;
    printf("beginnning: %s, line: %i\n", beginning, linecount);
  };
  int c;
  while((c = fgetc(fptrin)) != -1){
    fputc(c, fptrout);
  }
  fclose(fptrin);
  fclose(fptrout);
  return 0;
}
