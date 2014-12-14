# file:   Makefile
# author: Scott Cheloha <scottcheloha@gmail.com>

# Makefile for vc (vowelcount)

OUT = -o vc
SRC = vowelcount.c

all: $(SRC)
	cc -O2 $(SRC) $(OUT)

.phony: clean

clean:
	rm -f vc
