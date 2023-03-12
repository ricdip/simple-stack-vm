include config.mk

.DEFAULT_GOAL := help

.SILENT: help
.PHONY: help # Display this help message
help:
	@grep -E '^.PHONY:.+#.+' Makefile | sed 's/.PHONY: //' | awk -F ' # ' '{printf "%-15s %s\n", $$1, $$2}'

.PHONY: build # Build application
build: $(SRC)
	@echo "*** Building application files ***"
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

.PHONY: build_debug # Build debug application
build_debug: $(SRC)
	@echo "*** Building application files for debug ***"
	$(CC) $(CFLAGSDEBUG) $(SRC) -o $(OBJDEBUG)

.PHONY: clean # Clean application files
clean:
	@echo "*** Cleaning application files ***"
	rm -f $(OBJ)
	rm -f $(OBJDEBUG)

.PHONY: run # Run application
run: build
	@echo "*** Running application ***"
	./$(OBJ)

.PHONY: run_debug # Run debug application
run_debug: build_debug
	@echo "*** Running debug application ***"
	./$(OBJDEBUG)

.PHONY: format # Format source files
format:
	clang-format -i $(FILES)
