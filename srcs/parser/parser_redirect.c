#include "../../includes/parser.h"

t_redirect	*init_redirect(void)
{
	t_redirect	*ret;

	ret = (t_redirect*)malloc(sizeof(t_redirect));
	ret->fd_io = NOT_SPECIFIED;
	ret->fd_file = NOT_SPECIFIED;
	ret->type = NOT_SPECIFIED;
	ret->filename = NULL;
	ret->next = NULL;
	return (ret);
}

void		set_rd_type(t_rd_type *type, t_token *token)
{
	if (token->type == LDIR)
		*type = RD_INPUT;
	else if (token->type == RDIR)
		*type = RD_OUTPUT;
	else if (token->type == RRDIR)
		*type = RD_APPEND_OUTPUT;
}

void		set_cmd_rd(t_redirect *rd, t_redirect **list)
{
	t_redirect	*last;

	if (!*list)
	{
		*list = rd;
	}
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = rd;
		rd->next = NULL;
	}
}