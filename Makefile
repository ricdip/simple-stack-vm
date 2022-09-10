# compiler options
CC = g++
CFLAGS = -pedantic -Wall -Wextra -Werror
CFLAGSDEBUG = -pedantic -Wall -Wextra -Werror -fsanitize=address -g


# sources and objects
SRC = $(shell fd --type f -e cpp)
FILES = $(shell fd --type f -e cpp -e hpp)
OBJ = main.exe
OBJDEBUG = main_debug.exe


# rules
build: $(SRC)
	@echo "*** Building application files ***"
	clang-format -i $(FILES)
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

build_debug: $(SRC)
	@echo "*** Building application files for debug ***"
	$(CC) $(CFLAGSDEBUG) $(SRC) -o $(OBJDEBUG)

clean:
	@echo "*** Cleaning application files ***"
	rm -f $(OBJ)
	rm -f $(OBJDEBUG)

run: build
	@echo "*** Running application ***"
	./$(OBJ)

run_debug: build_debug
	@echo "*** Running debug application ***"
	./$(OBJDEBUG)


.PHONY: build build_debug clean run run_debug
