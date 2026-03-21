#include <stdbool.h>
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
      free(line);
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

  // find first <page> tag
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
  // TODO stop adding to output file after encountering </page> tag.
  fputs(line, fptrout);
  fputs("\n", fptrout);
  while ((c = fgetc(fptrin)) != -1) {
    fputc(c, fptrout);
  }
  fclose(fptrin);
  fclose(fptrout);
  return 0;
}
