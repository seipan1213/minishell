/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:02:09 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/17 20:29:46 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"

void	addnext_token(t_token **lst, t_token *t)
{
	t_token	*tmp;

	tmp = (*lst)->next;
	(*lst)->next = t;
	t->next = tmp;
}

void	expand_div(t_token **lst, char *str, int flag)
{
	t_token	*t;
	t_token	*token;
	t_token	*tmp;

	if (!flag)
	{
		(*lst)->str = front_join((*lst)->str, str);
		if (!(*lst)->str)
			exit_error(MALLOCERR, NULL, 1);
		return ;
	}
	t = tokenise(str);
	free(str);
	lexer_tokens(t);
	tmp = t;
	while (t)
	{
		(*lst)->str = front_join((*lst)->str, ft_strdup(t->str));
		t = t->next;
		if (t)
		{
			token = create_token(STR, ft_strdup(""));
			if (!token)
				exit_error(MALLOCERR, NULL, 1);
			addnext_token(lst, token);
			*lst = (*lst)->next;
		}
	}
	if (tmp)
		free_token(tmp);
}