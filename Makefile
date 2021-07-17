#paths
INCLUDE = ./include
SRC = ./src

#compiler
CC = g++

#compile options
CPPFLAGS = -Wall -Werror -Wextra -std=c++11 -ggdb -I$(INCLUDE)

OBJS = $(SRC)/main.o \
	$(SRC)/Items.o \
	$(SRC)/Spells.o \
	$(SRC)/HeroesTeam.o \
	$(SRC)/Grid.o \
	$(SRC)/Database.o \
	$(SRC)/Market.o \
	$(SRC)/Heroes.o \
	$(SRC)/Monsters.o \
	$(SRC)/Location.o

EXEC = main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC)

valgrind: $(EXEC)
	valgrind ./$(EXEC)
