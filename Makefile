NAME = liblpc.so

CC = clang
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

HDR = lpc.h \
	  lpc_int.h

SRC = lpc_export.c \
	  lpc_int_constructor.c \
	  lpc_int_errmsg.c \
	  lpc_int_load.c \
	  lpc_int_load_destroyer.c \
	  lpc_int_storage.c

OBJ = $(patsubst %.c, obj/%.o, $(SRC))

.PHONY = all clean fclean re

all: create_dir $(NAME)

$(NAME): $(HDR) $(OBJ)
	@$(CC) -shared $(CFLAGS) -o $(NAME) $(OBJ)

obj/%.o: %.c
	@$(CC) $(CFLAGS) -c -fPIC $< -o $@

create_dir:
	@mkdir -p obj

clean:
	@rm -rf obj/

fclean:
	@rm -rf obj/ $(NAME)

re: fclean all

test: all
	@$(CC) $(CFLAGS)
