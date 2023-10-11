NAME = liblpc.a

CC = clang
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

HDR = lpc.h \
	  lpc_int.h

SRC = lpc_export.c \
	  lpc_int_constructor.c \
	  lpc_int_errmsg.c \
	  lpc_int_load.c \
	  lpc_int_storage.c

OBJ = $(patsubst %.c, obj/%.o, $(SRC))

.PHONY = all clean fclean re

all: $(NAME)

# $(NAME): $(HDR) $(OBJ)
# 	@$(CC) -shared -Wl,-soname,libleakproof.so -o $(NAME) $(OBJ)

# %.o: %.c
# 	@$(CC) $(CFLAGS) -c -fPIC $< -o $@

$(NAME): $(HDR) $(SRC) | $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

$(OBJ): $(SRC) create_dir
	@for i in $@; do \
		src_file=$$(echo $$i | sed 's,obj/,,' | sed 's,\.o,\.c,'); \
		$(CC) $(CFLAGS) -c $$src_file -o $$i; \
	done

create_dir:
	@mkdir -p obj

clean:
	@rm -rf obj/

fclean:
	@rm -rf obj/ $(NAME)

re: fclean all

test: all
	@$(CC) $(CFLAGS)
