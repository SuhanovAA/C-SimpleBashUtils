#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void read_file(char *argv[]);
int check_parametr(int argc, char *argv[]);

// parameters cat
struct flag {
  int flag_b;
  int flag_e;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_v;
} flags;

// parameters GNU
const struct option long_options[] = {
    {"number-nonblank", (int)0, (int *)0, 'b'},
    {"number", (int)0, (int *)0, 'n'},
    {"squeeze-blank", (int)0, (int *)0, 's'},
};

#endif  // SRC_CAT_S21_CAT_H_
