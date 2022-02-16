

CC= gcc 
CFLAGS = -Iinclude -Wall -Wextra -Wshadow -pedantic -g
CSDL = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

DEP_FILE = $(OBJ_DIR)/$*.d
DEPFLAGS = -MT $@ -MMD -MP -MF
OUTPUT = -o $@
SCR_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
EXE = spaceinvaders
LIB = libmy 

SRCS = $(shell find $(SCR_DIR) -name *.c)
OBJS = $(SRCS:$(SCR_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(SRCS:$(SCR_DIR)/%.c=$(OBJ_DIR)/%.d)


$(EXE) : $(OBJS)
	gcc $^ $(CSDL) -o $(EXE)

$(LIB): $(OBJS)
	ar rcs $(LIB) $?

$(OBJ_DIR)/%.o: $(SCR_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ 

all: $(LIB)

clean: 
	rm -rf $(BUILD_DIR)

re: clean all

.PHONY: all clean re
 
$(DEPS):
include $(DEPS)
