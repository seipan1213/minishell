SRCSDIR = srcs/
SRCFILE = parser/init_parser.c parser/parser.c \
				parser/parser_utils.c parser/parser_free.c \
				parser/set_cmd_args.c parser/parser_redirect.c \
				lexer/token_utils.c lexer/error.c \
				lexer/lexer.c lexer/lexer_check.c lexer/token.c \
				lexer/token_meta_1.c lexer/token_meta_2.c \
				exec/exec.c exec/exec_utils.c exec/exec_cmd.c \
				exec/exec_cmd_utils.c exec/exec_buildin.c \
				buildin/build_env.c buildin/build_echo.c \
				buildin/build_exit.c buildin/build_export.c \
				buildin/build_unset.c buildin/build_pwd.c \
				env/env_cast.c env/env_sort.c env/env_utils.c \
				env/env.c \
				utils/utils.c \
				minishell.c
CC    = gcc
CFLAGS = #-Wall -Wextra -Werror
NAME = minishell
LIBFT = ${LIBFTDIR}libft.a
LIBFTDIR = libft/
SRCS = $(addprefix $(SRCSDIR), $(SRCFILE))
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: re
	./${NAME}

.PHONY: all clean fclean re