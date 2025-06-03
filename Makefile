CC = gcc
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    # macOS with Homebrew OpenSSL
    BREW_OPENSSL = $(shell brew --prefix openssl)
    CFLAGS = -Wall -Wextra -O2 -I./src -I$(BREW_OPENSSL)/include
    LDFLAGS = -L$(BREW_OPENSSL)/lib -lcrypto
    EXE =
else ifeq ($(OS),Windows_NT)
    # Windows (MinGW/MSYS2, user must set OPENSSL_DIR)
    OPENSSL_DIR ?= C:/OpenSSL
    CFLAGS = -Wall -Wextra -O2 -I./src -I$(OPENSSL_DIR)/include
    LDFLAGS = -L$(OPENSSL_DIR)/lib -lcrypto
    EXE = .exe
else
    # Linux (assumes OpenSSL is in standard locations)
    CFLAGS = -Wall -Wextra -O2 -I./src
    LDFLAGS = -lcrypto
    EXE =
endif

SRC = src/main.c src/file_scan.c src/hash.c src/duplicate.c src/log.c src/prompt.c
OBJ = $(SRC:.c=.o)
TARGET = out/dia$(EXE)

all: out $(TARGET)

out:
	@mkdir -p out

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) out/dia out/dia.exe

.PHONY: all clean out