/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:02:09 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/19 17:58:01 by sehattor         ###   ########.fr       */
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

void	token_next_set(t_token **lst)
{
	t_token	*token;

	token = create_token(STR, ft_strdup(""));
	if (!token)
		exit_error(MALLOCERR, NULL, 1);
	addnext_token(lst, token);
	expand_null("", &(*lst)->str);
	*lst = (*lst)->next;
}

static void	expand_div_util(t_token **lst, t_token **t)
{
	(*lst)->str = front_join((*lst)->str, ft_strdup((*t)->str));
	*t = (*t)->next;
	if (*t)
		token_next_set(lst);
}

void	expand_div(t_token **lst, char *str, int flag)
{
	t_token	*t;
	t_token	*tmp;

	if (!flag)
	{
		(*lst)->str = front_join((*lst)->str, str);
		if (!(*lst)->str)
			exit_error(MALLOCERR, NULL, 1);
		return ;
	}
	t = tokenise(str);
	lexer_tokens(t);
	tmp = t;
	if (ft_isspace(*str))
		token_next_set(lst);
	while (t)
		expand_div_util(lst, &t);
	if (ft_isspace(str[ft_strlen(str) - 1]))
		token_next_set(lst);
	free(str);
	if (tmp)
		free_token(tmp);
}