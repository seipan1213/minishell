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
#include "../includes/minishell.h"

void	test_minishell(char **argv, char **envp)
{
	t_token		*tokens;
	astNode		*node;

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
	astNode		*node;
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
		if (line && ft_strlen(line) > 0)
		{
			add_history(line);
			set_signal(SIG_IGN);
			tokens = NULL;
			tokens = lexer(line);
			node = NULL;
			parser(&tokens, &node);
			ret = exec(node);
			free_node(node);
		}
		if (line)
			free(line);
	}
}
