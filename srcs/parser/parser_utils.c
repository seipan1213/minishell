
#include "../../includes/parser.h"

bool		is_rd(int type)
{
	return (1 <= type && type <= 5);
}

astNode		*new_cmd_node()
{
	astNode		*new;

	new = malloc(sizeof(astNode *));
	new->cmd = malloc(sizeof(t_command *));
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

	new = malloc(sizeof(astNode *));
	if (!new)
		return (NULL);
	new->type = type;
	new->left = left;
	new->right = right;
	new->cmd = NULL;
	return(new);
}