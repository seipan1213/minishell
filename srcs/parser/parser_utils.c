
#include "../../includes/parser.h"

bool		is_simple_cmd(int type)
{
	return (0 <= type && type <= 5);
}

bool		is_type(t_token **tokens, int type)
{
	return ((*tokens)->type == type);
}

t_command	*create_cmd()
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command *));
	if (!cmd)
		return(NULL);
	cmd->arg = NULL;
	cmd->rd = NULL;
	cmd->next = NULL;
	return (cmd);
}

void		init_cmd(t_token **tokens, t_command **cmd)
{
	t_command	*last;
	t_command	*tmp;

	tmp = create_cmd();
	tmp->arg = ft_strdup((*tokens)->val);
	if (!cmd)
		(*cmd) = tmp;
	else
	{
		last = (*cmd);
		while (last->next)
			last = last->next;
		last->next = tmp;
	}
}

t_command	*new_cmd_node(t_token **tokens, astNode **node)
{
	t_command	*new;

	new = NULL;
	while (tokens && is_simple_cmd((*tokens)->type))
	{
		ft_putstr_fd("debag\n", 1);
		init_cmd(tokens, &new);
		ft_putstr_fd(new->arg, 1);
		*tokens = (*tokens)->next;
	}
	return(new);
}

void		print_cmd(t_command *cmd)
{
	while (cmd)
	{
		printf("[%s]\n", cmd->arg);
		cmd = cmd->next;
	}
}

int main()
{
	t_token		*tokens;
	astNode		*node;
	// t_list	*semi;
	// t_pipe	*pipe;

	tokens = NULL;
	tokens = token_init();
	print_token(tokens);
	t_command	*cmd;
	if (!(cmd = new_cmd_node(&tokens, &node)))
		printf("False\n");
	print_cmd(cmd);

	// del_token(list);
	// system("leaks a.out");
	return(0);
}