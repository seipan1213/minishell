#include "../../includes/parser.h"
#include "../../includes/lexer.h"

void	free_redirect(t_redirect *rd)
{
	t_redirect	*tmp;

	while (rd)
	{
		tmp = rd;
		free_token(tmp->filename);
		rd = rd->next;
		free(tmp);
	}
}

void	free_cmd(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd;
		free_redirect(tmp->rd);
		free_token(tmp->arg);
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_node(astNode *node)
{
	if (!node)
		return ;
	if (node->type == SCOLON || node->type == PIPE)
	{
		free_node(node->left);
		free_node(node->right);
		free(node);
	}
	else
	{
		free_cmd(node->cmd);
		free(node);
	}
}