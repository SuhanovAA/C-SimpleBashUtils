CC := gcc 
CFLAGS := -Wall -Wextra -Werror -std=c11 -pedantic -g

FILE := s21_cat
OFILE := s21_cat
TESTSH := test_cat

FLAGTEST := -n
TEXTTEST := test/test1.txt
FILETEST := test/test2.txt


.PHONY: all build $(FILE) test docker clean clang rebuild 

all: $(FILE)
build: $(FILE)
rebuild: clean all

$(FILE): $(FILE).c $(FILE).h
	$(CC) $(CFLAGS) -o $(OFILE) $(FILE).c

test: $(FILE)
	bash $(TESTSH).sh

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
	rm -rf $(OFILE)

clang:
	rm -rf .clang-format
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	clang-format -i *.c *.h



