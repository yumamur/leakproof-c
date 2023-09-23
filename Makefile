NAME = libleakproof.so

CC = clang
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

HDR = leakproof.h \
	  leakproof_int.h

SRC = leakproof_export.c \
	  leakproof_int_utils.c \
	  leakproof_int_civilwork.c

OBJ = $(SRC:.c=.o)

.PHONY = all clean fclean re

all: $(NAME)

$(NAME): $(HDR) $(OBJ)
	@$(CC) -shared -Wl,-soname,libleakproof.so -o $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c -fPIC $< -o $@

clean:
	@rm -rf $(OBJ)

fclean:
	@rm -rf $(OBJ) $(NAME)

re: fclean all

test: all
	@$(CC) $(CFLAGS)
