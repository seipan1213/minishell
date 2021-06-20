#include "../../includes/parser.h"
#include "../../includes/lexer.h"

void	free_redirect(t_redirect *rd)
{
	t_redirect	*tmp;

	while (rd)
	{
		tmp = rd;
			// print_tokens(rd->filename);
		free_token(tmp->filename);
		rd = rd->next;
		free(tmp);
	}
}

void	free_cmd(t_command *cmd)
{
	t_command	*tmp;
	t_command	*now;

	now = cmd;
	while (now)
	{
		tmp = now->next;
		free_redirect(now->rd);
		free_token(now->arg);
		free(now);
		now = tmp;
	}
	cmd = NULL;
}

int		is_node_type(int type)
{
	if (type == SCOLON || type == PIPE || type == STR)
		return (1);
	return (0);
}

void	free_node(astNode *node)
{
	// printf("\n===== free_node %p ====\n", node);
	if (!node)
		return ;
	if (is_node_type(node->type) && node->cmd)
	{
		// print_tokens(node->cmd->arg);
		free_cmd(node->cmd);
		node->cmd = NULL;
	}
	free_node(node->left);
	free_node(node->right);
	free(node);
	node = NULL;
	// printf("\n===== done!! %p ====\n", node);
}