#include "s21_grep.h"

int main(int argc, char **argv) {
  char buffer[PAT_COUNT] = {0};
  if ((argc > 2)) {
    if (arguments(argc, argv, buffer) == 0) {
      open_file(argc, argv, buffer);
    }
  } else {
    grep_none_argc();
  }
  return 0;
}

int arguments(int argc, char **argv, char *buffer) {
  int opt = 0;
  int failFlag = 0;

  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        flags.eflag++;
        only_e_flag(buffer);
        break;
      case 'i':
        flags.iflag = 1;
        break;
      case 'v':
        flags.vflag = 1;
        break;
      case 'c':
        flags.cflag = 1;
        break;
      case 'l':
        flags.lflag = 1;
        break;
      case 'n':
        flags.nflag = 1;
        break;
      case 'h':
        flags.hflag = 1;
        break;
      case 's':
        flags.sflag = 1;
        break;
      case 'f':
        flags.fflag++;
        only_f_flag(buffer, argv, &failFlag);
        break;
      case 'o':
        flags.oflag = 1;
        break;
      default:
        failFlag = 1;
        break;
    }
  }
  if (!flags.eflag && !flags.fflag) {
    strcat(buffer, argv[optind++]);
  }
  return failFlag;
}

void open_file(int argc, char *argv[], char *buffer) {
  int count_file = argc - optind;
  FILE *fp = NULL;
  for (; optind < argc; optind++) {
    fp = fopen(argv[optind], "r");
    if (fp == NULL) {
      if (!flags.sflag)
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                argv[optind]);
      continue;
    }
    workspase(fp, buffer, argv, &count_file);
  }
}

void workspase(FILE *fp, char *buffer, char *argv[], int *count_file) {
  int new_line = 0;
  int line_n = 1;
  int line_c = 0;
  int flag = 0;
  regex_t regex;
  char str[STR_COUNT] = {0};
  int reg_i = 0;
  if (flags.fflag) {
    buffer[strlen(buffer) - 1] = '\0';
  }
  while (fgets(str, STR_COUNT, fp) != NULL) {
    if (flags.iflag) {
      reg_i = REG_ICASE;
    }
    regcomp(&regex, buffer, REG_EXTENDED | reg_i);
    work_flag(&regex, str, &line_n, &line_c, &flag, count_file, argv, fp,
              &new_line);
    line_n++;
  }
  if (flags.cflag) {
    if (*count_file > 1) printf("%s:", argv[optind]);
    if (flags.lflag && line_c > 0)
      printf("1\n");
    else
      printf("%d\n", line_c);
  }

  if (flags.lflag && flag > 0) {
    printf("%s\n", argv[optind]);
  }
  fclose(fp);
}

void work_flag(regex_t *regex, char *str, int *line_n, int *line_c, int *flag,
               int *count_file, char *argv[], FILE *fp, int *new_line) {
  regmatch_t matchPattern[1] = {0};
  size_t nmatch = 1;

  int regular = regexec(regex, str, nmatch, matchPattern, 0);

  if (flags.vflag) {
    if (regular == REG_NOMATCH)
      regular = 0;
    else
      regular = REG_NOMATCH;
  }

  if (regular == 0) {
    if (flags.oflag && !flags.cflag)
      only_o_flag(matchPattern, str, argv, line_n, count_file, regex, new_line,
                  nmatch);
    if (!flags.lflag && !flags.oflag && !flags.cflag) {
      if ((*count_file > 1) && !flags.hflag) {
        printf("%s:", argv[optind]);
      }
      if (flags.nflag) {
        printf("%d:", *line_n);
      }

      if (feof(fp)) {
        printf("%s\n", str);
      } else
        printf("%s", str);
    }
    (*line_c)++;
    (*flag)++;
  }
  regfree(regex);
}

void only_e_flag(char *buffer) {
  if (flags.eflag > 1) {
    strcat(buffer, "|");
  }
  strcat(buffer, optarg);
}

void only_f_flag(char *buffer, char *argv[], int *fail) {
  FILE *openFileFlagF = NULL;
  openFileFlagF = fopen(optarg, "r");
  int now_line;
  char f_str[2] = {0};
  if (openFileFlagF != NULL) {
    while ((now_line = fgetc(openFileFlagF)) != EOF) {
      if (now_line == '\n') {
        strcat(buffer, "|");
        continue;
      } else {
        f_str[0] = now_line;
        strcat(buffer, f_str);
      }
    }
    if (now_line == EOF) {
      strcat(buffer, "|");
    }
    fclose(openFileFlagF);
  } else if (flags.fflag < 2) {
    fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
            argv[optind]);
    *fail = 1;
  }
}

void only_o_flag(regmatch_t matchPattern[1], char *str, char *argv[],
                 int *line_n, int *count_file, regex_t *regex, int *new_line,
                 size_t nmatch) {
  char *s = str;
  while (*s != '\0') {
    if (regexec(regex, s, nmatch, matchPattern, 0) == 0) {
      if ((*count_file > 1) && (*new_line != *line_n)) {
        printf("%s:", argv[optind]);
      }

      for (int i = matchPattern[0].rm_so; i < matchPattern[0].rm_eo; i++) {
        printf("%c", s[i]);
      }
      printf("\n");

      s += matchPattern[0].rm_eo;
      *new_line = *line_n;
    } else
      s++;
  }
}

void grep_none_argc(void) {
  printf(
      "usage: s21_grep [-abcdDEFGHhIiJLlMmnOopqRSsUVvwXxZz] [-A num] [-B num] [-C[num]]\n\
        [-e pattern] [-f file] [--binary-files=value] [--color=when]\n\
        [--context[=num]] [--directories=action] [--label] [--line-buffered]\n\
        [--null] [pattern] [file ...]\n");
}
