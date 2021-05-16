/**
* @file parser.c

* @brief parser
**/

#include "../../includes/parser.h"

astNode		*new_node(int type, astNode *left, astNode *right)
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


int			p_cmd(t_token **tokens, astNode **node)
{
	// create new node
	// put cmd (args & rd) in node
	// return
}

int			p_job(t_token **tokens, astNode **node)
{
	// pass it to cmd to get new node
	p_cmd(tokens, node);
	// check "|" or not
	// if "|"
	// 		child = get right node
	//		new left = cur node, new right = child
}

int			p_cmdline(t_token **tokens, astNode **node)
{
	// pass it to job to get new node
	p_job(tokens, node);
	// check ";" or not
	// if ";"
	// 		child = get right node
	//		new left = cur node, new right = child
}

int			parser(t_token **tokens, astNode **node)
{
	int		result;
	result = p_cmdline(tokens, node);
	return (result);
}

// int main()
// {
// 	t_token		*tokens;
// 	astNode		*node;
// 	// t_list	*semi;
// 	// t_pipe	*pipe;

// 	tokens = NULL;
// 	tokens = token_init();
// 	print_token(tokens);

// 	t_command	*cmd;
// 	cmd = new_cmd_node(&tokens, &node);
	
// 	print_cmd(cmd);

// 	// del_token(list);
// 	// system("leaks a.out");
// 	return(0);
// }
