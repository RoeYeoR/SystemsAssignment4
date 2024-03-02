CC = gcc
CFLAGS = -Wall 
EXEC = digitcompress

all: $(EXEC)

$(EXEC): compress.o encodemain.o
    $(CC) $(CFLAGS) $^ -o $@

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f *.o $(EXEC)
