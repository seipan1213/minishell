/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:55:21 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/14 19:55:21 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	check_qoute(int *flag, int type)
{
	if (type == SQUOTE)
		*flag ^= 1;
	else if (type == DQUOTE)
		*flag ^= 2;
}

int		check_syntax(t_token *t)
{
	t_ttype	pre_type;
	int		quote_flag;

	pre_type = -1;
	quote_flag = 0;
	while (t)
	{
		while (t->type == SPACE && t->next)
			t = t->next;
		check_qoute(&quote_flag, t->type);
		if ((is_metatype(t->type) && is_rdcttype(pre_type))
			|| (is_metatype(pre_type) && is_rdcttype(t->type))
			|| (is_metatype(t->type) && is_metatype(pre_type))
			|| (is_rdcttype(t->type) && is_rdcttype(pre_type))
			|| (is_metatype(t->type) && pre_type == -1)
			|| t->type == DSCOLON)
			return (put_error(SYNTAXERR, -1));
		pre_type = t->type;
		if (t)
			t = t->next;
	}
	if (quote_flag != 0 || (t &&
		(is_rdcttype(t->type) || t->type == PIPE || t->type == ESC)))
		return (put_error(SYNTAXERR, -1));
	return (0);
}

int		check_avoid(t_token *t)
{
	while (t)
	{
		if (t->type == DAND || t->type == DPIPE || t->type == LLLDIR)
			return (put_error(SYNTAXERR, -1));
		t = t->next;
	}

}

int		check_tokens(t_token *t)
{
	return (check_syntax(t) || check_avoid(t));
}