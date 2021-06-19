#include "../../includes/parser.h"
#include "../../includes/lexer.h"
#include "../../includes/exec.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		free(tmp->str);
		token = token->next;
		free(tmp);
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	**tmp_tokens;

	if (!tokens)
		return ;
	tmp_tokens = tokens;
	free_token(*tokens);
	free(tmp_tokens);
}
