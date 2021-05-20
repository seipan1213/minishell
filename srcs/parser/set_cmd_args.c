
#include "../../includes/parser.h"
#include "../../includes/lexer.h"

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

	dup = gen_token(src->str, src->type);
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



// void		print_cmd(t_command *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("[%s]\n", cmd->arg);
// 		cmd = cmd->next;
// 	}
// }