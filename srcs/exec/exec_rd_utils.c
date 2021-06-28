
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
		O_RDWR | O_CREAT | O_TRUNC, 0664));
	}
	return(-1);
}

int	get_rd_fd(t_redirect *rd, int is_child)
{
	t_redirect	*rd_now;

	if (!rd)
		return (TRUE);
	rd_now = rd;
	while (rd_now)
	{
		if ((rd_now->fd_io = open_rdfile(rd_now)) < 0)
		{
			if (is_child)
				exit_error(strerror(errno), rd_now->filename->str, 1);
			else
				return (put_error(strerror(errno), rd_now->filename->str, FALSE));
		}
		if (rd_now->type == RD_HERE_DOC)
			get_heredoc(rd);
		rd_now = rd_now->next;
	}
	return (TRUE);
}

void	dup_fd(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

void	change_rd_fd(t_redirect *rd)
{
	t_redirect	*rd_now;

	if (!rd)
		return ;
	rd_now = rd;
	while (rd_now)
	{
		if (rd_now->type == RD_HERE_DOC)
		{
			close(rd_now->fd_io);
			rd_now->fd_io = open(HD_TMPFILE, O_RDWR);
		}
		dup_fd(rd_now->fd_io, rd_now->fd_file);
		if (rd_now->type == RD_HERE_DOC)
			unlink(HD_TMPFILE);
		rd_now = rd_now->next;
	}
}
