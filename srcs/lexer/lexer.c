/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:55:18 by sehattor          #+#    #+#             */
/*   Updated: 2021/05/14 19:55:18 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int		lexer_str(t_token *t)
{
	t_token	*tmp;
	char		*str;

	while(t && t->next)
	{
		while (t->next && t->type == t->next->type && t->type == STR)
		{
			if (!(str = ft_strjoin(t->str, t->next->str)))
				return (put_error(MALLOCERR, 0));
			free(t->str);
			t->str = str;
			tmp = t->next;
			t->next = t->next->next;
			free(tmp->str);
			free(tmp);
		}
		t = t->next;
	}
	return (1);
}

void		lexer_space(t_token *t)
{
	t_token	*tmp;

	while(t && t->next)
	{
		if (t->next->type == SPACE)
		{
			tmp = t->next;
			t->next = tmp->next;
			free(tmp->str);
			free(tmp);
		}
		else
			t = t->next;
	}
}

int		lexer_tokens(t_token *t)
{
	int	ret;

	ret = lexer_str(t);
	lexer_space(t);
	return (ret);
}

t_token		*lexer(char *line)
{
	t_token	*t;
	int			ret;

	ret = 1;
	t = tokenise(line);
	ret = check_tokens(t);
	lexer_tokens(t);
	//print_tokens(t);
	if (ret == 0)
		return (NULL);
	return (t);
}