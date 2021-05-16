
#include "../../includes/parser.h"

bool		is_simple_cmd(t_token **tokens)
{
	if (!(*tokens))
		return (0);
	return (0 <= (*tokens)->type && (*tokens)->type <= 5);
}

bool		is_type(t_token **tokens, int type)
{
	if (!(*tokens))
		return (0);
	return ((*tokens)->type == type);
}

t_command	*create_cmd()
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return(NULL);
	cmd->arg = NULL;
	cmd->rd = NULL;
	cmd->next = NULL;
	return (cmd);
}

void		set_cmd_token(t_token *src, t_token **dest)
{
	t_token		*last;
	t_token		*dup;

	dup = create_token(src->val, src->type);
	if (!*dest)
	{
		*dest = dup;
	}
	else
	{
		last = *dest;
		while (last->next)
			last = last->next;
		last->next = dup;
	}
}

void		set_cmd_args(t_token **tokens, t_command *cmd)
{
	while (tokens && is_simple_cmd(tokens))
	{
		set_cmd_token(*tokens, &cmd->arg);
		*tokens = (*tokens)->next;
	}
}

int main()
{
	t_token		*tokens;
	astNode		*node = NULL;
	t_command	*cmd;
	// t_list	*semi;
	// t_pipe	*pipe;

	tokens = NULL;
	printf("\n======= new_token =======\n");
	tokens = token_init();
	print_token(tokens);
	// printf("\n======= new_arg =======\n");
	// if (!(cmd = create_cmd()))
	// 	perror("false\n");
	// set_cmd_args(&tokens, cmd);
	// print_token(cmd->arg);

	printf("\n======= new_node =======\n");
	if (!(parser(&tokens, &node)))
		perror("Failure\n");
	else
		ft_putstr_fd("Success!!!\n", 1);
	printf("		%d: \n\n", node->type);
	printf("	%d:		%d:%s \n\n",	node->left->type, \
									 	node->right->type, \
										node->right->cmd->arg->val);
	printf("%d:%s		%d:%s\n",	node->left->left->type, \
									node->left->left->cmd->arg->val, \
									node->left->right->type, \
									node->left->right->cmd->arg->val);
	// del_token(list);
	// system("leaks a.out");
	return(0);
}

// void		print_cmd(t_command *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("[%s]\n", cmd->arg);
// 		cmd = cmd->next;
// 	}
// }