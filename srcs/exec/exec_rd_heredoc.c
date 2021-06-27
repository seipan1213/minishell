#include "../../includes/exec.h"

int	have_quote(char *deli)
{
	int i;

	i = 0;
	while (deli[i])
	{
		if (is_quote(deli[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	expand_heredoc(char **line)
{
	int		start;
	int		end;
	char	*front;
	char	*back;
	char	*expand_line;

	start = 0;
	end = 0;
	expand_line = NULL;
	while ((*line)[end])
	{
		while ((*line)[end] != '$' && (*line)[end])
			end++;
		front = ft_substr(*line, start, end - start);
		expand_line = strjoin_free(expand_line, front);
		if ((*line)[end])
		{
			back = expand_env((*line) + end, g_data.envs);
			expand_line = strjoin_free(expand_line, back);
			end += add_cnt_stop_env((*line) + end);
			start = end;
		}
	}
	*line = expand_line;
}

void	get_heredoc(t_redirect *rd)
{
	int		q_flag;
	char	*line;
	char	*tmp;
	t_quote	*point;

	q_flag = 0;
	if (have_quote(rd->filename->str))
	{
		q_flag = 1;
		tmp = expand_delimiter(rd->filename->str);
		free(rd->filename->str);
		rd->filename->str = tmp;
	}
	while (write(STDOUT_FILENO, "> ", 2) && get_next_line(0, &line) > 0)
	{
		if (!q_flag)
			expand_heredoc(&line);
		if (ft_strcmp(line, rd->filename->str) != 0)
		{
			write(rd->fd_io, line, ft_strlen(line));
			write(rd->fd_io, "\n", 1);
			free(line);
		}
		else
			return ;
	}
}