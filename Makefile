#output dir
OUTPUT_DIR = obj

#tools
CC = gcc
CFLAGS = -c

all: check_out_dir run_server

check_out_dir :
	mkdir -p ${OUTPUT_DIR}

run_server: $(OUTPUT_DIR)/parse.o $(OUTPUT_DIR)/sequence.o $(OUTPUT_DIR)/main.o
	$(CC) $(OUTPUT_DIR)/parse.o $(OUTPUT_DIR)/sequence.o $(OUTPUT_DIR)/main.o -o run_server -lm

$(OUTPUT_DIR)/parse.o: parse.c
	$(CC) $(CFLAGS) parse.c -o $(OUTPUT_DIR)/parse.o

$(OUTPUT_DIR)/sequence.o: sequence.c
	$(CC) $(CFLAGS) sequence.c -o $(OUTPUT_DIR)/sequence.o

$(OUTPUT_DIR)/main.o: main.c
	$(CC) $(CFLAGS) main.c -o $(OUTPUT_DIR)/main.o

clean:
	rm -rf $(OUTPUT_DIR) run_server

.PHONY: all  check_out_dir run_server clean 
