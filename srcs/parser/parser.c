/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotatabe <kotatabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:07:47 by kotatabe          #+#    #+#             */
/*   Updated: 2021/08/01 13:43:18 by kotatabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/lexer.h"
#include "../../includes/exec.h"

bool	parse_cmd_rd(t_token **tokens, t_command *cmd)
{
	t_redirect	*rd;

	rd = init_redirect();
	if ((*tokens)->type == RINT)
	{
		if (is_intrange((*tokens)->str))
			return (put_error(BAD_FD, FD_OUTOFRANGE, FALSE));
		rd->fd_file = ft_atoi((*tokens)->str);
		*tokens = (*tokens)->next;
	}
	set_rd_type(rd, *tokens);
	*tokens = (*tokens)->next;
	if (!*tokens)
	{
		free(rd);
		return (put_error(SYNTAXERR, NULL, FALSE));
	}
	rd->filename = gen_token((*tokens)->str, (*tokens)->type);
	set_cmd_rd(rd, &cmd->rd);
	*tokens = (*tokens)->next;
	return (TRUE);
}

bool	parse_cmd(t_token **tokens, t_astNode **node, t_cmd_link *cmd_ptr)
{
	*node = new_cmd_node(cmd_ptr);
	while (*tokens)
	{
		if (is_type(tokens, STR))
		{
			if (set_cmd_args(tokens, (*node)->cmd) == FALSE)
				return (FALSE);
		}
		else if (is_rd((*tokens)->type))
		{
			if (parse_cmd_rd(tokens, (*node)->cmd) == FALSE)
				return (FALSE);
		}
		else
			break ;
	}
	return (TRUE);
}

bool	parse_job(t_token **tokens, t_astNode **node, t_cmd_link *cmd_ptr)
{
	t_astNode		*right;

	right = NULL;
	if (!(parse_cmd(tokens, node, cmd_ptr)))
		return (FALSE);
	while (*tokens)
	{
		if (is_type(tokens, PIPE))
		{
			*tokens = (*tokens)->next;
			if (!*tokens)
				return (put_error(SYNTAXERR, NULL, FALSE));
			if (!(parse_cmd(tokens, &right, cmd_ptr)))
				return (FALSE);
			*node = new_parent_node(PIPE, *node, right);
		}
		else
			break ;
	}
	return (TRUE);
}

bool	parse_cmdline(t_token **tokens, t_astNode **node)
{
	t_astNode	*right;
	t_cmd_link	cmd_ptr;

	cmd_ptr.ptr = NULL;
	if (!(parse_job(tokens, node, &cmd_ptr)))
		return (FALSE);
	while (*tokens)
	{
		if (is_type(tokens, SCOLON))
		{
			cmd_ptr.ptr = NULL;
			*tokens = (*tokens)->next;
			if (!*tokens)
				break ;
			if (!(parse_job(tokens, &right, &cmd_ptr)))
				return (FALSE);
			*node = new_parent_node(SCOLON, *node, right);
		}
		else
			break ;
	}
	return (TRUE);
}

bool	parser(t_token **tokens, t_astNode **node)
{
	int			result;
	t_token		*for_free;

	for_free = *tokens;
	if (!tokens || !*tokens)
		return (0);
	result = parse_cmdline(tokens, node);
	if (result == FALSE)
	{
		g_data.status = EXIT_FAILURE;
		free_node(*node);
		*node = NULL;
	}
	free_token(for_free);
	return (result);
}
