CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/scheduler.c src/generator.c
OBJ = $(SRC:.c=.o)
EXEC = probsched

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -f $(EXEC) *.o
