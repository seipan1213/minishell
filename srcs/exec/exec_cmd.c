/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:02:41 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/14 17:47:03 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	exec_cmdline(t_command *cmd, char **args, \
						t_pipe_status *p_stat, int pipe_fd[])
{
	pid_t	pid;
	int		new_pipe_fd[2];

	if (*p_stat == PIPE_WR_ONLY || *p_stat == PIPE_RD_WR)
	{
		if (pipe(new_pipe_fd) < 0)
			return (FALSE);
	}
	pid = fork();
	if (pid < 0)
		return (FALSE);
	if (pid == 0)
	{
		set_signal(SIG_DFL);
		get_rd_fd(cmd->rd, TRUE);
		dup_pipe(p_stat, pipe_fd, new_pipe_fd);
		change_rd_fd(cmd->rd, TRUE);
		if (is_builtin(args))
			exit(exec_builtin(args));
		else
			exec_bin(args);
	}
	pass_pipe(p_stat, pipe_fd, new_pipe_fd);
	cmd->pid = pid;
	return (TRUE);
}

int	exec_cmd(t_command *cmd, t_pipe_status *p_stat, int pipe_fd[])
{
	char	**args;

	args = token_to_args(cmd->arg);
	if (!*args)
		return (FALSE);
	if (*p_stat == NO_PIPE && is_builtin(args))
	{
		g_data.status = exec_simple_buildin(cmd, args);
	}
	else
		exec_cmdline(cmd, args, p_stat, pipe_fd);
	get_next_p_stat(cmd, p_stat);
	free_split(args);
	return (TRUE);
}

void	exec_pipeline(t_astNode *node)
{
	t_pipe_status	p_stat;
	t_command		*cmd;
	int				pipe_fd[2];

	p_stat = PIPE_WR_ONLY;
	while (node->type == PIPE)
		node = node->left;
	cmd = node->cmd;
	while (cmd)
	{
		exec_cmd(cmd, &p_stat, pipe_fd);
		cmd = cmd->next;
	}
	wait_commands(node->cmd);
}
