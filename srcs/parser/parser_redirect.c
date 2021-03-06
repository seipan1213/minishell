/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:05:07 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/29 21:05:09 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_redirect	*init_redirect(void)
{
	t_redirect	*ret;

	ret = (t_redirect *)malloc(sizeof(t_redirect));
	ret->fd_io = NOT_SPECIFIED;
	ret->fd_file = NOT_SPECIFIED;
	ret->fd_backup = NOT_SPECIFIED;
	ret->type = NOT_SPECIFIED;
	ret->filename = NULL;
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}

void	set_rd_fd(t_redirect *rd)
{
	if (rd->fd_file == NOT_SPECIFIED)
	{
		if (rd->type == RD_INPUT || rd->type == RD_HERE_DOC)
			rd->fd_file = STDIN_FILENO;
		else
			rd->fd_file = STDOUT_FILENO;
	}
}

void	set_rd_type(t_redirect *rd, t_token *token)
{
	if (token->type == LDIR)
		rd->type = RD_INPUT;
	else if (token->type == RDIR)
		rd->type = RD_OUTPUT;
	else if (token->type == RRDIR)
		rd->type = RD_APPEND_OUTPUT;
	else if (token->type == LLDIR)
		rd->type = RD_HERE_DOC;
	set_rd_fd(rd);
}

void	set_cmd_rd(t_redirect *rd, t_redirect **dst)
{
	t_redirect	*dst_tmp;

	if (!*dst)
	{
		*dst = rd;
	}
	else
	{
		dst_tmp = *dst;
		while (dst_tmp->next)
			dst_tmp = dst_tmp->next;
		dst_tmp->next = rd;
		rd->prev = dst_tmp;
		rd->next = NULL;
	}
}
