
#include "../../includes/exec.h"

void	get_heredoc(t_redirect *rd)
{
	char	*line;
	while (get_next_line(0, &line) < 0)
	{
		
	}
}

int	open_file(t_redirect *rd)
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
		return(open(".tmpfile", \
		O_RDONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE));
	}
	return(-1);
}

void	get_rd_fd(t_redirect *rd)
{
	t_redirect	*rd_now;

	if (!rd)
		return ;
	rd_now = rd;
	while (rd_now)
	{
		if ((rd_now->fd_io = open_file(rd_now)) < 0)
			return ;
		rd_now = rd_now->next;
	}
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
		dup_fd(rd_now->fd_io, rd_now->fd_file);
		rd_now = rd_now->next;
	}
}
