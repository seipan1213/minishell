#include "../../includes/parser.h"
#include "../../includes/lexer.h"
#include "../../includes/exec.h"

void	free_token(t_token *token)
{
	t_token	*tmp;
	t_token	*now;

	now = token;
	while (now)
	{
		tmp = now->next;
		free(now->str);
		free(now);
		now = tmp;
	}
	token = NULL;
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
