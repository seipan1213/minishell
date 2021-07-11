/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:08:37 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/10 03:18:13 by sehattor         ###   ########.fr       */
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
