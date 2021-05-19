/**
* @file parser.c

* @brief parser
**/

#include "../../includes/parser.h"
#include "../../includes/lexer.h"

bool	set_cmd_rd(t_token **tokens, t_command *cmd)
{
	set_cmd_token(*tokens, &cmd->rd);
	*tokens = (*tokens)->next;
	set_cmd_token(*tokens, &cmd->rd);
	*tokens = (*tokens)->next;
	return (TRUE);
}

bool	parse_cmd(t_token **tokens, astNode **node)
{
	*node = new_cmd_node(); 	// create new node
	while (*tokens)				// put t_command (args & rd) in node
	{
		if (is_type(tokens, STR))
		{
			set_cmd_args(tokens, (*node)->cmd);
		}
		else if (is_rd((*tokens)->type))
		{
			set_cmd_rd(tokens, (*node)->cmd);
		}
		else
			break ;
	}
	return(TRUE);
}

bool	parse_job(t_token **tokens, astNode **node)
{
	astNode		*right;

	right = NULL;
	if (!(parse_cmd(tokens, node)))
		return (FALSE);
	while (*tokens)
	{
		if (is_type(tokens, PIPE)) 	//	check "|" or not
		{
			*tokens = (*tokens)->next;
			if (!(parse_cmd(tokens, &right))) // get right node
				return(FALSE);
			*node = new_parent_node(PIPE, *node, right);
		}
		else
			break ;
	}
	return (TRUE);
}

bool	parse_cmdline(t_token **tokens, astNode **node)
{
	astNode		*right;

	if (!(parse_job(tokens, node)))
		return (FALSE);
	while (*tokens)
	{
		if (is_type(tokens, SCOLON)) //	check ";" or not
		{
			*tokens = (*tokens)->next;
			if (!(parse_job(tokens, &right))) // get right node
				return(FALSE);
			*node = new_parent_node(SCOLON, *node, right);
		}
		else
			break ;
	}
	return (TRUE);
}

bool	parser(t_token **tokens, astNode **node)
{
	int		result;
	result = parse_cmdline(tokens, node);
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

int main()
{
	t_token		*tokens;
	astNode		*node = NULL;
	t_command	*cmd;
	char		*line;
	// t_list	*semi;
	// t_pipe	*pipe;

	tokens = NULL;
	// printf("\n======= new_token =======\n");
	get_next_line(0, &line);
	tokens = lexer(line);
	ft_putstr_fd("qqqqqq\n", 1);
	// print_tokens(tokens);
	return (0);
	printf("\n======= new_node =======\n");
	if (!(parser(&tokens, &node)))
		perror("Failure\n");
	else
		ft_putstr_fd("Success!!!\n", 1);
	printf("		%d: \n\n", node->type);
	printf("	%d:		%d:%s \n\n",	node->left->type, \
									 	node->right->type, \
										node->right->cmd->arg->str);
	printf("%d:%s		%d:%s\n",	node->left->left->type, \
									node->left->left->cmd->arg->str, \
									node->left->right->type, \
									node->left->right->cmd->arg->str);
	// del_token(list);
	// system("leaks a.out");
	return(0);
}
