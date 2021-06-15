#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"
#include "../includes/parser.h"
#include "../includes/exec.h"
#include "../includes/lexer.h"
#include "../includes/utils.h"

#define STDERR 2
#define MINISHELL "MINISHELL$ "

void		minishell(char **envp);
void		sig_int_input();
void		sig_quit_input();


void	test_minishell(char **argv, char **envp)
{
	t_token		*tokens = NULL;
	astNode		*node = NULL;

	tokens = NULL;
	tokens = lexer(argv[2]);
	node = NULL;
	parser(&tokens, &node);
	exec(node);
	exit(g_data.status);
}

int		main(int argc, char **argv, char **envp)
{
	g_data.envs = envs_init();
	if (argc == 1)
		minishell(envp);
	else if (argc > 2 && (ft_strcmp(argv[1], "-c") == 0))
		test_minishell(argv, envp);
}

void	minishell(char **envp)
{
	t_token		*tokens;
	astNode		*node = NULL;
	char		*line;
	int			ret;
	t_command	*tmp;

	ret = 0;
	while (1)
	{
		set_signal(SIG_DFL);
		line = readline(MINISHELL);
		if (!line)
		{
			g_data.quit = 1;
			built_exit(NULL);
		}
		// rl_on_new_line();
		if (line && ft_strlen(line) > 0)
		{
			add_history(line);
			set_signal(SIG_IGN);
			tokens = NULL;
			tokens = lexer(line);
			node = NULL;
			parser(&tokens, &node);
			ret = exec(node);
		}
		if (line)
			free(line);
	}
}

void	sig_int_input()
{
	ft_putstr_fd("\b\b  \b\n", STDERR);
	ft_putstr_fd(MINISHELL, STDERR);
}

void	sig_quit_input()
{
	ft_putstr_fd("\b\b  \b\b", STDERR);
}
