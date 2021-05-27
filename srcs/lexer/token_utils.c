/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:15:12 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/15 21:15:12 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int		is_meta(char c)
{
	if (c == '\'' || c == '\"' || c == '<' || c == '>' ||
		c == '&' || c == '|' || c == '\\' || c == ';')
		return (1);
	return (0);
}

int	is_metatype(int i)
{
	if (i == PIPE || i == DPIPE || i == AND || i == DAND
		|| i == SCOLON || i == DSCOLON)
		return (1);
	return (0);
}

int	is_rdcttype(int i)
{
	if (i == RDIR || i == RRDIR || i == LDIR || i == LLDIR || i == LLLDIR)
		return (1);
	return (0);
}

t_token	*tokens_last(t_token *t)
{
	if (!t)
		return (NULL);
	while (t->next)
		t = t->next;
	return (t);
}

void	print_tokens(t_token *t)
{
	while (t)
	{
		printf("STR	=	%s	TYPE	=	%d	TOKEN	=	%p	NEXT	=	%p\n", t->str, t->type, t, t->next);
		t = t->next;
	}
}