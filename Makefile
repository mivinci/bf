BIN=bf
DIR=/usr/local/bin/
.PHONY: install, uninstall


all: $(BIN)


$(BIN):
	gcc main.c -o $@


install:
	cp $(BIN) $(DIR)


uninstall:
	rm $(DIR)$(BIN)