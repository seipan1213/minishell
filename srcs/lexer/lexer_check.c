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

int		check_syntax(t_token *t)
{
	t_ttype	pre_type;

	pre_type = -1;
	while (t->next)
	{
		while (t->type == SP && t->next)
			t = t->next;
		if ((is_metatype(t->type) && is_rdcttype(pre_type))
			|| (is_metatype(pre_type) && is_rdcttype(t->type))
			|| (is_metatype(t->type) && is_metatype(pre_type))
			|| (is_rdcttype(t->type) && is_rdcttype(pre_type))
			|| (is_metatype(t->type) && pre_type == -1)
			|| t->type == DSCOLON)
			return (put_error(SYNTAXERR, 0));
		pre_type = t->type;
		if (t->next)
			t = t->next;
	}
	if (t && (is_rdcttype(t->type) || t->type == PIPE || t->type == ESCAPE ||
			t->type == SCOLON || t->type == DSCOLON))
		return (put_error(SYNTAXERR, 0));
	return (1);
}

int		check_avoid(t_token *t)
{
	while (t)
	{
		if (t->type == DAND || t->type == DPIPE || t->type == LLLDIR)
			return (put_error(SYNTAXERR, 0));
		t = t->next;
	}
	return (1);
}

int		check_tokens(t_token *t)
{
	return (check_syntax(t) && check_avoid(t));
}