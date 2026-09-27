## ---- Project settings ----
TARGET   := app

SRC_DIR  := src
INC_DIR  := headers
BUILD_DIR:= build

CC       := gcc

## Every subfolder under headers/ (e.g. headers/teacher) is added as its
## own -I path, so a .c file can #include "teacherDashboard.h" without
## needing the "teacher/" prefix. Built by globbing for .h files and taking
## just their directory ($(dir ...)), rather than relying on a trailing-slash
## wildcard match -- that directory-only filtering isn't reliable in
## mingw32-make on Windows and can pick up individual files as "directories".
## Add another wildcard line below if you ever nest folders deeper than
## headers/<feature>/<file>.h.
INC_DIRS := $(sort $(INC_DIR) $(dir $(wildcard $(INC_DIR)/*/*.h)) $(dir $(wildcard $(INC_DIR)/*/*/*.h)))
CFLAGS   := -Wall -Wextra -std=c11 -g $(addprefix -I,$(INC_DIRS))
LDFLAGS  :=

## ---- Sources (auto-detected) ----
## Every .c file in src/ is picked up automatically, including files in
## subfolders such as src/teacher. Just drop a new .c file in the right
## src/ folder (and its .h in the matching headers/ folder) later --
## no need to edit this Makefile. Add another wildcard line below if you
## ever nest folders deeper than src/<feature>/<file>.c.
SRCS     := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c) $(wildcard $(SRC_DIR)/*/*/*.c)
OBJS     := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS     := $(OBJS:.o=.d)

## ---- OS-aware shell commands ----
## mingw32-make runs recipes through cmd.exe on Windows, whose builtin
## mkdir/rm don't take Unix flags like -p / -rf. Pick the right syntax
## for whichever OS is actually running make.
ifeq ($(OS),Windows_NT)
    TARGET   := $(TARGET).exe
    MKDIR    = if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
    RM_RF    = if exist "$(subst /,\,$1)" rmdir /s /q "$(subst /,\,$1)"
    RM_F     = if exist "$1" del /q "$1"
else
    MKDIR    = mkdir -p $1
    RM_RF    = rm -rf $1
    RM_F     = rm -f $1
endif

## ---- Rules ----
.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Compile each src/**.c into a matching build/**.o, auto-generating header
# dependencies (-MMD) so editing a .h triggers a rebuild of the right files.
# The mkdir call recreates the source's subfolder layout (e.g. build/teacher/)
# on demand, so no separate directory rule is needed.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(call MKDIR,$(dir $@))
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

run: $(TARGET)
	./$(TARGET)

clean:
	@$(call RM_RF,$(BUILD_DIR))
	@$(call RM_F,$(TARGET))