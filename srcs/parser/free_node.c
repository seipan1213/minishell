/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:08:23 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/03 20:29:59 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/lexer.h"

void	free_redirect(t_redirect *rd)
{
	t_redirect	*tmp;
	t_redirect	*now;

	now = rd;
	while (now)
	{
		tmp = now->next;
		free_token(now->filename);
		free(now);
		now = tmp;
	}
	rd = NULL;
}

void	free_cmd(t_command *cmd)
{
	t_command	*now;

	now = cmd;
	if (now)
	{
		free_redirect(now->rd);
		free_token(now->arg);
		free(now);
	}
	cmd = NULL;
}

int	is_node_type(int type)
{
	if (type == SCOLON || type == PIPE || type == STR)
		return (1);
	return (0);
}

void	free_node(t_astNode *node)
{
	if (!node)
		return ;
	if (is_node_type(node->type) && node->cmd)
	{
		free_cmd(node->cmd);
		node->cmd = NULL;
	}
	free_node(node->left);
	free_node(node->right);
	free(node);
	node = NULL;
}
