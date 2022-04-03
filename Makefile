TARGET = ./main.out
HDRS_DIR = project/include
TEST = ./test.out

SRCS = \
		project/src/main.c \
		project/src/logic.c \
		project/src/print_manager.c \
		project/src/scan_manager.c \
		project/src/file_write_manager.c \
		project/src/record_manager.c

TEST_SRCS = \
		project/test/test.c \
		project/src/file_write_manager.c \
		project/src/scan_manager.c

.PHONY: all build rebuild check test memtest build_test custom_test clean

all: clean check test memtest build_test custom_test

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

$(TEST): $(TEST_SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TEST) $(CFLAGS) $(TEST_SRCS)

build: $(TARGET)

build_test: $(TEST)

rebuild: clean build

check:
	./run_linters.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) *.dat

custom_test:
	./test.out
