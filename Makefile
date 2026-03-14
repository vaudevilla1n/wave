CFLAGS = -Wall -Wextra -Wpedantic -g3 -std=c99
LDFLAGS = -lraylib -lm -lX11

BIN := wave 

.PHONY: all clean

all: $(BIN)

$(BIN): %: %.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(BIN)
