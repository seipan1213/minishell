SRCS =	srcs/parser/*.c \
		srcs/lexer/*.c
OBJS = $(SRCS:.c=.o)

CC	= gcc
CFLAGS = -Wall -Wextra -Werror
NAME = a.out
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): 
	gcc ${LIBFT} $(SRCS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

test: re
	./${NAME}
