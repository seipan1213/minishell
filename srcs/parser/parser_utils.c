/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:58:38 by kotatabe          #+#    #+#             */
/*   Updated: 2021/07/03 20:29:59 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/lexer.h"
#include "../../includes/exec.h"

bool	is_rd(int type)
{
	return ((RDIR <= type && type <= LLLDIR) || type == RINT);
}

t_astNode	*new_cmd_node(t_cmd_link *cmd_ptr)
{
	t_astNode		*new;

	new = (t_astNode *)malloc(sizeof(t_astNode));
	new->cmd = (t_command *)malloc(sizeof(t_command));
	new->type = STR;
	new->left = NULL;
	new->right = NULL;
	new->cmd->arg = NULL;
	new->cmd->rd = NULL;
	new->cmd->pid = NO_PID;
	new->cmd->next = NULL;
	if (cmd_ptr->ptr)
		cmd_ptr->ptr->next = new->cmd;
	cmd_ptr->ptr = new->cmd;
	return (new);
}

t_astNode	*new_parent_node(int type, t_astNode *left, t_astNode *right)
{
	t_astNode		*new;

	new = (t_astNode *)malloc(sizeof(t_astNode));
	if (!new)
		return (NULL);
	new->type = type;
	new->left = left;
	new->right = right;
	new->cmd = NULL;
	return (new);
}
