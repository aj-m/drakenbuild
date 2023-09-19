NAME=hello-world-gtk
SRC_DIR=src
BIN_DIR=bin
OUT_DIR=build
CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk4)
LDLIBS = $(shell pkg-config --libs gtk4)

.PHONY : all
all : $(OUT_DIR)/$(NAME)

$(OUT_DIR)/$(NAME) : $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/gamedata.c $(SRC_DIR)/main.c $(LDLIBS)

.PHONY : clean
clean :
	$(RM) $(OUT_DIR)/$(NAME)

