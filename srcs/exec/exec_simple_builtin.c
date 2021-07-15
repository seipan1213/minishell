/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:03:24 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/14 18:05:01 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	backup_cur_fd(t_redirect *rd)
{
	t_redirect	*rd_now;

	if (!rd)
		return ;
	rd_now = rd;
	while (rd_now)
	{
		if (rd_now->fd_file >= 0)
		{
			rd_now->fd_backup = dup(rd_now->fd_file);
		}
		rd_now = rd_now->next;
	}
}

void	recover_fd(t_redirect *rd)
{
	if (!rd)
		return ;
	while (rd->next)
		rd = rd->next;
	while (rd)
	{
		if (rd->fd_file >= 0)
		{
			close(rd->fd_file);
			dup2(rd->fd_backup, rd->fd_file);
			close(rd->fd_backup);
		}
		rd = rd->prev;
	}
}

int	exec_simple_buildin(t_command *cmd, char **args)
{
	int		ret;

	backup_cur_fd(cmd->rd);
	if (!(get_rd_fd(cmd->rd, FALSE)))
		return (EXIT_FAILURE);
	if (!(change_rd_fd(cmd->rd, FALSE)))
		return (EXIT_FAILURE);
	ret = exec_builtin(args);
	recover_fd(cmd->rd);
	return (ret);
}
