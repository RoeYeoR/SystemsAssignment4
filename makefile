CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
EXEC = digitcompress

all: $(EXEC)

$(EXEC): compress.o encodemain.o
    $(CC) $(CFLAGS) $^ -o $@

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f *.o $(EXEC)
