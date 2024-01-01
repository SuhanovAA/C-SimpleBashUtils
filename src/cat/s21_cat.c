#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int i, j;
  int check_error, flags_num;
  flags_num = 0;
  for (i = 1; i < argc; i++) {
    check_error = check_parametr(argc, argv);
    if (check_error == -1) {
    } else if (check_error == '?') {
      exit(0);
    } else {
      flags_num++;
    }
  }
  for (j = 1 + flags_num; j < argc; j++) {
    read_file(&argv[j]);
  }
  return 0;
}

int check_parametr(int argc, char *argv[]) {
  int find_flag;
  find_flag = getopt_long(argc, argv, "beEnstTv", long_options, 0);
  if (find_flag != -1) {
    switch (find_flag) {
      case 'b':
        flags.flag_b = 1;
        break;
      case 'e':
        flags.flag_e = 1;
        flags.flag_v = 1;
        break;
      case 'E':
        flags.flag_e = 1;
        break;
      case 'n':
        flags.flag_n = 1;
        break;
      case 's':
        flags.flag_s = 1;
        break;
      case 't':
        flags.flag_t = 1;
        flags.flag_v = 1;
        break;
      case 'T':
        flags.flag_t = 1;
        break;
      case '?':
        break;
    }
  }
  return find_flag;
}

void read_file(char *argv[]) {
  FILE *file_open;
  file_open = fopen(*argv, "r");

  if (file_open == NULL) {
    fprintf(stderr, "s21_cat: %s: No such file or directory\n", *argv);
  } else {
    int count_line = 1;
    int empty_lines = 0;
    char read_char = '\0';
    char last = '\n';
    int counter_for_b = 0;
    while ((read_char = fgetc(file_open)) != EOF) {
      // s
      if (flags.flag_s == 1 && read_char == '\n') {
        if (empty_lines >= 1) {
          continue;
        }
        empty_lines++;
      } else {
        empty_lines = -1;
      }
      // b n
      if ((flags.flag_b != 1 && flags.flag_n == 1 && last == '\n') ||
          (flags.flag_b == 1 && read_char != '\n' && last == '\n')) {
        if (counter_for_b == 1)
          ;
        else {
          fprintf(stdout, "%6d\t", count_line++);
          counter_for_b++;
        }
      }
      // v
      if (flags.flag_v == 1 && read_char != '\t' && read_char != '\n') {
        if (read_char >= 32 && read_char <= 126) {
          fprintf(stdout, "%c", read_char);
          continue;
        } else {
          fprintf(stdout, "^%c", read_char + 64);
          continue;
        }
      }
      // e
      if (flags.flag_e == 1 && read_char == '\n') {
        fprintf(stdout, "%c", '$');
      }
      // t
      if (flags.flag_t == 1 && read_char == '\t') {
        fprintf(stdout, "^I");
        continue;
      }

      fprintf(stdout, "%c", read_char);
      last = read_char;
      counter_for_b = 0;
    }
  }
  fclose(file_open);
}
