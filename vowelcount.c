/* file:   vowelcount.c
   author: Scott Cheloha <scottcheloha@gmail.com>

   vowelcount counts the number of vowels in an input file.
   Currently only supports ASCII input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/* Returns 1 if character 'c' is a vowel, and 0 otherwise.  */
int
is_vowel(int c, int *vowels)
{
  if (isalpha(c)) {
    /* 'c' is alphabetical.  Now check if 'c' is a vowel.  */
    int lower_c = tolower(c);
    int i = 0;
    while (vowels[i] != '\0') {
      if (lower_c == vowels[i]) {
        return 1;
      }

      i++;
    }
  }

  return 0;
}

void
usage()
{
  fprintf(stderr,
          "usage: vc [file]\n"                                  \
          "options:\n"                                                  \
          "  h  --  print this message and exit\n");
  exit(1);
}

int
main(int argc, char **argv)
{
  FILE *input_file;
  int c;
  while ( (c = getopt(argc, argv, "a:h")) != -1) {
    switch (c) {
    case 'a':
      fprintf(stderr, "Error: -a option used.  " \
              "Alphabet files not supported yet.\n");
      usage();
      break;
    case 'h':
      usage();
      break;
    }
  }

  char *input_filename;
  if (optind < argc) {
    /* first non-option argument is assumed to be input filename */
    input_filename = argv[optind];
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
      fprintf(stderr, "Error: '%s': %s\n", argv[optind], strerror(errno));
      exit(1);
    }
  } else {
    /* If input file is not specified, read from standard input.  */
    input_file = stdin;
  }

  if (argc == 1) {

  } else if (argc == 2) {
    /* If there is only one argument, assume it is the input file
       and try to read it.  */
  } else {
    /* Otherwise, that's an error.  Print usage info and quit.  */
    usage();
  }

  /* Find our alphabet file.  */
  /* Currently I just use the vowels[] array.  */

  /* Define what a vowel actually is.
     Assuming English alphabet currently.
     NULL terminated.  */
  int vowels[6] = {'a','e','i','o','u','\0'};

  /* Start reading through the file, character by character and counting
     those vowels.  */
  unsigned long vowel_count = 0;
  while ((c = fgetc(input_file)) != EOF) {
    if (is_vowel(c, vowels)) {
      vowel_count++;
    }
  }

  /* Check for error on input file.  */
  if (ferror(input_file)) {
    fprintf(stderr, "Error: file '%s': %s\n",
            input_filename, strerror(errno));
    goto cleanup;
  }

  /* Print results.  */
  printf("    vowels: %lu\n", vowel_count);

  /* If necessary, clean up.  */
 cleanup:
  if (input_file != stdin) {
    if ( (fclose(input_file) == EOF)) {
      fprintf(stderr, "Error: tried to close file '%s': %s",
              input_filename, strerror(errno));
      exit(1);
    }
  }

  return 0;
}
