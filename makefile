CC = cc
CFLAGS = -Wall -Wextra -std=c99 -MMD -MP
LDFLAGS = -lGL -lglut -lGLU -lm
SRC_DIR = src
INCLUDE_DIR = include
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
BINARY = main

all: $(BINARY)

run: $(BINARY)
	./$^

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Include generated dependencies
-include $(OBJECTS:.o=.d)

# Clean up object files, dependency files, and executable
.PHONY: clean clear
clean:
	rm -f $(OBJECTS) $(OBJECTS:.o=.d) $(BINARY)

foda:
	clear && make clean && make && ./$(BINARY)
