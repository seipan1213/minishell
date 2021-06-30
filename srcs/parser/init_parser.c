/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:58:30 by kotatabe          #+#    #+#             */
/*   Updated: 2021/06/29 20:58:31 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/lexer.h"

void	put_token(t_token *t, char *val, int type)
{
	t->str = ft_strdup(val);
	t->type = (t_ttype)type;
}

t_token	*gen_token(char *val, int type)
{
	t_token	*new_t;

	new_t = NULL;
	new_t = (t_token *)malloc(sizeof(t_token));
	put_token(new_t, val, type);
	new_t->next = NULL;
	return (new_t);
}
