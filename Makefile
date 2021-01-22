CC = g++
FLAGS := -g -pthread -O2 -Wpedantic -Wall -pedantic-errors -std=c++17
LIBS := -lwiringPi -lpthread
OUT = prog.out

SRC = $(wildcard *.cpp)
INC = $(wildcard *.h)

$(OUT): $(SRC) $(INC)
	$(CC) $(FLAGS) $(LIBS) -o $(OUT) $(SRC)

clean:
	rm -fv $(OUT)

run: $(OUT)
	./$(OUT)

all:	$(OUT) run
