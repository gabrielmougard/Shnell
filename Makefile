#configure file directories
BIN_DIR=bin
SRC_DIR=src
INCLUDE_DIR=include

CFLAGS += -Wall -g -I$(INCLUDE_DIR)/

COMPILE=$(CC) $(CFLAGS) -c $^ -o $@

#Create lists of src and object files for src dir
SRC_FILES=$(wildcard $(SRC_DIR)/*.c) #Get .c files in source directory
SRC_OBJS=$(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o, $(SRC_FILES)) #Get name of .o files in source directory

# Create src object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(COMPILE)
