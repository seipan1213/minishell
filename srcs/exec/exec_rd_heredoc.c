/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rd_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:13:01 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/20 16:06:44 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	have_quote(char *deli)
{
	int	i;

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
			back = expand_env((*line) + end);
			expand_line = strjoin_free(expand_line, back);
			end += add_cnt_stop_env((*line) + end);
			start = end;
		}
	}
	*line = expand_line;
}

void	get_heredoc(t_redirect *rd)
{
	int 	q_flag;
	char	*line;
	char	*tmp;

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
		if (*line && !q_flag)
			expand_heredoc(&line);
		if (ft_strcmp(line, rd->filename->str) != 0)
		{
			ft_putendl_fd(line, rd->fd_io);
			free(line);
		}
		else
			return ;
	}
}
