/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:08:37 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/29 21:08:49 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/lexer.h"
#include "../../includes/exec.h"

void	free_token(t_token *token)
{
	t_token	*tmp;
	t_token	*now;

	now = token;
	while (now)
	{
		tmp = now->next;
		free(now->str);
		free(now);
		now = tmp;
	}
	token = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	**tmp_tokens;

	if (!tokens)
		return ;
	tmp_tokens = tokens;
	free_token(*tokens);
	free(tmp_tokens);
}
