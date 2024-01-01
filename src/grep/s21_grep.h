#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAT_COUNT 4096
#define STR_COUNT 4096
#define NEW_COUNT 4096

int arguments(int argc, char *argv[], char *buffer);
void open_file(int argc, char *argv[], char *buffer);
void only_e_flag(char *buffer);
void only_f_flag(char *buffer, char *argv[], int *fail);
void workspase(FILE *fp, char *buffer, char *argv[], int *count_file);
void work_flag(regex_t *regex, char *str, int *line_n, int *line_c, int *flag,
               int *count_file, char *argv[], FILE *fp, int *new_line);
void only_o_flag(regmatch_t matchptr[1], char *str, char *argv[], int *line_n,
                 int *count_file, regex_t *regex, int *new_line, size_t nmatch);
void grep_none_argc(void);

extern char *optarg;
extern int optind, opterr, optopt;

struct flag {
  int eflag;
  int iflag;
  int vflag;
  int cflag;
  int lflag;
  int nflag;
  int hflag;
  int sflag;
  int fflag;
  int oflag;
} flags;

#endif
