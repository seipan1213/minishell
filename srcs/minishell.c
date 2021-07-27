/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:02:20 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/30 16:02:20 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/const.h"
#include "../libft/libft.h"
#include "../includes/parser.h"
#include "../includes/exec.h"
#include "../includes/lexer.h"
#include "../includes/utils.h"
#include "../includes/minishell.h"

void	test_minishell(char **argv)
{
	t_token		*tokens;
	t_astNode	*node;

	tokens = NULL;
	tokens = lexer(argv[2]);
	node = NULL;
	parser(&tokens, &node);
	exec(node);
	exit(g_data.status);
}

void	launch_minishell(char *line)
{
	t_token		*tokens;
	t_astNode	*node;

	add_history(line);
	set_signal(SIG_IGN);
	tokens = NULL;
	tokens = lexer(line);
	node = NULL;
	parser(&tokens, &node);
	exec(node);
	free_node(&node);
}

void	minishell(void)
{
	char		*line;

	while (1)
	{
		set_prompt_signal();
		line = readline(MINISHELL);
		if (!line)
		{
			free(line);
			g_data.quit = 1;
			built_exit(NULL);
		}
		if (line && ft_strlen(line) > 0)
		{
			launch_minishell(line);
		}
		if (line)
			free(line);
	}
}

int	main(int argc, char **argv)
{
	init_data();
	if (argc == 1)
		minishell();
	else if (argc > 2 && (ft_strcmp(argv[1], "-c") == 0))
		test_minishell(argv);
}
