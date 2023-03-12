include config.mk

.DEFAULT_GOAL := help

.SILENT: help
.PHONY: help # display this help message
help:
	@grep -E '^.PHONY:.+#.+' Makefile | sed 's/.PHONY: //' | awk -F ' # ' '{printf "%-15s %s\n", $$1, $$2}'

.PHONY: build # build application
build: $(SRC)
	@echo "*** Building application files ***"
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

.PHONY: build_debug # build debug application
build_debug: $(SRC)
	@echo "*** Building application files for debug ***"
	$(CC) $(CFLAGSDEBUG) $(SRC) -o $(OBJDEBUG)

.PHONY: clean # clean application files
clean:
	@echo "*** Cleaning application files ***"
	rm -f $(OBJ)
	rm -f $(OBJDEBUG)

.PHONY: run # run application
run: build
	@echo "*** Running application ***"
	./$(OBJ)

.PHONY: run_debug # run debug application
run_debug: build_debug
	@echo "*** Running debug application ***"
	./$(OBJDEBUG)

.PHONY: format # format source files
format:
	clang-format -i $(FILES)
