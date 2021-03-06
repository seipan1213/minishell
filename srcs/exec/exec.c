/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:11:29 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/21 20:55:47 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_bin(char **args)
{
	char	*path;
	char	**envs;

	envs = environ_gen(g_data.envs);
	if (!envs)
		exit_error(MALLOCERR, NULL, 1);
	path = exec_search(args[0]);
	if (!path)
		exit_error("command not found", args[0], 127);
	execve(path, args, envs);
	free_split(envs);
	free(path);
	exit(1);
}

int	exec_cmd_node(t_astNode *node)
{
	t_pipe_status	p_stat;

	p_stat = NO_PIPE;
	if (node->type == PIPE)
	{
		exec_pipeline(node);
	}
	else
	{
		exec_cmd(node->cmd, &p_stat, NULL);
		wait_commands(node->cmd);
	}
	return (TRUE);
}

int	exec(t_astNode *node)
{
	if (!node)
		return (FALSE);
	if (node->type == SCOLON)
	{
		exec(node->left);
		exec(node->right);
	}
	else
	{
		exec_cmd_node(node);
	}
	return (TRUE);
}
