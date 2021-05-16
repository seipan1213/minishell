SRCS = *.c
OBJS = $(SRCS:.c=.o)

CC	= gcc
CFLAGS = -Wall -Wextra -Werror
NAME = a.out
ARLIBFT = ../../libft/libft.a

all: $(NAME)

$(NAME):
	gcc ${ARLIBFT} $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

test: re
	./${NAME}
