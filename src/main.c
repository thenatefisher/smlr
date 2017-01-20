#include "smlr.h"
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROGRAM_NAME "smlr"

#define AUTHORS "Nate S. Fisher"

void usage(void);

// clang-format off
static struct option const longopts[] = {
  {"size",      optional_argument, NULL, 's'},
  {"alignment", optional_argument, NULL, 'a'},
  {"help",      no_argument,       NULL, 'h'},
  {NULL, 0, NULL, 0}
};
// clang-format on

int main(int argc, char** argv) {
  int              c;
  size_t           size  = 5;
  smlr_alignment_t align = ALIGN_MIDDLE;

  while (1) {

    c = getopt_long(argc, argv, "s:a:h", longopts, NULL);

    // detect end of opts
    if (c == -1) {
      break;
    }

    switch (c) {
      case 's':
        size = strtoul(optarg, NULL, 10);
        if (size < 5) {
          fprintf(stderr, "Error: Output size must be greater than 4\n");
          return EXIT_FAILURE;
        }
        break;
      case 'a':
        if (!strcmp(optarg, "left")) {
          align = ALIGN_LEFT;
        }
        if (!strcmp(optarg, "right")) {
          align = ALIGN_RIGHT;
        }
        break;
      case 'h':
      default:
        usage();
        return EXIT_SUCCESS;
    }
  }

  smlr_t* smlr = smlr_new(size, align);
  if (smlr) {

    char* buf   = calloc(size + 1, sizeof(char));
    char  lastc = 0;

    if (!buf) {
      fprintf(stderr, "Error: Could not create output buffer\n");
      return EXIT_FAILURE;
    }

    while (1) {
      char c = getc(stdin);

      if (c == EOF) {
        if (smlr_get_buf(smlr, buf, size + 1)) {
          fprintf(stderr, "Error: Could not populate output buffer\n");
          free(buf);
          return EXIT_FAILURE;
        }
        printf("%s\n", buf);
        break;
      } else if (c == '\n') {
        continue;
      }

      if (smlr_push(smlr, c)) {
        free(buf);
        return EXIT_FAILURE;
      }
    }

    if (smlr_delete(smlr)) {
      fprintf(stderr, "Error: Could not delete smlr_t\n");
      free(buf);
      return EXIT_FAILURE;
    }

    free(buf);

  } else {
    fprintf(stderr, "Error: Could not create smlr_t\n");
  }

  return EXIT_SUCCESS;
}

void usage() {

  printf("smlr - Truncates stdin to a maximum fixed size, \n");
  printf("abbreviating the output if over the specified length.\n");

  printf("\nUsage: [source] | smlr [-s SIZE] [-a ALIGNMENT]\n");
  printf("\t-s: \tSize of output \n");
  printf("\t\tIf equal or greater than input, input is relayed to stdout unchanged\n");
  printf("\t\tDefault value is 5\n");
  printf("\t-a: \tAlignment of output \n");
  printf("\t\tCan be either `left` or `right`\n");
  printf("\t\tDefault value is middle\n");

  printf("\nEXAMPLES\n");
  printf("git rev-parse --abbrev-ref HEAD | smlr -s 10 -a left\n");
  printf("  > feat...-13\n");
  printf("echo \"abcdefghijkl\" | smlr -s 10 -a right\n");
  printf("  > ...ghijkl\n");
  printf("date | smlr -s 10\n");
  printf("  > Thu ...017\n\n");

}
