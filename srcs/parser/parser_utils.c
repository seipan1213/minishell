
#include "../../includes/parser.h"
#include "../../includes/lexer.h"
#include "../../includes/exec.h"


bool		is_rd(int type)
{
	return ((RDIR <= type && type <= LLLDIR) || type == RINT);
}

astNode		*new_cmd_node(t_cmd_link *cmd_ptr)
{
	astNode		*new;

	new = (astNode *)malloc(sizeof(astNode));
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

astNode		*new_parent_node(int type, astNode *left, astNode *right)
{
	astNode		*new;

	new = (astNode *)malloc(sizeof(astNode));
	if (!new)
		return (NULL);
	new->type = type;
	new->left = left;
	new->right = right;
	new->cmd = NULL;
	return(new);
}