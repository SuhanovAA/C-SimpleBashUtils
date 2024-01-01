CC := gcc 
CFLAGS := -Wall -Wextra -Werror -std=c11 -pedantic -g

FILE := s21_grep
OFILE := s21_grep
TESTSHONE := test_grep_one
TESTSHTWO := test_grep_two

FLAGTEST := -v
TEXTTEST := test/test0.txt
FILETEST := test/test1.txt

.PHONY: all build $(FILE) test docker clean clang rebuild 

all: $(FILE)
build: $(FILE)
rebuild: clean all
test: test2 test1 

$(FILE): $(FILE).c $(FILE).h
	$(CC) $(CFLAGS) -o $(OFILE) $(FILE).c

test1: $(FILE)
	bash $(TESTSHONE).sh

test2: $(FILE)
	bash $(TESTSHTWO).sh

docker:
	sh ../../materials/build/run.sh

leaks:
	leaks -atExit -- ./$(OFILE) $(FLAGTEST) $(TEXTTEST) $(FILETEST)
	
clean: 
	rm -rf $(FILE)
	rm -rf *.o
	rm -rf *.out
	rm -rf .clang-format
	rm -rf *.dSYM
	rm -rf s21_grep
	rm -rf logs

clang:
	rm -rf .clang-format
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	clang-format -i *.c *.h
