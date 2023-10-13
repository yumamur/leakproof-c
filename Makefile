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

OBJ = $(patsubst %.c, obj/%.o, $(SRC))
OBJ += $(patsubst %.c, obj/%.o, $(SRC_INT))

.PHONY = all clean fclean re

all: create_dir $(NAME)

dev: CFLAGS += -fsanitize=address
dev: NAME := liblpc-dev.so
dev: create_dir $(NAME)

$(NAME): $(HDR) $(OBJ)
	@$(CC) -shared $(CFLAGS) $(OBJ) -o $(NAME)

obj/%.o: %.c
	@$(CC) $(CFLAGS) -c -fPIC $< -o $@

create_dir:
	@mkdir -p obj

clean:
	@rm -rf obj/

fclean:
	@rm -rf obj/ $(NAME) liblpc-dev.so

re: fclean all

test: all
	@$(CC) $(CFLAGS)
