CC = gcc
CFLAGS = -Wall -Iinclude -MMD
SRC = src/main.c src/scheduler.c src/generator.c src/file_loader.c src/output_writer.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
EXEC = probsched

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) -lm

run: $(EXEC)
	./$(EXEC)

test: $(EXEC)
	./$(EXEC) < input.txt

debug: CFLAGS += -g
debug: clean $(EXEC)
	gdb ./$(EXEC)

valgrind: $(EXEC)
	valgrind ./$(EXEC)

clean:
	rm -f $(EXEC) src/*.o src/*.d

-include $(DEP)


