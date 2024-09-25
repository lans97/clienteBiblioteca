######################
#   Old Compile.sh   #
######################
# if [ ! -d "bin/" ]
# then
#     mkdir bin
#     if [ ! -d  "bin/int/" ]
#     then
#         mkdir bin/int
#     fi
# fi
#
# gcc `pkg-config --cflags gtk+-3.0` -o bin/BibClient src/*.c `pkg-config --libs gtk+-3.0` -lnsl -lm -lz -lmysqlclient -rdynamic
#
######################
#    Old Debug.sh    #
######################
# if [ ! -d "bin/" ]
# then
#     mkdir bin
#     if [ ! -d  "bin/int/" ]
#     then
#         mkdir bin/int
#     fi
# fi
#
# gcc `pkg-config --cflags gtk+-3.0` -g -o bin/BibClient src/*.c `pkg-config --libs gtk+-3.0` -lnsl -lm -lz -lmysqlclient
#
######################
#    New Makefile    #
######################
# Compiler and flags
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -I src/
LDFLAGS = `pkg-config --libs gtk+-3.0` -lnsl -lm -lz -lmysqlclient -rdynamic

# Dirs
SRC_DIR = src
OBJ_DIR = bin/int
BIN_DIR = bin

# Target bin
TARGET = $(BIN_DIR)/BibClient

# Source and obj's
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Rule: Build bin
all: $(TARGET)

# Rule: Create bin
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Rule: Compile obj's
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create dirs
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule: Debug
debug: CFLAGS += -g
debug: CFLAGS += -DDEBUG
debug: $(TARGET)

# Cleanup
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Deep clean
distclean: clean
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: all clean distclean debug

