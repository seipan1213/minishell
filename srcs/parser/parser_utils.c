
#include "../../includes/parser.h"
#include "../../includes/lexer.h"


bool		is_rd(int type)
{
	return (1 <= type && type <= 5);
}

astNode		*new_cmd_node()
{
	astNode		*new;

	new = (astNode *)malloc(sizeof(astNode));
	new->cmd = (t_command *)malloc(sizeof(t_command));
	new->type = STR;
	new->left = NULL;
	new->right = NULL;
	new->cmd->arg = NULL;
	new->cmd->rd = NULL;
	new->cmd->next = NULL;
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