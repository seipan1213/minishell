SRCSDIR = srcs/
SRCFILE = parser/init_parser.c parser/parser.c \
				parser/parser_utils.c parser/set_cmd_args.c \
				parser/parser_redirect.c parser/free_node.c \
				parser/free_tokens.c \
				lexer/token_utils.c \
				lexer/lexer.c lexer/lexer_check.c lexer/token.c \
				lexer/token_meta_1.c lexer/token_meta_2.c \
				exec/exec.c exec/exec_utils.c exec/exec_cmd.c \
				exec/exec_cmd_utils.c exec/exec_builtin.c \
				exec/exec_rd_utils.c exec/exec_simple_builtin.c \
				exec/exec_path.c exec/exec_rd_heredoc.c \
				exec/exec_expand_delimiter.c \
				builtin/built_env.c builtin/built_echo.c \
				builtin/built_exit.c builtin/built_export.c \
				builtin/built_unset.c builtin/built_pwd.c \
				builtin/built_cd.c \
				env/env_cast.c env/env_sort.c env/env_utils_1.c \
				env/env.c env/env_utils_2.c \
				expand/expand.c expand/expand_utils.c \
				utils/utils.c utils/error.c utils/signal.c utils/init.c \
				minishell.c
CC    = gcc
CFLAGS = -I $(shell brew --prefix readline)/include -Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory -L$(shell brew --prefix readline)/lib
NAME = minishell
LIBFT = ${LIBFTDIR}libft.a
LIBFTDIR = libft/
SRCS = $(addprefix $(SRCSDIR), $(SRCFILE))
OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -g3 -fsanitize=address
debug: re

.PHONY: all clean fclean re
