## ---- Project settings ----
TARGET   := app

SRC_DIR  := src
INC_DIR  := headers
BUILD_DIR:= build

CC       := gcc
CFLAGS   := -Wall -Wextra -std=c11 -g -I$(INC_DIR)
LDFLAGS  :=

## ---- Sources (auto-detected) ----
## Every .c file in src/ is picked up automatically.
## Just drop a new .c file in src/ (and its .h in headers/) later --
## no need to edit this Makefile.
SRCS     := $(wildcard $(SRC_DIR)/*.c)
OBJS     := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS     := $(OBJS:.o=.d)

## ---- Rules ----
.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Compile each src/*.c into build/*.o, auto-generating header dependencies
# (-MMD) so editing a .h in headers/ triggers a rebuild of the right files.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)