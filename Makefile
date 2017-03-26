CC:=gcc
CFLAGS:=-Wall -std=c99
LIBS:=-lm

all: lab2

lab2: lab2.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $@.c

test: lab2
	@./test_harness lab2 examples

handin:
	@echo "Turning in the following files..."
	@tar cvzf `whoami`-lab2.tgz lab2.c Makefile
	@cp `whoami`-lab2.tgz /home/khale/HANDIN/lab2
	@echo "You can run 'ls /home/khale/HANDIN/lab2/<yourid>-lab2.tgz' to make sure your file made it to the HANDIN dir"

clean:
	rm -f lab2

.PHONY: clean test handin

