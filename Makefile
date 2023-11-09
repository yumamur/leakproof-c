NAME = liblpc.so

CC = clang
CFLAGS = -Wall -Werror -Wextra

HDR	=	lpc.h

SRC	=	lpc_export.c \
		lpc_flush.c

HDR_INT	=	lpc_int.h

SRC_INT	=	lpc_int_addr.c \
			lpc_int_constructor.c \
			lpc_int_destroyer.c \
			lpc_int_errmsg.c \
			lpc_int_load.c \
			lpc_int_storage.c

OBJ = $(patsubst %.c, %.o, $(SRC) $(SRC_INT))

BUILD_DIR = build

TARGET = $(BUILD_DIR)/lib/$(NAME)

.PHONY: all clean fclean re
.INTERMEDIATE: $(OBJ)
.SUFFIXES:
.SILENT:

all: $(TARGET)

dev: CFLAGS += -fsanitize=address -DLPC_DEV=1
dev: NAME := liblpc-dev.so
dev: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR) $(BUILD_DIR)/include $(BUILD_DIR)/lib
	@$(CC) -shared $(CFLAGS) $(OBJ) -o $(TARGET)
	@cp $(HDR) $(BUILD_DIR)/include/

%.o: %.c
	@$(CC) $(CFLAGS) -c -fPIC $< -o $@

clean:
	@rm -rf $(OBJ)

fclean:
	@rm -rf build

re: fclean all

test: all
	@$(CC) $(CFLAGS) test/main.c -L. $(NAME)
