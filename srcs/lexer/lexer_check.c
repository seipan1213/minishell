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

int	check_syntax(t_token *t)
{
	t_ttype	pre_type;

	pre_type = -1;
	if (is_metatype(t->type))
		return (put_error(SYNTAXERR, NULL, 0));
	while (t->next)
	{
		while (t->type == SP && t->next)
			t = t->next;
		if ((is_metatype(t->type) && is_rdcttype(pre_type))
			|| (is_metatype(pre_type) && is_rdcttype(t->type))
			|| (is_metatype(t->type) && is_metatype(pre_type))
			|| (is_rdcttype(t->type) && is_rdcttype(pre_type))
			|| (is_metatype(t->type) && (int)pre_type == -1))
			return (put_error(SYNTAXERR, NULL, 0));
		pre_type = t->type;
		if (t->next)
			t = t->next;
	}
	if (t->type != SP)
		pre_type = t->type;
	if (t && (is_rdcttype(pre_type) || pre_type == PIPE || pre_type == ESCAPE))
		return (put_error(SYNTAXERR, NULL, 0));
	return (1);
}

int	check_avoid(t_token *t)
{
	int	len;

	while (t)
	{
		if (t->type == STR && (t->str[0] == '\"' || t->str[0] == '\''))
		{
			len = ft_strlen(t->str);
			if (len < 2 || t->str[len - 1] != t->str[0])
				return (put_error(SYNTAXERR, NULL, 0));
		}
		if (t->type == DAND || t->type == DPIPE || t->type == LLLDIR ||\
				t->type == AND || t->type == ESCAPE || t->type == DSCOLON)
			return (put_error(SYNTAXERR, NULL, 0));
		t = t->next;
	}
	return (1);
}

int	check_tokens(t_token *t)
{
	return (check_syntax(t) && check_avoid(t));
}
