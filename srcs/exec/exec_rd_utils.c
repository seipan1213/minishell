/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:03:19 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/27 18:35:01 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	open_rdfile(t_redirect *rd)
{
	if (rd->type == RD_INPUT)
		return (open(rd->filename->str, O_RDONLY));
	else if (rd->type == RD_OUTPUT)
	{
		return (open(rd->filename->str, \
					O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE));
	}
	else if (rd->type == RD_APPEND_OUTPUT)
	{
		return (open(rd->filename->str, \
					O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE));
	}
	else if (rd->type == RD_HERE_DOC)
	{
		return (open(HD_TMPFILE, \
					O_RDWR | O_CREAT | O_TRUNC, 0644));
	}
	return (OPEN_ERR);
}

void	start_heredoc(t_redirect *rd, int is_child)
{
	pid_t	pid;
	int		status;

	if (is_child)
	{
		set_heredoc_sig();
		get_heredoc(rd);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			set_heredoc_sig();
			get_heredoc(rd);
			exit(EXIT_SUCCESS);
		}
		if (waitpid(pid, &status, 0) < 0)
		{
			exit_error(strerror(errno), NULL, errno);
		}
		handler_singal(status, WIFSIGNALED(status));
	}
	set_signal(SIG_IGN);
}

int	if_signal(t_redirect *rd, int is_child)
{
	if (is_child)
		return (0);
	if (g_data.status == 130)
	{
		unlink(HD_TMPFILE);
		close(rd->fd_io);
	}
	return (g_data.status);
}

int	get_rd_fd(t_redirect *rd, int is_child)
{
	t_redirect	*now;

	if (!rd)
		return (EXIT_SUCCESS);
	now = rd;
	while (now)
	{
		now->fd_io = open_rdfile(now);
		if (now->fd_io < 0)
		{
			if (is_child)
				exit_error(strerror(errno), now->filename->str, EXIT_FAILURE);
			else
				return (put_error(strerror(errno), \
						now->filename->str, EXIT_FAILURE));
		}
		if (now->type == RD_HERE_DOC)
		{
			start_heredoc(now, is_child);
			if (g_data.status >= 128)
				return (if_signal(now, is_child));
		}
		now = now->next;
	}
	return (EXIT_SUCCESS);
}

int	change_rd_fd(t_redirect *rd, int is_child)
{
	t_redirect	*rd_now;

	if (!rd)
		return (TRUE);
	rd_now = rd;
	while (rd_now)
	{
		if (rd_now->type == RD_HERE_DOC)
		{
			close(rd_now->fd_io);
			rd_now->fd_io = open(HD_TMPFILE, O_RDWR);
		}
		if (dup2(rd_now->fd_io, rd_now->fd_file) < 0)
		{
			if (is_child)
				exit_error(strerror(errno), NULL, EXIT_FAILURE);
			else
				return (put_error(strerror(errno), NULL, FALSE));
		}
		close(rd_now->fd_io);
		if (rd_now->type == RD_HERE_DOC)
			unlink(HD_TMPFILE);
		rd_now = rd_now->next;
	}
	return (TRUE);
}
