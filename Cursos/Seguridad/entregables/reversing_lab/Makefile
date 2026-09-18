CC = gcc
CFLAGS = -g -O0 -Wall
BIN = bin
SRC = src

all: $(BIN)/safecheck $(BIN)/obfcheck

$(BIN)/safecheck: $(SRC)/safecheck.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $< -o $@
	cp $@ $(BIN)/safecheck_stripped
	- strip $(BIN)/safecheck_stripped

$(BIN)/obfcheck: $(SRC)/obfcheck.c
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN)

.PHONY: all clean
